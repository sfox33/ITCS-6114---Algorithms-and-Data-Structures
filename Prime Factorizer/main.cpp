#include <iostream>
#include <string>
#include <sstream>
#include "PrimeFactorizer.h"

void findMaxArray(int alpha[], int beta[], int arraySize);
void findPrimes(int low, int high, PrimeFactorizer factorizer);
bool isPrime(int num);

int main()
{
    PrimeFactorizer factorizer;
    int num,arrayNums,arraySize,i,low,high;
    std::string input;
    std::stringstream stream;

    //Start problem 3: Enumerate all primes between two positive integers.
    std::cout << "Problem 3: Enter two positive integers in increasing order separated by a space: ";
    getline(std::cin, input);

    stream << input;
    stream >> low;
    stream >> high;

    //Ensure that low and high are both positive and in the proper order.
    if(low < 0){
        low *= -1;
    }

    if(high < 0){
        high *= -1;
    }

    if(low > high){
        int temp = low;
        low  = high;
        high = temp;
    }

    findPrimes(low, high, factorizer);

    //Problem 4: Print out the larger element of each component of two arrays
    std::cout << "\nProblem 4: Comparing arrays.  Enter the size of the arrays: ";
    std::cin >> arraySize;
    std::cin.ignore();

    int alpha[arraySize];
    int beta[arraySize];

    std::cout << "Enter in the values for the first array separated by a space:\n";
    getline(std::cin, input);

    stream.clear();
    stream.str(std::string());
    stream << input;
    for(i = 0; i < arraySize; i++){
        stream >> alpha[i];
    }

    std::cout << "\nEnter in the values for the second array separated by a space:\n";
    getline(std::cin, input);

    stream.clear();
    stream.str(std::string());
    stream << input;
    for(i = 0; i < arraySize; i++){
        stream >> beta[i];
    }

    findMaxArray(alpha, beta, arraySize);

    //Problem 5: Find the prime factorization of a positive number.
    std::cout << "\nProblem 5: Factorizing integers.  Enter the number you would like to factorize: ";
    std::cin >> num;
    factorizer.factorize(num);
    return 0;
}
/**
* Takes in two arrays of equal length and saves the greater value
* of the two arrays ith slot into a new array.
* @input alpha[] - the first array of integers
* @input beta[] - the second array of integers
* @input arraySize - the size of the two arrays
*/
void findMaxArray(int alpha[], int beta[], int arraySize){
    int gamma[arraySize];
    std::cout << "\nThe Maximum of the two Arrays:\n";
    for(int i = 0; i < arraySize; i++){
        gamma[i] = std::max(alpha[i],beta[i]);
        std::cout << gamma[i] << std::endl;
    }
}

/**
* Prints the primes that can be found between the two positive integer inputs.
* @input low - the lower bound of integers to be checked for primes
* @input high - the upper bound of integers to be checked for primes.
*/
void findPrimes(int low, int high, PrimeFactorizer factorizer){
    int number = low;
    int numPrimes = 0;
    std::cout << "The prime numbers between " << low << " and " << high << ":\n\t";
    //1 is not a prime number, so skip it if it's in the interval
    if(number == 1){
        number++;
    }
    //Check every integer in the interval [low,high] to see if it's a prime
    while(number <= high){
        if(factorizer.isPrime(number)){
            std::cout << number << ", ";
            numPrimes++;
        }
        number++;
    }
    std::cout << "\nThere are " << numPrimes << " primes." << std::endl;
}
