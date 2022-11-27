#pragma once
#include "application.hpp"

class ClassView;
class ClassModel;

class ClassController : public ApplicationController
{
public:
  ClassController(const Comet::Params&);

  Comet::Promise initialize() { return ApplicationController::initialize(); }
  Comet::Promise finalize()   { return ApplicationController::finalize(); }

  void show();
  void method();

private:
  bool view_already_attached(const std::string& id) const;
  std::shared_ptr<ClassView> render_class(const std::shared_ptr<ClassModel>&);
  std::shared_ptr<ClassModel> find_class();
  Comet::Promise fetch_method_documentations(const std::shared_ptr<ClassView>&, const std::shared_ptr<ClassModel>&);
};
