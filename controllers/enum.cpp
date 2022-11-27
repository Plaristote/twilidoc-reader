#include "enum.hpp"
#include "models/project.hpp"
#include "views/enum.hpp"

using namespace std;
EnumController::EnumController(const Comet::Params& params) : ApplicationController(params)
{
}

void EnumController::show()
{
  const string id = params.at("id");
  auto& project = ProjectModel::instance;
  auto model = project.get_enums().get(id);

  if (model)
  {
    auto view = make_shared<EnumView>();

    view->set_model(model);
    view->trigger_binding_updates();
    default_layout().render(view);
  }
  else
    render_404(std::stringstream() << "enum " << id << " not found");
}
