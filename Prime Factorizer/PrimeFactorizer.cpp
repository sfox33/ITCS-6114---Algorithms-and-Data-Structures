#include "PrimeFactorizer.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <tgmath.h>

PrimeFactorizer::PrimeFactorizer()
{
    //Creating a vector that holds all known primes less than 100
    int temp[25] = {2,3,5,7,11,13,17,19,
                    23,29,31,37,41,43,47,
                    53,59,61,67,71,73,79,
                    83,89,97};
    primes.insert(primes.end(),temp,temp+25);
}

PrimeFactorizer::~PrimeFactorizer()
{

}

/**
* Prints out all unique primes that divide the input.
* @input num - integer that needs to be factored
*/
void PrimeFactorizer::factorize(int num){
    int goal = floor(sqrt(num));
    int newNum = num;
    int number = 0;
    int frontier;
    std::cout << "The prime factors of " << num << " are:\n\t";
    //Finds all primes that divide newNum
    for(int i = 0; i < primes.size(); i++){
        //Prints out prime if it divides newNum
        if(newNum% primes[i] == 0){
            std::cout << primes[i] << ", ";
            newNum /= primes[i];
            number++;
        }
        while (newNum % primes[i] == 0){    //Keeps dividing newNum until it is no longer divisible by the current prime
            newNum /= primes[i];
        }
    }

    frontier = primes.back() + 1;
    //Activates if newNum is still divisible by a prime not contained in the primes[] vector
    while(newNum != 1){
        while(!isPrime(frontier)){
            frontier++;
        }
        while(newNum % primes.back() == 0){
            std::cout << primes.back() << ", ";
            newNum /= primes.back();
            number++;
        }
        frontier++;
    }
    std::cout << "\nIt has " << number << " different prime factors.";
}

/**
* Returns true if its input is a prime number.
* @input num - integer whose primality is to be determined.
*/
bool PrimeFactorizer::isPrime(int num){
    int limit = ceil(sqrt(num));
    if(std::find(primes.begin(),primes.end(),num) != primes.end()){
        return true;
    }
    for(int i = 0; primes[i] <= limit; i++){
        if(num % primes[i] == 0){
            return false;
        }
    }
    primes.push_back(num);
    return true;
}
