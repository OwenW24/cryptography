#include "DHKE.hpp"

int main()
{
    DHKE alice;
    DHKE bob(1);

    // pair<int, int> alice_param = alice.get_domain_parameters();
    // pair<int, int> bob_param = bob.get_domain_parameters();

    // cout << alice_param.first << " " << alice_param.second << endl;
    // cout << bob_param.first << " " << bob_param.second << endl;


    // cout << alice.k_pub << endl;
    // cout << bob.k_pub << endl;

    alice.key_exchange(bob);

    // alice_param = alice.get_domain_parameters();
    // bob_param = bob.get_domain_parameters();

    // cout << alice_param.first << " " << alice_param.second << endl;
    // cout << bob_param.first << " " << bob_param.second << endl;
    
    // cout << alice.k_pub << endl;
    // cout << bob.k_pub << endl;

    cout << "--------" << endl;
    cout << "shared key:" << endl;

    cout << alice.get_k_shared() << endl;
    cout << bob.get_k_shared() << endl;

    return 0;
}