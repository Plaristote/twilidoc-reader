#pragma once
#include "invokable.hpp"

enum MethodFlags
{
  PlainMethod = 0,
  StaticMethod = 1,
  VirtualMethod = 2,
  PureVirtualMethod = 4,
  ConstMethod = 8
};

class ClassModel;

class MethodModel : public InvokableModel
{
public:
  MethodModel(ClassModel* p = nullptr) : parent(p) {}

  bool implements(const MethodModel&) const;
  bool is_constructor() const override;
  bool is_static() const { return (flags & StaticMethod) > 0; }
  bool is_virtual() const { return (flags & VirtualMethod) > 0; }
  bool is_pure_virtual() const { return (flags & PureVirtualMethod) > 0; }
  bool is_const() const { return (flags & ConstMethod) > 0; }
  unsigned short get_flags() const override { return flags; }
  CppVisibility get_visibility() const override { return visibility; }
  std::string  get_uri() const override;
  const std::string& get_package() const override;

  void from_json(Data json_data) override;

  static void load_list(Data list_data, std::vector<std::shared_ptr<MethodModel>>& list, ClassModel* parent = nullptr);

private:
  CppVisibility visibility;
  unsigned short flags = PlainMethod;
  ClassModel* parent = nullptr;
};

typedef std::vector<std::shared_ptr<MethodModel>> MethodList;

bool has_pure_virtual_methods(const MethodList&);
