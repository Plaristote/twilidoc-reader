#pragma once
#include "application.hpp"

class FunctionController : public ApplicationController
{
public:
  FunctionController(const Comet::Params&);

  Comet::Promise initialize() { return ApplicationController::initialize(); }
  Comet::Promise finalize()   { return ApplicationController::finalize(); }

  void show();
};
