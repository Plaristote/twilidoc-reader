#include "class_breadcrumb.hpp"
#include "models/project.hpp"
#include "models/namespace.hpp"
#include "models/function.hpp"
#include "helpers/package.hpp"
#include <iostream>

using namespace std;

ClassBreadcrumb::ClassBreadcrumb()
{
  add_class("breadcrumbs");
}

static string get_uri_for_fragment(const string& name)
{
  auto nses = ProjectModel::instance.get_namespaces();
  auto classes = ProjectModel::instance.get_classes();
  shared_ptr<NamespaceModel> ns_result;
  shared_ptr<ClassModel> class_result;
  
  ns_result = nses.find([name](const shared_ptr<NamespaceModel>& ns) { return ns->get_full_name() == name; });
  if (ns_result)
    return PackageHelper::uri("#/namespaces/" + name, PackageHelper::current_package);
  class_result = classes.find([name](const shared_ptr<ClassModel>& klass) { return klass->get_full_name() == name; });
    return PackageHelper::uri("#/classes/" + name, class_result->get_package());
  return "";
}

void ClassBreadcrumb::trigger_binding_updates()
{
  empty();
  if (full_name.length() > 0 && name.length() > 0)
    generate_crumbs();
}

void ClassBreadcrumb::generate_crumbs()
{
  *this > Comet::Element(
    "a", {
      {"class", "crumb"},
      {"href",  PackageHelper::uri("#/namespaces", PackageHelper::current_package)}
    }
  ).text(PackageHelper::current_package.length() ? PackageHelper::current_package : "Root");
  for (const auto& entry : fragments())
  {
    string uri = get_uri_for_fragment(entry.first);
    Comet::Element link(uri.length() > 0 ? "a" : "span");
    Comet::Element separator("span", {{"class","sep"}});

    link.add_class("crumb");
    link.text(entry.second);
    if (uri.length() > 0)
      link.attr("href", uri);
    *this > separator;
    *this > link;
  }
}

map<string, string> ClassBreadcrumb::fragments() const
{
  map<string, string> result;
  string scope = full_name.substr(2, full_name.length() - name.length() - 2);
  size_t scope_starts_at = 0;

  for (int i = 0 ; i < scope.length() ; ++i)
  {
    if (scope[i] == ':' && scope[i + 1] == ':')
    {
      string parent_scope = "::" + scope.substr(0, i);
      string fragment = scope.substr(scope_starts_at, i - scope_starts_at);

      result.emplace(parent_scope, fragment);
      ++i;
      scope_starts_at = i + 1;
    }
  }
  return result;
}

void ClassBreadcrumb::set_namespace(const NamespaceModel& ns)
{
  full_name = ns.get_full_name();
  name = ns.get_name();
  trigger_binding_updates();
}

void ClassBreadcrumb::set_function(const FunctionModel& func)
{
  full_name = func.get_full_name();
  name = func.get_name();
  trigger_binding_updates();
}
