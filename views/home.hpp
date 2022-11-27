#pragma once
#include "templates/./home.hpp"
#include "components/highlightjs.hpp"

class Home : public HtmlTemplate::Home
{
public:
  void set_homepage(const std::string& homepage_html)
  {
    doc_view.set_source(homepage_html);
    set_loading(false);
    trigger_binding_updates();
    doc_view.trigger_binding_updates();
  }

  void on_homepage_not_found()
  {
    text("No homepage for this project.");
  }
};
