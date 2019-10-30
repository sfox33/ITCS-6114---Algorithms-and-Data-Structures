/**
 *@author Sean Fox
 *@date 9-18-17
 *
 *Implements the Merge Sort, Quick Sort, and Euclidean algorithms.  Main
 *runs demos for each algorithm with randomly selected integers less than 100.
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <limits>

int* mergeSort(int* array, int length);
void quickSort(int* array, int length);
int euclid(int a, int b);

int main() {
    srand(time(NULL));
    int arraySize=10;
    int nums[arraySize];
    int gcd, a, b;
    for(int i = 0; i < arraySize; i++){
        nums[i]=rand()%100;
    }
    std::cout << "Merge Sort:\n" << "Original: ";
    for(int i = 0; i < arraySize; i++){
        std::cout << nums[i] << ", ";
    }
    std::cout << "\n" << "Sorted: ";
    mergeSort(nums, arraySize);
    for(int i = 0; i < arraySize; i++){
        std::cout << nums[i] << ", ";
    }
    std::cout << "\n";
    
    std::cout << "Quick Sort:\nOriginal: ";
    for(int i = 0; i < arraySize; i++){
        nums[i]=rand()%100;
    }
    for(int i = 0; i < arraySize; i++){
        std::cout << nums[i] << ", ";
    }
    std::cout << "\nSorted: ";
    quickSort(nums, arraySize);
    for(int i = 0; i < arraySize; i++){
        std::cout << nums[i] << ", ";
    }
    std::cout << "\n";
    
    gcd = euclid(24,60);
    std::cout << "gcd(24,60) = " << gcd << "\n";
    gcd = euclid(60,0);
    std::cout << "gcd(60,0) = " << gcd << "\n";
    gcd = euclid(0,0);
    std::cout << "gcd(0,0) = " << gcd << "\n";
    gcd = euclid(4,24);
    std::cout << "gcd(4,24) = " << gcd << "\n";
    a = rand()%100;
    b = rand()%100;
    gcd = euclid(a,b);
    std::cout << "gcd(" << a << "," << b << ") = " << gcd << "\n";
    a = rand()%100;
    b = rand()%100;
    gcd = euclid(a,b);
    std::cout << "gcd(" << a << "," << b << ") = " << gcd << "\n";
    a = rand()%100;
    b = rand()%100;
    gcd = euclid(a,b);
    std::cout << "gcd(" << a << "," << b << ") = " << gcd << "\n";
    return 0;
}

/* Performs the Merge Sort algorithm.
 * @param array - pointer to the array of integers that is to be sorted
 * @param length - integer that holds the length of the array
 */
int* mergeSort(int* array, int length) {
    int* first;     //Holds the sorted left half of array
    int* second;    //Holds the sorted right value of array
    int temp[length];   //Used to hold the merged subarrays
    int firstCount;     //Runs through first
    int secondCount;    //Runs through second

    if(length == 1){
        return array;
    }
    else{
        first = mergeSort(array, length/2); //Sorts through the left halt of array
        second = mergeSort(array + (length/2), length-(length/2)); //Sorts through the right half of array
        firstCount = 0;
        secondCount = 0;
        //Sorts through and merges first and second into one array
        for(int j = 0; j < length; j++){
            if(firstCount >= length/2){         //If first has been completely merged...
                temp[j]=second[secondCount];
                secondCount++;
            }
            else if(secondCount >= length-(length/2)){  //If second has been completely merged...
                temp[j]=first[firstCount];
                firstCount++;
            }
            else if(first[firstCount] <= second[secondCount]){  //If the next min value comes from first...
                temp[j]=first[firstCount];
                firstCount++;
            }
            else{       //If the next min value comes from second...
                temp[j]=second[secondCount];
                secondCount++;
            }
        }
        
        for(int j=0; j<length; j++){
            *(first+j)=temp[j];
        }
        
        return array;
    }
}

/* Performs the Quick Sort algorithm.
 * @param array - pointer to the array of integers that is to be sorted
 * @param length - integer that holds the length of the array
 */
void quickSort(int* array, int length) {
    int left = 1;   //The left most starting point to cycle through the array
    int right = length-1;   //The right most starting point to cycle through the array
    int pivot = array[0];   //Pivot value; contains the first array value by default
    int temp;
    
    while(left < right){
        while(left < length-1 && array[left] < pivot){   //Increase left until array[left] is greater than pivot
            left++;
        }
        while(right > 0 && array[right] >= pivot){  //Decrease right until array[right] is less than pivot
            right--;
        }
        if(left < right){   //Swap the array values at left and right 
            temp = array[left];
            array[left] = array[right];
            array[right] = temp;
        }
    }
    //If the array holds two values, swap the values if necessary
    if(length == 2 && array[right] < pivot){
        array[0] = array[right];
        array[right] = pivot;
    }
    if(length != 2){    //If array is greater than two swap pivot and right values
        array[0] = array[right];
        array[right] = pivot;
    }
    //Divide and conquer by quick sorting the sub arrays to the left and right of the pivot
    if(length > 1){
        if(right !=0){
            quickSort(array, right);
        }
        if(right < length-1){
            quickSort(&array[right+1], length-right-1);
        }
    }
}

/*
 * Performs the Euclidean algorithm on two nonnegative integers to find
 * their greatest common divisor.  If a negative integer is input or 
 * both inputs are zero, the maximum value of an integer is returned
 * to denote an error.
 * @param a - the first of two integers
 * @param b - the second of two integers
 */
int euclid(int a, int b){
    int temp;
    int last,r;
    r=-1;
    //Check to determine that both integers are not negative or simultaneously zero 
    if(a < 0 || b < 0 || (a == 0 && b == 0)){
        return std::numeric_limits<int>::max(); //Returns the maximimum integer value for an error
    }
    if(b > a){  //Makes sure that a is the maximum integer
        temp = a;
        a=b;
        b=temp;
    }
    //Keeps performing the division algorithm until a nonzero remainder is reached
    if(b != 0 && a%b == 0){
        return b;
    }
    while(r!=0){
        last = r;
        if(b==0){
            r=a;
        }
        else{
            r=a%b;
        }
        a=b;
        b=r;
    }
    
    return last;
}
