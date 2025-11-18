#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <memory>
#include <vector>
#include <string>

class App {

public:
    App();
    void run();

private:
    /* root component */
    ftxui::Component    root;
    ftxui::Component    generateCmdButton;

    /* headers */
    struct HeaderData {
        std::string         key;
        std::string         value;
        ftxui::Component    keyInput;
        ftxui::Component    valueInput;
    };

    std::vector<std::shared_ptr<HeaderData> >   headerData;
    ftxui::Component                            headersContainer;
    ftxui::Component                            addHeaderButton;

    /* http method selection */
    int                         methodSelected;
    std::vector<std::string>    methodOptions;
    ftxui::Component            methodRadiobox;

    /* url input  */
    ftxui::Component            urlInput;
    std::string                 urlInputValue;
};
