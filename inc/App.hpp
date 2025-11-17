#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>

class App {
public:
    App();
    void run();

private:
    ftxui::Component root;
    ftxui::Component input;
    ftxui::Component button;
    std::string input_value;
};
