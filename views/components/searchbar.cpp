#include "searchbar.hpp"
#include "models/project.hpp"
#include "application.hpp"
#include <comet/globals.hpp>
#include <iostream>

using namespace std;

static client::String* render_search_label(client::Object* raw_data)
{
  DataTree type_data(raw_data);
  Comet::Element virtual_container;
  Comet::Element el("div", {{"class","search-option"}});
  Comet::Element alias_el("span", {{"class","alias"}});
  Comet::Element name_el("span", {{"class","true-name"}});
  Comet::Element kind_el("span", {{"class","kind badge"}});
  string label;

  switch (type_data["kind"].defaults_to<int>(0))
  {
    case ClassKind:
      kind_el.text("class");
      kind_el.add_class("bg-primary");
      break ;
    case StructKind:
      kind_el.text("struct");
      kind_el.add_class("bg-primary");
      break ;
    case TypedefKind:
      kind_el.text("typedef");
      kind_el.add_class("bg-dark");
      break ;
    case EnumKind:
      kind_el.text("enum");
      kind_el.add_class("bg-dark");
      break ;
    case MethodKind:
      kind_el.text("method");
      kind_el.add_class("bg-warning");
      break ;
    case FunctionKind:
      kind_el.text("function");
      kind_el.add_class("bg-warning");
      break ;
    case FieldKind:
      kind_el.text("field");
      kind_el.add_class("bg-info");
      break ;
    case NamespaceKind:
      kind_el.text("namespace");
      kind_el.add_class("bg-secondary");
    default:
      break ;
  }
  el > kind_el;
  el > alias_el;
  el > name_el;
  alias_el.text(type_data["name"].as<string>());
  name_el.text(type_data["full_name"].as<string>());
  virtual_container > el;
  return *Comet::String(virtual_container.html());
}

static client::Object* search_score(client::String* raw_search)
{
  std::string search = Comet::String(raw_search);

  return cheerp::Callback([search](client::Object* _candidate)
  {
    double total = 0;
    try {
      Comet::Object candidate(_candidate);
      string full_name = candidate["full_name"];
      string name      = candidate["name"];
      string excerpt   = candidate["excerpt"];
      int    type      = candidate["kind"];

      if (name.find(search) != string::npos)
      {
        total -= (name.length() - search.length()) / 2;
        total += 30;
      }
      if (full_name.find(search) != string::npos)
      {
        total -= (full_name.length() - search.length()) / 2;
        total += 20;
      }
      if (excerpt.find(search) != string::npos)
        total += 10;
      if (total > 0)
      {
        switch (type)
        {
          case ClassKind:
          case StructKind:
          case NamespaceKind:
          case FunctionKind:
            total += 10;
            break ;
          case TypedefKind:
            total += 5;
            break ;
          default:
            total += 1;
            break ;
        }
      }
    } catch (...) {
      cout << "error happened in search_score" << endl;
    }
    return total;
  });
}

static void on_search(SearchBar* self, client::String* raw_value)
{
  string value = Comet::String(raw_value);

  self->clear();
  Application::get().router.navigate(value, true);
}

SearchBar::SearchBar(Comet::Element _el) : el(_el), tom_select((client::Object*)nullptr), events(*Comet::window)
{
  Comet::Object options, render_options;
  function<void(client::String*)> callback = std::bind(on_search, this, std::placeholders::_1);
  function<client::Object* (client::String*)> score_callback = search_score;

  options.set("options", ProjectModel::instance.get_search_options());;
  options.set("valueField", "uri");
  options.set("onItemAdd", callback);
  options.set("score", score_callback);
  options.set("render", render_options);
  render_options.set("option", function<client::String*(client::Object*)>(render_search_label));
  tom_select = new client::TomSelect(*el, *options);

  Comet::window.set("poil", options);

  events.on("keydown", [this](client::KeyboardEvent* event) -> bool
  {
    if (event->get_ctrlKey())
    {
      string pressed = Comet::String(event->get_key());
      if (pressed == "k")
      {
        tom_select->focus();
        event->preventDefault();
        return true;
      }
    }
    return false;
  });
}

SearchBar::~SearchBar()
{
  tom_select->destroy();
}

void SearchBar::clear()
{
  tom_select->clear();
}
