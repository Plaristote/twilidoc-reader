#pragma once
#include "application.hpp"
#include "views/home.hpp"

class HomeController : public ApplicationController
{
public:
  HomeController(const Comet::Params&);

  void index();
};
