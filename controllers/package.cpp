#include "package.hpp"
#include "views/module_index.hpp"

using namespace std;

PackageController::PackageController(const Comet::Params& params) : ApplicationController(params)
{
}

void PackageController::index()
{
  auto view = make_shared<ModuleIndexView>();

  view->set_packages(ProjectModel::instance.get_packages());
  default_layout().render(view);
}

void PackageController::show()
{
}
