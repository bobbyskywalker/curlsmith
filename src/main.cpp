#include <iostream>
#include "../inc/App.hpp"

int main(int ac, char **av) {
    if (ac != 1) {
        std::cout << "curlsmith: invalid number of arguments" << std::endl;
        std::exit(1);
    }
    App app = App();
    app.run();
    return (0);
}
