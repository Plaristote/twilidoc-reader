#pragma once
#include <comet/mvc/controller.hpp>
#include "views/layouts/application.hpp"
#include <sstream>

class ApplicationController : public Comet::Controller
{
public:
  ApplicationController(const Comet::Params& params) : Comet::Controller(params)
  {
  }

  Comet::Promise initialize();

  void render_404(const std::stringstream& stream)
  {
    render_404(stream.str());
  }

  void render_404(const std::string& message);

protected:
  Comet::Layout<ApplicationLayout>& default_layout();

  Comet::Promise fetch_documentation(const std::string& uri, std::function<void(const std::string&)> callback);

  static std::string package_param;
};
