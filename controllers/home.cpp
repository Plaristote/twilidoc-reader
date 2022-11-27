#include "home.hpp"
#include <comet/http.hpp>

using namespace std;

HomeController::HomeController(const Comet::Params& params) : ApplicationController(params)
{
}

void HomeController::index()
{
  auto request = Comet::Http::Request::get("docs/_home.html");
  auto view = make_shared<Home>();

  request->send().then([request, view]()
  {
    auto response = request->get_response();

    if (response->ok())
      view->set_homepage(response->get_response_text());
    else
      view->on_homepage_not_found();
  });
  default_layout().render(view);
}
