#include "../inc/App.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

App::App() {
    input  = Input(&input_value, "Type here...");
    button = Button("OK", [&]{
        std::cout << "Pressed: " << input_value << "\n";
    });

    root = Container::Vertical({
        input,
        button,
    });

    root = Renderer(root, [&]{
        return window(text("curlsmith"), vbox({
            text("A TUI curl command builder"),
            separator(),
            text("URL: " + input_value),
            input->Render(),
            button->Render(),
        })) | center;
    });
}

void App::run() {
    auto screen = ScreenInteractive::TerminalOutput();
    screen.TrackMouse(false);
    screen.Loop(root);
}
