#include "CapVector.h"
#include <iostream>

/**
 * Default constructor method.
 */

CapVector::CapVector() {

}

/**
 * Constructor method.
 * @input input - StateVector this object is based on
 */
CapVector::CapVector(StateVector input)
{
    int num = 0;
    int prev = input.getSV()->front();
    int i;
    for(i = 0; i < (*input.getSV()).size(); i++) {
        if((*input.getSV())[i] == 0) {
            continue;
        } else if((*input.getSV())[i] == prev) {
            num++;
        } else {
            if(prev != 0) {
                cv.push_back(num);
                blockValues.push_back((*input.getSV())[i-1]);
            }
            num = 1;
            prev = (*input.getSV())[i];
        }
    }
    cv.push_back(num);
    blockValues.push_back((*input.getSV())[i-1]);
}

/**
 * Deconstructor method.
 */
CapVector::~CapVector()
{
    //dtor
}

/**
 * Return the cv variable, a vector
 * @return &cv - vector holding the actual values of the object
 */
std::vector<int>* CapVector::getCV() {
    return &cv;
}

std::vector<int>* CapVector::getBlockValues() {
    return &blockValues;
}

/**
 * Prints the values of the cap vector.
 * @input none
 * @return none
 */
void CapVector::toString() {
    std::cout << "(";
    for(int i = 0; i < cv.size(); i++) {
        std::cout << cv[i] << ", ";
    }
    std::cout << ")\n";
    return;
}
