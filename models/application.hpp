#pragma once
#include <comet/mvc/json_model.hpp>
#include "helpers/package.hpp"
#include "id.hpp"

class ApplicationModel : public Comet::JsonModel<Comet::StringIdTrait>
{
public:
  virtual std::string get_resource_name() const { return ""; }

  virtual const std::string& get_package() const = 0;

  virtual std::string get_uri() const
  {
    return PackageHelper::uri(
      "#/" + get_resource_name() + '/' + get_id(),
      get_package()
    );
  }
};
