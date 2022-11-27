#pragma once
#include "application.hpp"
#include "template_parameter.hpp"
#include "param.hpp"
#include "visibility.hpp"

class InvokableModel : public ApplicationModel
{
public:
  std::string get_url() const override { return ""; }

  const std::string& get_name() const { return name; }
  std::shared_ptr<ParamModel> get_return_type() const { return return_type; }
  const ParamModels& get_params() const { return params; }
  const TemplateParameters& get_template_parameters() const { return template_params; }
  bool is_template() const { return template_params.size() > 0; }
  virtual bool is_constructor() const { return false; }
  bool has_return_type() const { return return_type != nullptr; }
  const std::string& get_excerpt() const { return excerpt; }
  const std::string& get_doc() const { return doc; }
  virtual unsigned short get_flags() const { return 0; }
  virtual CppVisibility get_visibility() const { return PublicVisibility; }

  virtual void from_json(Data json_data) override;
  std::string to_json() const override { return ""; }

protected:
  std::string name;
  std::shared_ptr<ParamModel> return_type;
  ParamModels params;
  TemplateParameters template_params;
  std::string excerpt;
  std::string doc;
};
