#include "../inc/App.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <memory>

using namespace ftxui;

App::App() {
    urlInput = Input(&urlInputValue, "Type here...");

    methodOptions = {
        "GET", "POST", "PUT", "DELETE", "PATCH", "HEAD", "OPTIONS"
    };
    methodSelected = 0;
    methodRadiobox = Radiobox(&methodOptions, &methodSelected);

    generateCmdButton = Button("Generate", [&]{
        std::exit(1);
    });

    generateCmdButton = CatchEvent(generateCmdButton, [&](Event event) {
        if (event == Event::Return) {
            std::exit(1);
            return true;
        }
        return false;
    });

    headersContainer = Container::Vertical({});

    addHeaderButton = Button("Add header", [&]{
        auto data = std::make_shared<HeaderData>();
        headerData.push_back(data);

        auto keyInput = Input(&data->key, "Key (e.g., Content-Type)");
        auto valueInput = Input(&data->value, "Value (e.g., application/json)");
        data->keyInput = keyInput;
        data->valueInput = valueInput;
        auto pairContainer = Container::Horizontal({keyInput, valueInput});
        headersContainer->Add(pairContainer);
    });

    root = Container::Vertical({
        urlInput,
        methodRadiobox,
        addHeaderButton,
        headersContainer,
        generateCmdButton,
    });

    root = Renderer(root, [&]{
        std::vector<Element> headerElems;
        for (size_t i = 0; i < headerData.size(); i++) {
            headerElems.push_back(
                hbox({
                    text("Header " + std::to_string(i + 1) + ": "),
                    headerData[i]->keyInput->Render() | size(WIDTH, EQUAL, 25),
                    text(" : "),
                    headerData[i]->valueInput->Render() | flex,
                }) | border
            );
        }

        return window(text("curlsmith"), vbox({
            text("A TUI curl command builder"),
            separator(),
            text("URL: " + urlInputValue),
            urlInput->Render(),
            separator(),
            methodRadiobox->Render(),
            separator(),
            hbox({
                text("Headers"),
                filler(),
                addHeaderButton->Render(),
            }),
            vbox(headerElems),
            separator(),
            generateCmdButton->Render(),
        })) | center;
    });
}

void App::run() {
    auto screen = ScreenInteractive::TerminalOutput();
    screen.TrackMouse(false);
    screen.Loop(root);
}
