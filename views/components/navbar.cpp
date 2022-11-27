#include "navbar.hpp"
#include "application.hpp"

using namespace std;

Navbar::Navbar() : searchbar(search_input)
{
  listen_to(Application::get().router.on_route_executed, std::bind(&Navbar::on_route_changed, this, std::placeholders::_1));
}

void Navbar::on_route_changed(const string& route)
{
  for (Comet::Element link : links.find("a"))
  {
    string href = link.get_attribute("href");
    if (route == "" || route == "/")
      link.toggle_class("active", href == "#");
    else if (route.find("/packages") == 0)
      link.toggle_class("active", href == "#/packages");
    else if (route.find("/namespaces") == 0 || route.find("/classes") == 0 || route.find("/functions") == 0)
      link.toggle_class("active", href == "#/namespaces");
    else
      link.remove_class("active");
  }
}
