#ifndef PRIMEFACTORIZER_H
#define PRIMEFACTORIZER_H
#include <vector>


class PrimeFactorizer
{
    public:
        PrimeFactorizer();
        virtual ~PrimeFactorizer();
        void factorize(int num);
        bool isPrime(int num);
    protected:
    private:
        std::vector<int> primes;
};

#endif // PRIMEFACTORIZER_H
