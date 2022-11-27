#pragma once
#include "application.hpp"

class EnumController : public ApplicationController
{
public:
  EnumController(const Comet::Params&);

  Comet::Promise initialize() { return ApplicationController::initialize(); }
  Comet::Promise finalize()   { return ApplicationController::finalize(); }

  void show();
};
