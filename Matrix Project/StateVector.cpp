/***
 * StateVector.cpp
 *
 * ITCS 6114 Project
 *
 * Description: Holds a StateVector for enumerating matrices over {0,1}.
 *  Consists of a single vector to hold values along with manipulation methods.
 *
 * @author Sean Fox
 * @date 11/30/17
 */
#include "StateVector.h"
#include <iostream>
#include <algorithm>

/**
 * Constructor method.
 * @input initVal - integer holding the value for each element of the vector
 * @input length - integer holding the size of the vector
 */
StateVector::StateVector(int initVal, int length)
{
    for(int i=0; i<length; i++) {
        sv.push_back(initVal);
    }
}

/**
 * Deconstructor method
 */
StateVector::~StateVector()
{
}

/**
 * Subtracts an assignment vector from a state vector
 * @input assignment - a StateVector object holding an assignment vector
 * @input cap - a vector of a CapVector object
 */
void StateVector::updateVector(StateVector assignment, std::vector<int> cap) {
    int measure[cap.size()];    //Holds the first available position of each block.
    int first;
    //Find the first available nonzero element
    for(int j = 0; j < sv.size(); j++) {
        if(sv[j] != 0) {
            first = j;
            break;
        }
    }
    //Determine the first index of each block in the cap vector
    for(int k = 0; k < cap.size(); k++) {
        if(k == 0) {
            measure[k] = first;
        } else {
            measure[k] = measure[k-1] + cap[k-1];// - 1;
        }
    }
    //Start subtracting the assignment vector from the state vector
    for(int i = 0; i < assignment.getSV()->size(); i++) {
        sv[measure[(*assignment.getSV())[i]]] -= 1;
        measure[(*assignment.getSV())[i]]++;
    }
    std::sort(sv.begin(), sv.end());
}

/**
 * Prints the values of the state vector.
 * @input none
 * @return none
 */
void StateVector::toString() {
    std::cout << "(";
    for(int i = 0; i < sv.size(); i++) {
        std::cout << sv[i] << ", ";
    }
    std::cout << ")\n";
    return;
}

/**
 * Return the sv variable, a vector
 * @return &sv - vector holding the actual values of the object
 */
std::vector<int>* StateVector::getSV() {
    return &sv;
}

/**
 * Compares the state vector to a second state vector to determine which is smaller
 * @input other - a second StateVector object
 * @return bool - true if this object is less than other, false otherwise.
 */
bool StateVector::isLessThan(StateVector other){
    std::vector<int> temp = (*other.getSV());
    //Compares the two StateVectors lexicographically
    for(int i = 0; i < sv.size(); i++) {
        if(temp[i] != sv[i]){
            if(temp[i] > sv[i]){
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}
