#include "application.hpp"
#include "models/project.hpp"
#include "controllers/application.hpp"
#include <iostream>

using namespace std;

static bool application_loaded = false;

static void on_404(const string& value)
{
  ApplicationController controller({});

  cout << "Path not found: `" << value << '`' << endl;
  controller.render_404("Path invalid");
}

static void loading_view()
{
  Comet::Element el("div", {{"class","loading-view"}});

  el > vector<Comet::Element>{
    Comet::Element("img", {{"src","twicon.png"}}),
    Comet::Element("span").text("Twilidoc loading")
  };
  Comet::body > el;
}

void webMain()
{
  Comet::document.on_ready([]()
  {
    if (!application_loaded)
      loading_view();
  });
  Comet::window.set_timeout([]()
  {
    ProjectModel::instance.fetch().then([]()
    {
      application_loaded = true;
      Application::start();
      Application::get().router
        .on_route_not_found.connect(on_404);
    });
  }, 250);
}
