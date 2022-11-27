#pragma once
#include "param.hpp"
#include "visibility.hpp"

class ClassModel;

class FieldModel : public ParamModel
{
public:
  FieldModel(ClassModel* p = nullptr) : parent(p) {}
  CppVisibility get_visibility() const { return visibility; }
  bool is_static() const { return _is_static; }
  const std::string& get_doc() const { return doc; }
  const std::string& get_excerpt() const { return excerpt; }
  std::string get_uri() const;

  void from_json(Data json_data) override;

  static void load_list(Data list, std::vector<std::shared_ptr<FieldModel>>& out, ClassModel* parent);

private:
  CppVisibility visibility;
  bool _is_static = false;
  ClassModel* parent = nullptr;
  std::string doc, excerpt;
};

typedef std::vector<std::shared_ptr<FieldModel>> FieldList;
