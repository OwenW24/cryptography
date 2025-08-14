#include "DHKE.hpp"

void DHKE::choose_p()
{
    srand(time(0) + seed);
    p = rand() % 2048;
}

void DHKE::choose_alpha()
{
    srand(time(0) + seed);
    alpha = rand() % (Primes[p] - 1);
}

void DHKE::choose_k_priv()
{
    srand(time(0) + seed);
    k_priv = (rand() % (Primes[p] - 3)) + 2;
}

void DHKE::compute_k_pub()
{
    k_pub = fast_exp::exp(alpha, k_priv, p);
}

void DHKE::compute_k_shared(int other_k_pub)
{
    k_shared = fast_exp::exp(other_k_pub, k_priv, p);
}

void DHKE::gen_domain_parameters()
{
    choose_p();
    choose_alpha();
}

std::pair<int, int> DHKE::get_domain_parameters()
{
    return {Primes[p], alpha};
}

void DHKE::key_exchange(DHKE &other)
{

    other.p = this->p;
    other.alpha = this->alpha;  // not that clean

    other.choose_k_priv();
    other.compute_k_pub();

    this->compute_k_shared(other.k_pub);
    other.compute_k_shared(this->k_pub);  // clean


}

int DHKE::get_k_shared()
{
    return k_shared;
}

DHKE::DHKE()
{
    seed = 0;
    gen_domain_parameters();
    choose_k_priv();
    compute_k_pub();
}

DHKE::DHKE(int t)
{
    seed = t;
    gen_domain_parameters();
    choose_k_priv();
    compute_k_pub();
}


