#include "class.hpp"
#include <comet/globals.hpp>

using namespace std;

ClassView::ClassView()
{
  visibility_picker.signaler.connect([this](const string& message)
  {
    cout << "visibility picker signal " << message << endl;
    if (message == "visibility-change")
      signaler.trigger("update-visibility");
  });
}

void ClassView::scroll_to_method(const string& method)
{
  string escaped_method = Comet::window["CSS"].apply("escape", Comet::String(method));
  Element el = find_one("#method_" + escaped_method);

  if (!el.is_undefined())
  {
    const double headerSize = 64;
    auto* rect = el->getBoundingClientRect();
    Comet::ObjectImpl<client::ScrollToOptions> options(new client::ScrollToOptions);

    options.set("behavior", "smooth");
    options->set_top(rect->get_top() - headerSize - 10);
    Comet::window->scrollTo(options.native_object());
  }
}

void ClassView::toggle_inherited_display()
{
  if (!inherited_members_initialize)
    set_inherited_methods(ProjectModel::instance.collect_inherited_methods(model, {}));
  set_with_inherited_members(!with_inherited_members);
  signaler.trigger("inherit-display");
}

string ClassView::documentation_for_method(const string& method_name) const
{
  auto it = method_docs.find(method_name);

   return it != method_docs.end() ? it->second : std::string();
}
