#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include "ciphers.hpp"
#include "attack.hpp"



int main(){

    std::string xs = "abcdefghijklmnopqrstuvwxyz";
    std::string ys = "JGRMQOYGHMVBJWRWQFPWHGFFDQGFPFZRKBEEBJIZQQOCIBZKLFAFGQVFZFWWEOGWOPFGFHWOLPHLRLOLFDMFGQWBLWBWQOLKFWBYLBLYLFSFLJGRMQBOLWJVFPFWQVHQWFFPQOQVFPQOCFPOGFWFJIGFQVHLHLROQVFGWJVFPFOLFHGQVQVFILEOGQILHQFQGIQVVOSFAFGBWQVHQWIJVWJVFPFWHGFIWIHZZRQGBABHZQOCGFHX";
    std::string ys1 =  "lrvmnir bpr sumvbwvr jx bpr lmiwv yjeryrkbi jx qmbm wi bpr xjvni mkd ymibrut jx irhx wi bpr riirkvr jx ymbinlmtmipw utn qmumbr dj w ipmhh but bj rhnvwdmbr bpr yjeryrkbi jx qmbm mvvjudwko bj yt wkbrusurbmbwjk lmird jk xjubt trmui jx ibndt";
    Shift sh(xs, 3);
    Affine af(xs, 5, 8);

    std::cout << sh.get_xs() << std::endl << sh.get_ys() << std::endl << std::endl;
    std::cout << af.get_xs() << std::endl << af.get_ys() << std::endl << std::endl;

    Freq fq(ys1);
    fq.adjust();

    return 0;
}