#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include "ciphers.hpp"
#include "attack.hpp"



int main(){

    std::string xs = "abcdefghijklmnopqrstuvwxyz";
    std::string ys = "JGRMQOYGHMVBJWRWQFPWHGFFDQGFPFZRKBEEBJIZQQOCIBZKLFAFGQVFZFWWEOGWOPFGFHWOLPHLRLOLFDMFGQWBLWBWQOLKFWBYLBLYLFSFLJGRMQBOLWJVFPFWQVHQWFFPQOQVFPQOCFPOGFWFJIGFQVHLHLROQVFGWJVFPFOLFHGQVQVFILEOGQILHQFQGIQVVOSFAFGBWQVHQWIJVWJVFPFWHGFIWIHZZRQGBABHZQOCGFHX";

    Shift sh(xs, 3);
    Affine af(xs, 5, 8);

    std::cout << sh.get_xs() << std::endl << sh.get_ys() << std::endl << std::endl;
    std::cout << af.get_xs() << std::endl << af.get_ys() << std::endl << std::endl;

    Freq fq(ys);
    std::cout << fq.get_ys() << std::endl << "spongebob" << std::endl << fq.get_xs() << std::endl << std::endl;


    return 0;
}