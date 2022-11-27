#pragma once
#include "templates/./function.hpp"

class FunctionView : public HtmlTemplate::Function
{
public:
  void set_documentation(const std::string& doc_html)
  {
    doc.set_source(doc_html);
    doc.trigger_binding_updates();
  }
};
