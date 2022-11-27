#include "function.hpp"
#include "models/project.hpp"
#include "views/function.hpp"

using namespace std;

FunctionController::FunctionController(const Comet::Params& params) : ApplicationController(params)
{
}

void FunctionController::show()
{
  auto& project = ProjectModel::instance;
  const string id = params.at("id");
  const auto& model = project.get_functions().get(id);

  if (model)
  {
    auto view = make_shared<FunctionView>();

    if (model->get_doc().length() > 0)
      fetch_documentation(model->get_doc(), bind(&FunctionView::set_documentation, view, placeholders::_1));
    view->set_model(model);
    default_layout().render(view);
  }
  else
    render_404(std::stringstream() << "function " << id << " not found");
}
