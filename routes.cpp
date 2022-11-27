#include <comet/router.hpp>
#include <comet/globals.hpp>
#include "controllers/home.hpp"
#include "controllers/context.hpp"
#include "controllers/class.hpp"
#include "controllers/function.hpp"
#include "controllers/enum.hpp"
#include "controllers/package.hpp"
#include "models/type_solver.hpp"

using namespace Comet;
using namespace std;

void Router::initialize()
{
  auto resource_routes = [&]()
  {
    match_action("/namespaces", ContextController, root);
    match_action("/namespaces/:id", ContextController, namespace_);
    match_action("/classes/:id", ClassController, show);
    match_action("/classes/:id/:path", ClassController, method);
    match_action("/functions/:id", FunctionController, show);
    match_action("/enums/:id", EnumController, show);
  };

  match_action("/?", HomeController, index);
  match_action("/packages", PackageController, index);
  match_action("/packages/:package", PackageController, show);
  resource_routes();
  scope("/packages/:package", resource_routes);
  match("/typedef/:id", [this](const Comet::Params& params)
  {
    TypeSolver solver;
    string path = Comet::window.apply("decodeURI", Comet::String(params.at("id")));

    solver.solve(path);
    if (solver.is_handled_type())
    {
      if (solver.get_link_target() == "_blank")
        Comet::window->open(solver.get_link().c_str());
      else if (solver.get_link()[0] == '#')
        navigate(solver.get_link().substr(1), true);
    }
    else
    {
      Comet::String message("No documentation available for " + path);
      Comet::window->alert(*message);
    }
  });
}
