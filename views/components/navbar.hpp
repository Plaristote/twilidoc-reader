#pragma once
#include "templates/components/navbar.hpp"
#include "views/components/searchbar.hpp"

class Navbar : public HtmlTemplate::Navbar, public Comet::Listener
{
public:
  Navbar();

  void on_route_changed(const std::string&);

private:
  SearchBar searchbar;
};
