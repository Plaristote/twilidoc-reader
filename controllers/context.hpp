#pragma once
#include "application.hpp"

class ContextController : public ApplicationController
{
public:
  ContextController(const Comet::Params&);

  Comet::Promise initialize() { return ApplicationController::initialize(); }
  Comet::Promise finalize()   { return ApplicationController::finalize(); }

  void root();
  void namespace_();
};
