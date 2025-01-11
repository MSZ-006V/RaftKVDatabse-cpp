#include <iostream>
#include <boost/version.hpp>
#include <boost/config.hpp>

int main() {
    std::cout << "Boost version: " 
              << BOOST_VERSION / 100000 << "."    // Major version
              << BOOST_VERSION / 100 % 1000 << "." // Minor version
              << BOOST_VERSION % 100               // Patch version
              << std::endl;

    std::cout << "Boost platform: " << BOOST_PLATFORM << std::endl;
    std::cout << "Boost compiler: " << BOOST_COMPILER << std::endl;
    std::cout << "Boost standard library: " << BOOST_STDLIB << std::endl;

    return 0;
}
