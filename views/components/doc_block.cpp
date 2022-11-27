#include "doc_block.hpp"
#include "highlightjs.hpp"
#include "type_popup.hpp"

using namespace std;

void DocBlock::trigger_binding_updates()
{
  type_links.clear();
  type_popups.clear();
  HtmlTemplate::DocBlock::trigger_binding_updates();
  fix_code_link_issue();
  highlight_element(doc_el);
  initialize_links();
  initialize_type_buttons();
}

void DocBlock::initialize_links()
{
  for (Comet::Element link : doc_el.find("a"))
  {
    if (!link.has_attribute("target"))
    {
      const string href = link.get_attribute("href");

      link.attr(
        "target",
        href.find("://") != std::string::npos ? "_blank" : "_self"
      );
    }
  }
}

void DocBlock::initialize_type_buttons()
{
  for (Comet::Element typelink : doc_el.find(".btn-cpptype"))
  {
    Comet::Element* link;
    TypeSolver type_solver;

    type_links.push_back(typelink);
    link = &(*type_links.rbegin());
    type_solver.solve(typelink.get_attribute("data-cpptype"));
    if (type_solver.is_handled_type())
    {
      auto popup = make_shared<TypePopup>();

      popup->set_type_solver(type_solver);
      link->events->on("mouseenter", [popup]() { popup->set_visible(true); });
      link->events->on("mouseleave", [popup]() { popup->set_visible(false); });
      link->attr({
        {"href", type_solver.get_link()},
        {"target", type_solver.get_link_target()}
      });
      typelink > *popup;
      popup->set_visible(false);
      popup->trigger_binding_updates();
      type_popups.push_back(popup);
    }
  }
}

void DocBlock::fix_code_link_issue()
{
  for (Comet::Element link : doc_el.find("code > a"))
    link.text('[' + link.get_text() + ']');
}
