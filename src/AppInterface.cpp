#include "../inc/AppInterface.hpp"
#include "../inc/HttpMethod.hpp"
#include "../inc/curlsmith.hpp"
#include "../inc/CommandBuilder.hpp"

void AppInterface::initChildren() {
    urlInput = Input(&urlInputValue, "Type here...");

    methodOptions = {
        "GET", "POST", "PUT", "DELETE", "PATCH", "HEAD", "OPTIONS"
    };
    methodRadiobox = Radiobox(&methodOptions, &methodSelected);

    requestBody = Input(&requestBodyValue, "Type here...");

    generateCmdButton = Button("Generate", [] {
        /**/
    });

    generateCmdButton = CatchEvent(generateCmdButton, [this](Event const &event) {
        if (event == Event::Return) {
            generatedCommand = CommandBuilder::buildCurlCmd(
                static_cast<HttpMethod>(methodSelected),
                urlInputValue,
                requestBodyValue,
                headerData
            );
            return true;
        }
        return false;
    });

    headersContainer = ftxui::Container::Vertical({});

    addHeaderButton = Button("Add header", [this] {
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

std::vector<Element> AppInterface::renderMainElements(const std::vector<Element> &headerElements) const {
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

void AppInterface::renderRequestBodyField(std::vector<Element> &mainElements) const {
    if (isBodyInMethod(static_cast<HttpMethod>(methodSelected))) {
        mainElements.push_back(hbox({
            text("Request body"),
            filler()
        }));
        mainElements.push_back(requestBody->Render());
        mainElements.push_back(separator());
    }
}

std::vector<Element> AppInterface::renderGeneratedCommand() const {
    const auto lines = splitLines(generatedCommand);
    std::vector<Element> lineElements;
    for (const auto &line: lines) {
        lineElements.push_back(text(line));
    }
    return lineElements;
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
        if (!generatedCommand.empty()) {
            const auto lineElements = renderGeneratedCommand();
            mainElements.push_back(
                vbox(lineElements) | border | size(ftxui::HEIGHT, ftxui::LESS_THAN, 10)
            );
        }
        return window(text("curlsmith"), vbox(mainElements)) | center;
    });
}

void AppInterface::run() const {
    auto screen = ScreenInteractive::TerminalOutput();
    screen.TrackMouse(false);
    screen.Loop(root);
}
