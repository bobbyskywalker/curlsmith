#include "../inc/AppInterface.hpp"
#include "../inc/HttpMethod.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <memory>

void AppInterface::initChildren() {
    urlInput = Input(&urlInputValue, "Type here...");

    methodOptions = {
        "GET", "POST", "PUT", "DELETE", "PATCH", "HEAD", "OPTIONS"
    };
    methodRadiobox = Radiobox(&methodOptions, &methodSelected);

    requestBody = Input(&requestBodyValue, "Type here...");

    generateCmdButton = Button("Generate", []{
        std::exit(1);
    });

    generateCmdButton = CatchEvent(generateCmdButton, [](Event const& event) {
        if (event == Event::Return) {
            std::exit(1);
        }
        return false;
    });

    headersContainer = ftxui::Container::Vertical({});

    addHeaderButton = Button("Add header", [this]{
        const auto data = std::make_shared<HeaderData>();
        headerData.push_back(data);

        auto keyInput = Input(&data->key, "Key (e.g., Content-Type)");
        auto valueInput = Input(&data->value, "Value (e.g., application/json)");
        data->keyInput = keyInput;
        data->valueInput = valueInput;
        const auto pairContainer = ftxui::Container::Horizontal({keyInput, valueInput});
        headersContainer->Add(pairContainer);
    });
}

void AppInterface::populateRoot() {
    root = ftxui::Container::Vertical({
        urlInput,
        methodRadiobox,
        addHeaderButton,
        headersContainer,
        requestBody,
        generateCmdButton,
    });
}

std::vector<Element> AppInterface::renderHeaderElements() const {
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
    return headerElems;
}

std::vector<Element> AppInterface::renderMainElements(const std::vector<Element>& headerElements) const {
    std::vector mainElements = {
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
        vbox(headerElements),
        separator(),
    };
    return mainElements;
}

void AppInterface::renderRequestBodyField(std::vector<Element>& mainElements) const {
    if (methodSelected == static_cast<int>(HttpMethod::POST) ||
        methodSelected == static_cast<int>(HttpMethod::PUT) ||
        methodSelected == static_cast<int>(HttpMethod::PATCH)) {

        mainElements.push_back(hbox({
            text("Request body"),
            filler()
        }));
        mainElements.push_back(requestBody->Render());
        mainElements.push_back(separator());
        }
}

AppInterface::AppInterface() {
    methodSelected = 0;
    initChildren();
    populateRoot();

    root = Renderer(root, [this] {
        const std::vector<Element> headerElements = renderHeaderElements();
        std::vector<Element> mainElements = renderMainElements(headerElements);
        renderRequestBodyField(mainElements);
        mainElements.push_back(generateCmdButton->Render());
        return window(text("curlsmith"), vbox(mainElements)) | center;
    });
}

void AppInterface::run() const {
    auto screen = ScreenInteractive::TerminalOutput();
    screen.TrackMouse(false);
    screen.Loop(root);
}
