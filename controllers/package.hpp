#pragma once
#include "application.hpp"

class PackageController : public ApplicationController
{
public:
  PackageController(const Comet::Params&);

  Comet::Promise initialize() { return Comet::Controller::initialize(); }
  Comet::Promise finalize()   { return Comet::Controller::finalize(); }

  void index();
  void show();
};
