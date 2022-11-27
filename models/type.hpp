#pragma once
#include <comet/mvc/json_model.hpp>

enum TypeKind
{
  ClassKind = 1,
  StructKind,
  TypedefKind,
  EnumKind,
  NamespaceKind,
  MethodKind,
  FunctionKind,
  FieldKind,
  OtherKind
};

class TypeModel : public Comet::JsonModel<Comet::StringIdTrait>
{
public:
  std::string get_resource_name() const override { return "types"; }
  std::string get_url() const override { return ""; }

  TypeKind get_kind() const { return kind; }
  const std::string& get_raw_name() const { return raw_name; }
  const std::string& get_name() const { return name; }
  const std::string& get_full_name() const { return full_name; }
  const std::vector<std::string>& get_scopes() const { return scopes; }
  bool is_const() const { return _is_const; }
  int ref_count() const { return _ref_count; }
  int ptr_count() const { return _ptr_count; }

  void from_json(Data json_data) override;
  std::string to_json() const override { return ""; }

private:
  TypeKind kind;
  std::string raw_name;
  std::string name;
  std::string full_name;
  std::vector<std::string> scopes;
  bool _is_const = false;
  int _ref_count = 0;
  int _ptr_count = 0;
};
