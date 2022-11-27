#pragma once
#include "templates/./class.hpp"
#include "components/highlightjs.hpp"
#include <iostream>

class ClassView : public HtmlTemplate::Class
{
public:
  ClassView();

  void set_documentation(const std::string& doc_html)
  {
    doc.set_source(doc_html);
    doc.trigger_binding_updates();
  }

  void set_method_documentation(const std::string& method, const std::string& doc)
  {
    method_docs.emplace(method, doc);
  }

  void scroll_to_method(const std::string& method);

private:
  void toggle_inherited_display() override;

  bool inherited_members_initialize = false;

  std::string documentation_for_method(const std::string& method_name) const override;
};
