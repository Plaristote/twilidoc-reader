#pragma once
#include "lib/tom_select.hpp"

class SearchBar
{
public:
  SearchBar(Comet::Element);
  ~SearchBar();

  void clear();

private:
  Comet::Element el;
  Comet::ObjectImpl<client::TomSelect> tom_select;
  Comet::JavascriptEvents events;
};
