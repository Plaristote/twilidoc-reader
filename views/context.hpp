#pragma once
#include "templates/./context.hpp"

class ContextView : public HtmlTemplate::Context
{
public:
  ClassBreadcrumb& get_breadcrumbs() { return breadcrumbs; }

  void set_documentation(const std::string& doc_html)
  {
    doc.set_source(doc_html);
    doc.trigger_binding_updates();
    doc_wrapper.set_visible(true);
  }
};
