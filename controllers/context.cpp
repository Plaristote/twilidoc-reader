#include "context.hpp"
#include "models/project.hpp"
#include "views/context.hpp"
#include <iostream>

using namespace std;
ContextController::ContextController(const Comet::Params& params) : ApplicationController(params)
{
}

void ContextController::root()
{
  auto& project = ProjectModel::instance;
  auto view = make_shared<ContextView>();

  if (!package_param.length())
    view->set_title("Global namespace");
  else
  {
    view->set_package(package_param);
    view->set_title(package_param);
    fetch_documentation(
      "/packages/" + package_param + ".html",
      bind(&ContextView::set_documentation, view, placeholders::_1)
    );
  }
  view->set_namespaces(project.from_root_context(project.get_namespaces(), package_param));
  view->set_classes(project.from_root_context(project.get_classes(), package_param));
  view->set_functions(project.from_root_context(project.get_functions(), package_param));
  view->set_enums(project.from_root_context(project.get_enums(), package_param));
  default_layout().render(view);
}

void ContextController::namespace_()
{
  const string id = params.at("id");
  auto& project = ProjectModel::instance;
  auto model = project.get_namespaces().get(id);

  if (model)
  {
    auto view = make_shared<ContextView>();

    view->set_title(model->get_title());
    view->set_namespaces(project.from_context(project.get_namespaces(), model, package_param));
    view->set_classes(project.from_context(project.get_classes(), model, package_param));
    view->set_functions(project.from_context(project.get_functions(), model, package_param));
    view->set_enums(project.from_context(project.get_enums(), model, package_param));
    view->get_breadcrumbs().set_namespace(*model);
    if (model->get_doc().length() > 0)
      fetch_documentation(model->get_doc(), bind(&ContextView::set_documentation, view, placeholders::_1));
    default_layout().render(view);
  }
  else
    render_404(std::stringstream() << "namespace " << id << " not found");
}

