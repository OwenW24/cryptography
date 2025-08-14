#include "DHKE.hpp"

void DHKE::choose_p(int t)
{
    srand(time(0)+t);
    p = rand() % 2048;
}

void DHKE::choose_alpha(int t)
{
    srand(time(0)+t);
    alpha = rand() % (Primes[p] - 1);
}

void DHKE::choose_k_priv()
{
    srand(time(0));
    k_priv = rand() % (Primes[p] - 1);
}

void DHKE::compute_k_pub()
{
    k_pub = fast_exp::exp(alpha, k_priv, p);
}

void DHKE::compute_k_shared(int other_k_pub)
{
    k_shared = fast_exp::exp(other_k_pub, k_priv, p);
}

void DHKE::gen_domain_parameters(int t)
{
    choose_p(t);
    choose_alpha(t);
}

std::pair<int, int> DHKE::get_domain_parameters()
{
    return {Primes[p], alpha};
}

void DHKE::key_exchange(DHKE other)
{

    other.p = this->p;
    other.alpha = this->alpha;  // not that clean
    
    // this->compute_k_shared(other.k_pub);
    // other.compute_k_shared(this->k_pub);  // clean
}

int DHKE::get_k_shared()
{
    return k_shared;
}

DHKE::DHKE()
{
    gen_domain_parameters(0);
}

DHKE::DHKE(int t)
{
    gen_domain_parameters(t);
}
