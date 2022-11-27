#include "project.hpp"
#include <comet/http.hpp>
#include <comet/globals.hpp>
#include <iostream>

using namespace std;

ProjectModel ProjectModel::instance;

Comet::Promise ProjectModel::fetch()
{
  return Comet::Promise::all({
    Comet::JsonModel<>::fetch(),
    fetch_external_types()
  });
}

void ProjectModel::from_json(Data json_data)
{
  name = json_data["project"].defaults_to<string>("");
  logo = json_data["icon"].defaults_to<string>("");
  Comet::window.set("twilidoc_types", json_data["types"].as_object());
  Comet::window.set("twilidoc_enums", json_data["enums"].as_object());
  Comet::window.set("twilidoc_class", json_data["classes"].as_object());
  types.from_data(json_data["types"]);
  namespaces.from_data(json_data["namespaces"]);
  classes.from_data(json_data["classes"]);
  functions.from_data(json_data["functions"]);
  enums.from_data(json_data["enums"]);
  json_data["packages"].each([this](const Data package_data) -> bool
  {
    packages.insert(package_data["package"].as<string>());
    if (package_data["excerpt"].exists())
      package_excerpts.emplace(package_data["package"].as<string>(), package_data["excerpt"].as<string>());
    return true;
  });
  namespaces.each(bind(&ProjectModel::probe_namespace_packages, this, placeholders::_1));
  Comet::Element(Comet::document->get_head()).find_one("link[rel=icon]").attr("href", get_logo());
}

void ProjectModel::probe_namespace_packages(const shared_ptr<NamespaceModel>& model)
{
  if (model->are_packages_loaded())
    return ;
  model->set_packages_loaded();
  for (const auto& sub_ns : from_context(namespaces, model))
  {
    probe_namespace_packages(sub_ns);
    for (const auto& package : sub_ns->get_packages())
      model->add_package(package);
  }
  for (const auto& klass : from_context(classes, model))
    model->add_package(klass->get_package());
  for (const auto& function : from_context(functions, model))
    model->add_package(function->get_package());
  for (const auto& en : from_context(enums, model))
    model->add_package(en->get_package());
}

Comet::Promise ProjectModel::fetch_external_types()
{
  auto request = Comet::Http::Request::get("docs/_external_types.json");

  return request->send().then([this, request]()
  {
    if (request->get_response()->ok())
    {
      external_types.from_json(request->get_response()->get_response_text());
    }
  });
}

Comet::Object ProjectModel::get_search_options()
{
  Comet::ObjectImpl<client::Array> array;

  namespaces.each([&array](const shared_ptr<NamespaceModel>& ns)
  {
    Comet::Object object;

    object.set("kind", static_cast<int>(NamespaceKind));
    object.set("name", ns->get_name());
    object.set("full_name", ns->get_full_name());
    object.set("uri", "/namespaces/" + ns->get_full_name());
    object.set("excerpt", ns->get_excerpt());
    array->push(*object);
  });
  classes.each([&array](const shared_ptr<ClassModel>& klass)
  {
    {
      Comet::Object object;

      object.set("kind", static_cast<int>(klass->get_declared_as() == "struct" ? StructKind : ClassKind));
      object.set("name", klass->get_name());
      object.set("full_name", klass->get_full_name());
      object.set("uri", "/classes/" + klass->get_full_name());
      object.set("excerpt", klass->get_excerpt());
      array->push(*object);
    }
    for (const auto& method : klass->get_methods())
    {
      Comet::Object object;

      object.set("kind", static_cast<int>(MethodKind));
      object.set("name", method->get_name());
      object.set("full_name", klass->get_full_name() + "::" + method->get_name());
      object.set("uri", "/classes/" + klass->get_full_name() + '/' + method->get_name());
      object.set("excerpt", method->get_excerpt());
      array->push(*object);
    }
    for (const auto& field : klass->get_fields())
    {
      Comet::Object object;

      object.set("kind", static_cast<int>(FieldKind));
      object.set("name", field->get_name());
      object.set("full_name", klass->get_full_name() + "::" + field->get_name());
      object.set("uri", "/classes/" + klass->get_full_name() + '/' + field->get_name());
      object.set("excerpt", field->get_excerpt());
      array->push(*object);
    }
  });
  functions.each([&array](const shared_ptr<FunctionModel>& func)
  {
    Comet::Object object;

    object.set("kind", static_cast<int>(FunctionKind));
    object.set("type", "function");
    object.set("name", func->get_name());
    object.set("full_name", func->get_full_name());
    object.set("uri", "/functions/" + func->get_full_name());
    object.set("excerpt", func->get_excerpt());
    array->push(*object);
  });
  enums.each([&array](const shared_ptr<EnumModel>& type)
  {
    Comet::Object object;

    object.set("kind", static_cast<int>(EnumKind));
    object.set("name", type->get_name());
    object.set("full_name", type->get_full_name());
    object.set("uri", "/enums/" + type->get_full_name());
    object.set("excerpt", "");
    array->push(*object);
  });
  types.each([&array](const shared_ptr<TypeModel>& type)
  {
    if (type->get_raw_name().length() > 0 &&
        type->get_kind() != StructKind &&
        type->get_kind() != ClassKind)
    {
      Comet::Object object;

      object.set("kind", static_cast<int>(type->get_kind()));
      object.set("name", type->get_raw_name());
      object.set("full_name", type->get_full_name());
      object.set("uri", "/typedef/" + type->get_full_name());
      object.set("excerpt", "");
      array->push(*object);
    }
  });
  return array;
}

string ProjectModel::get_package_excerpt(const string& package) const
{
  auto it = package_excerpts.find(package);

  if (it != package_excerpts.end())
    return it->second;
  return "";
}
