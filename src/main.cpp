#include <iostream>
#include "../inc/AppInterface.hpp"

int main(int ac, char **av) {
    if (ac != 1) {
        std::cout << "curlsmith: invalid number of arguments" << std::endl;
        std::exit(1);
    }
    const auto appUI = AppInterface();
    appUI.run();
    return 0;
}
