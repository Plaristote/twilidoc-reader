#pragma once
#include "templates/components/doc_block.hpp"

class TypePopup;

class DocBlock : public HtmlTemplate::DocBlock
{
public:
  void trigger_binding_updates() override;
private:
  void fix_code_link_issue();
  void initialize_links();
  void initialize_type_buttons();

  std::list<Comet::Element> type_links;
  std::list<std::shared_ptr<TypePopup>> type_popups;
};
