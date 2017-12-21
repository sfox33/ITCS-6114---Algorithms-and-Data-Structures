'''
Homework4.py
ITCS 6114 Homework 4
Purpose - Examines a set of the first n natural numbers and returns all 
    Alternating Sorts or Double Alternating Sorts, determined by the user,
    and the number of (Double) Alternating Sorts that can be found.
Author - Sean Fox
Date - 10/22/17
'''
import time;
from itertools import permutations

count = 0;  #Global variable holding the number of alternating sorts found.

def main():
    n=int(input("Enter your value for n: "));   #Prompt the user for set size and type of sort
    type = int(input("Enter 1 to find Alternating Sorts or 2 to find Double Alternating Sorts: "));
    preSort = list(range(1,n+1));
    global count;
    
    #Adjust the type variable if it is not 1 or 2.  Default to 1.
    if(type != 1 and type != 2):
        print("The input type is not a recognized form.  Defaulting to Alternating Sort.");
        type = 1;
        
    #Determine all permutations of the first n natural numbers; print all (double) alternating sorts
    permute2(preSort, 0, len(preSort), type);
    
    #Print the number of accepted sorts.
    if(type == 1):
        print("There are ", count, " alternating sorts of length ", n, ".");
    else:
        print("There are ", count, " double alternating sorts of length ", n, ".");

    return;
  
'''
 Determines all permutations of the input list
 list - Holds the original set to be permuted
 start, end - Index variables to help traverse list
 type - Integer holding 1 or 2.  Used to determine which 
    alternating sort needs to be foun.
'''
def permute2(list, start, end, type):
    global count;

    #If a list has been permuted, determine if it is an alternating sort
    if (start == end-1):
        if(type == 1):
            result = detAltSort(list);
        else:
            result = detDoubleSort(list);
        #If the list is a sort, print it and increase count
        if(result):
            print("\t", list);
            count += 1;
        return;
    else:
        i=start;
        #Recursively determine a new permutation
        while (i < end):
            temp = list[start];
            list[start]=list[i];
            list[i]=temp;
            
            #Skip the rest of the permutation if the list cannot become an alternating sort
            if((i > 1 and (list[0] < list[1] or list[0] != max)) or i <= 1): 
                permute2(list, start+1, end, type);
            
            temp = list[start];
            list[start]=list[i];
            list[i]=temp;
            i += 1;
    return;

'''
 Determines if the input list is an alternating sort.
 preSort - The list to be examined
'''
def detAltSort(preSort):
    #Returns true if preSort only holds one number
    if(len(preSort) == 1):
        return True;
    i=0;
    flag = True;
    #Traverses the list
    while(i < len(preSort)-1):
        #If the value at i violates the alternating sort pattern, set flag to false
        if((i%2 == 0 and preSort[i] >= preSort[i+1]) or (i%2 == 1 and preSort[i] <= preSort[i+1])):
            flag = False;
            break;
        i += 1;
    return flag;

'''
 Determines if the input list is an alternating sort.
 preSort - The list to be examined
'''
def detDoubleSort(preSort):
    #If the list contains only one value, return true
    if(len(preSort) == 1):
        return True;
    i=0;
    flag = True;
    #Traverse the list
    while(i < len(preSort)-1):
        #If the value at i violates the double alternating sort pattern, set flag to false
        if(((i%4 == 0 or i%4 == 1) and preSort[i] >= preSort[i+1]) or ((i%4 == 2 or i%4 == 3) and preSort[i] <= preSort[i+1])):
            flag = False;
            break;
        i += 1;
    return flag;
    
if __name__ == '__main__':
    main()