/***
 * main.cpp
 *
 * ITCS 6114 Project
 *
 * Description: Implementation of the algorithm found in
 *   "Computation in the Enumeration of Integer Matrices" by Dr. Shanzhen Gao
 *   and Dr. Keh-Hsun Chen for their first problem.  Specifically, this program
 *   computes the number of mxn matrices over {0,1} whose rows each sum to a
 *   natural number s and whose columns each sum to a natural number t.  One
 *   additional constraint is that sm=tn must hold true.  All four values are
 *   determined by user input.
 *
 * @author Sean Fox
 * @date 11/30/17
 */
#include <iostream>
#include "StateVector.h"
#include "CapVector.h"
#include <cmath>
#include <map>
#include <utility>
#include <vector>

long long int calcMatrixNumber(int partSize, StateVector state, int rowNum);
bool isValid(StateVector assignment, CapVector cap);
int combinations(StateVector assignment, CapVector cap);
int factorial(int n);

/**
 * A struct designed to hold values to form a key for the
 * combinationTable map below.
 */
struct key {
    StateVector sv;
    int row;
    key(int row, StateVector sv) : row(row), sv(sv) {}
};

/**
 * A struct to overwrite the comparison operator to allow
 * combinationTable to use "key" objects as keys.
 */
struct keyCompare {
    bool operator( ) (key a, key b ) const
    {
        if(a.row>b.row){
            return true;
        }
        if(a.row == b.row){
            return a.sv.isLessThan(b.sv);
        }
        return false;
    }
};

/**
 * A global variable to hold state vectors at certain rows whose return values
 * are known.  Used to speed up the calculation process in calcMatrixNumber()
 */
std::map<key, long long int, keyCompare> combinationTable;

int main() {
    int m,n;    //Dimensions of the mxn matrix
    int rowSum,colSum;  //The summation values for the rows and columns
    bool flag;  //Boolean variable used to make sure  user input is valid

    std::cout << "Please enter the number of rows of your desired matrices: ";
    std::cin >> m;

    std::cout << "\nPlease enter the number of columns: ";
    std::cin >> n;

    std::cout << "\nPlease enter the integer that each row must sum to: ";
    std::cin >> rowSum;

    //Checking conditions: the sum of a row cannot be larger than the row size, and sm=tn.
    if(rowSum > n) {
        flag = false;
    }
    else if((rowSum*m)%n != 0) {
        flag = false;
    }
    else {
        flag = true;
    }

    //If rowSum was invalid, ask for a new value
    while(!flag) {
        std::cout << "\nThat value does not have a solution.  Please make sure the value is less than or equal to " << n << ": ";
        std::cin >> rowSum;
        if(rowSum <= n) {
            flag = true;
        } else if((rowSum*m)%n != 0) {
            flag = false;
        }
    }

    colSum = rowSum*m / n; //The Column sum is automatically determined

    std::cout << "\nYou wish to find the number of " << m << "x" << n << " matrices whose rows sum to " << rowSum << " and columns sum to " << colSum << std::endl << std::endl;

    StateVector state(colSum, n);   //Create state vector from the partition

    long long int num = calcMatrixNumber(rowSum, state, m);   //Calculate number of matrices meeting the entered conditions

    std::cout << "There are " << num << " possible " << m << "x" << n << " matrices whose rows sum to " << rowSum << " and columns sum to " << colSum << ".\n";
    return 0;
}

/**
 * Where the magic happens.  Calculates the number of mxn matrices whose rows sum to s
 * and whose columns sum to t.
 * @input partSize - integer holding the size of the partition
 * @input state - StateVector the holds the currently examined state vector
 * @input rowNum - integer that holds the number of rows remaining.  Used to keep track of
 *                 what row of the matrix the program is calculating
 * @return numSubMatrices - a long long int holding the number of constructible matrices
 */
long long int calcMatrixNumber(int partSize, StateVector state, int rowNum) {

    //Checks to see if tempKey (represents a combo of current state vector and row number)
    //is in combinationTable.  If so, return the stored value.
    key tempKey(rowNum, state);
    std::map<key, long long int, keyCompare>::iterator it = combinationTable.find(tempKey);
    if (it != combinationTable.end()) {
        return it->second;
    }

    long long int numSubMatrices = 0;   //Holds the number of constructible sub-matrices given the current state
    CapVector cap(state);               //Cap vector of the associated state vector
    StateVector assignment(0, partSize);    //Initializes an assignment vector
    StateVector second = state;         //A second state vector to represent an updated state after the effect of an assignment vector
    int capSize = cap.getCV()->size();      //Size of the cap vector
    int backEnd = assignment.getSV()->size()-1; //Index of last element of the assignment vector
    bool flag;      //Used to determine validity of assignment vector

    //Enumerates and examines all possible assignment vectors
    while((*assignment.getSV())[0] < capSize) {
        for(int j = assignment.getSV()->back(); j < capSize; j++){
            flag = isValid(assignment, cap);    //Determines if current assignment vector is valid
            if(flag) {
                if(rowNum == 1) {   //If this is the final row, there can only be one correct combination of assignments
                    return 1;
                }
                //Copies and updates the state vector
                second = state;
                second.updateVector(assignment, (*cap.getCV()));
                //Determine possible combinations of valid matrices that can be formed assuming this assignment vector is chose for this row
                numSubMatrices += (combinations(assignment, cap) * calcMatrixNumber(partSize, second, rowNum - 1));
            }
            (*assignment.getSV())[backEnd]++; //Update the assignment vector by increasing the last slot by one
        }
        //Adjust for overflow in the assignment vector
        for(int i = assignment.getSV()->size()-1; i > 0; i--){
            if((*assignment.getSV())[i] >= capSize) {
                (*assignment.getSV())[i-1]++;
            }
        }
        for(int i = 0; i < assignment.getSV()->size()-1; i++){
            if((*assignment.getSV())[i] != 0 && (*assignment.getSV())[i+1]>=capSize) {
                (*assignment.getSV())[i+1]=(*assignment.getSV())[i];
            }
        }
    }
    combinationTable[tempKey] = numSubMatrices; //Update the lookup table
    return numSubMatrices;
}

/**
 * Checks if the given assignment vector is valid according to the cap vector
 * @input assignment - StateVector object holding an assignment vector
 * @input cap - CapVector object holding a cap vector
 * @return bool value. true if assignment is valid, false otherwise
 */
bool isValid(StateVector assignment, CapVector cap) {
    int prev = (*assignment.getSV())[0];
    //Check non-decreasing nature of assignment vector
    for(int i = 0; i < assignment.getSV()->size(); i++) {
        if(prev > (*assignment.getSV())[i]) {
            return false;
        }
        prev = (*assignment.getSV())[i];
    }

    //Check to make sure no block is over-saturated
    std::vector<int> measure(cap.getCV()->size(),0);
    int temp;
    //Counts how many of each type of block appear in the assignment vector
    for(int j = 0; j < assignment.getSV()->size(); j++) {
        temp = (*assignment.getSV())[j];
        measure[temp]++;
    }
    //Makes sure the counts don't exceed the size of the block
    for(int k = 0; k < cap.getCV()->size(); k++) {
        if(measure[k] > (*cap.getCV())[k]) {
            return false;
        }
    }

    return true;
}

/**
 * Determines the number of ways the assignment vector can assign values
 * of the permutation into the state vector.
 * @input assignment - StateVector object holding an assignment vector
 * @input cap - CapVector object holding the associated cap vector
 * @return combination - an integer specifying the number of combinations possible
 */
int combinations(StateVector assignment, CapVector cap) {
    int combination=1;  //return value
    int num = 0;    //Temp variable to count size of contiguous blocks within assignment
    int prev = assignment.getSV()->front(); //The previous value found within assignment
    //Determines the size of contiguous sequences of number in assignment and uses that to calculate the combination value
    for(int i = 0; i < assignment.getSV()->size(); i++) {
        if((*assignment.getSV())[i] == prev) {  //Find size of current contiguous block
            num++;
        } else {    //Calculate combination; update bookkeeping variables
            combination *= (factorial((*cap.getCV())[prev])/(factorial(num)*factorial((*cap.getCV())[prev]-num)));
            num = 1;
            prev = (*assignment.getSV())[i];
        }
    }
    combination *= factorial((*cap.getCV())[prev]) / (factorial(num)*factorial((*cap.getCV())[prev]-num));
    return combination;
}

/**
 * Calculates the factorial of a nonnegative integer
 * @input n - a nonnegative integer
 * @return int - recursively determine factorial
 */
int factorial(int n) {
  if(n == 0){
    return 1;
  }
  if (n == 1) {
        return 1;
  } else {
        return n * factorial(n - 1);
  }
}
