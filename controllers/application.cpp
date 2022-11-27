#include "application.hpp"
#include "views/not_found.hpp"
#include "helpers/package.hpp"
#include <comet/http.hpp>
#include <comet/globals.hpp>
 
using namespace std;

std::string ApplicationController::package_param;

Comet::Layout<ApplicationLayout>& ApplicationController::default_layout()
{
  Comet::window->scrollTo(0, 0);
  return use_layout<ApplicationLayout>();
}

Comet::Promise ApplicationController::initialize()
{
  auto it = params.find("package");

  PackageHelper::current_package = package_param = it != params.end() ? it->second : "";
  return Comet::Controller::initialize();
}

void ApplicationController::render_404(const string& message)
{
  auto view = make_shared<NotFoundView>();
  
  view->set_message(message);
  default_layout().render(view);
}

Comet::Promise ApplicationController::fetch_documentation(const string& uri, function<void(const string&)> callback)
{
  auto query = Comet::Http::Request::get(uri);

  return query->send().then([query, callback]()
  {
    auto response = query->get_response();

    if (response->ok())
      callback(response->get_response_text());
    else
      callback("");
  });
}
