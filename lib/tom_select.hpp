#pragma once
#include <comet/element.hpp>

namespace client
{
  class TomSelect : public client::Object
  {
  public:
    TomSelect(client::HTMLElement*, client::Object*);
    void focus();
    void clear();
    void destroy();
  };
}
