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


template<typename RAIter>
int contigSum(RAIter first, RAIter last);


template<typename RAIter>
int sumIter(RAIter first, RAIter last){
    int sum = 0;
    for(auto iter = first; iter != last; ++iter){
        sum += *iter;
    }
    return sum;
}


template<typename RAIter>
int contigSum(RAIter first, RAIter last){

//Base Case
if(first == last)
{
    return *first; 
}

//Recursive Case
RAIter middle = first-last/2;
int b = contigSum(first, middle);
int c = contigSum(middle, last);
int d = sumIter(first, last);

return std::max({b,c,(b+c)});
}





#endif //#ifndef FILE_CONTIGSUM_HPP_INCLUDED