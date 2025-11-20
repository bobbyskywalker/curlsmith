#pragma once

#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/node.hpp>
#include <memory>
#include <vector>
#include <string>

#include "ftxui/component/component.hpp"

using ftxui::Element;
using ftxui::Input;
using ftxui::Radiobox;
using ftxui::Button;
using ftxui::CatchEvent;
using ftxui::Event;
using ftxui::Renderer;
using ftxui::ScreenInteractive;
using ftxui::text;
using ftxui::hbox;
using ftxui::vbox;
using ftxui::separator;
using ftxui::filler;
using ftxui::window;
using ftxui::center;
using ftxui::size;
using ftxui::flex;
using ftxui::border;
using ftxui::WIDTH;
using ftxui::EQUAL;

class App {
public:
    App();

    void run() const;

private:
    /* render logic */
    void initChildren();

    void populateRoot();

    [[nodiscard]] std::vector<Element> renderHeaderElements() const;

    [[nodiscard]] std::vector<Element> renderMainElements(
        const std::vector<Element> &headerElements) const;

    void renderRequestBodyField(std::vector<Element> &mainElements) const;

    /* root component */
    ftxui::Component root;
    ftxui::Component generateCmdButton;

    /* headers */
    struct HeaderData {
        std::string key;
        std::string value;
        ftxui::Component keyInput;
        ftxui::Component valueInput;
    };

    std::vector<std::shared_ptr<HeaderData> > headerData;
    ftxui::Component headersContainer;
    ftxui::Component addHeaderButton;

    /* http method selection */
    int methodSelected;
    std::vector<std::string> methodOptions;
    ftxui::Component methodRadiobox;

    /* url input */
    ftxui::Component urlInput;
    std::string urlInputValue;

    /* body input */
    ftxui::Component requestBody;
    std::string requestBodyValue;
};
