#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include "ciphers.hpp"
#include "attack.hpp"


int main(){

    std::string xs = "abcdefghijklmnopqrstuvwxyz";
    std::string ys = "";

    Shift sh(xs, 3);
    Affine af(xs, 5, 8);
    

    std::cout << sh.get_xs() << std::endl << sh.get_ys() << std::endl << std::endl;
    std::cout << af.get_xs() << std::endl << af.get_ys() << std::endl << std::endl;
    return 0;
}