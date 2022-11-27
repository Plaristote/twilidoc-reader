#pragma once
#include <comet/mvc/json_collection.hpp>

template<typename MODEL>
class ApplicationCollection : public Comet::JsonCollection<MODEL>
{
public:
  std::string get_url() const override { return ""; }

  void from_data(Data models_json) override
  {
    return Comet::JsonCollection<MODEL>::from_data(models_json);
  }
};
