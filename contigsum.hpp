// contigsum.hpp
// Alex E. Johnson

// For CS 411 Fall 2025
// Used in assignment 3, Exercise A
// There is no associated source file
#ifndef FILE_CONTIGSUM_HPP_INCLUDED
#define FILE_CONTIGSUM_HPP_INCLUDED

#include <iterator>
#include <algorithm>
using std::max;
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;


template <typename RAIter>
vector<int> contigSumRecur( RAIter first, RAIter last){
    auto length = last - first;
    // Base Case
    
    if(length == 1){
        return {*first, *first, *first, *first};
   
    }
    // Recursive Case
    else{
        auto middle = first + length/2;
        auto left = contigSumRecur(first, middle);
        auto right = contigSumRecur(middle, last); 


        //maximum subarray 
        int a = max({left[0],right[0],(left[2]+right[1])});
        //maximum left aligned array
        int b = max({left[1],left[3]+right[1]});
        //maximum right aligned array
        int c = max({right[2],right[3]+left[2]});
        //total sum
        int d = left[3] + right[3];
        
        return {a, b, c, d};
    }
}

template <typename RAIter>
int contigSum(RAIter first, RAIter last)
{
    if(first == last)
        return 0;
    
    auto result = contigSumRecur(first, last);
    return max(0, result[0]);
}



#endif // #ifndef FILE_CONTIGSUM_HPP_INCLUDED