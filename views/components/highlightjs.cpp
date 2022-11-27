#include "highlightjs.hpp"
#include <comet/globals.hpp>

void highlight_element(Comet::Element root)
{
  auto* node_list = root->querySelectorAll("code[class^='language-']");
  for (double i = 0 ; i < node_list->get_length() ; ++i)
  {
    if (node_list->item(i)->get_nodeType() == 1)
    {
      client::Object* object = static_cast<client::Object*>(node_list->item(i));
      Comet::window->set_("_tmp", object);
      client::eval("hljs.highlightElement(_tmp)");
    }
  }
}
