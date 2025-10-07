// inversions.hpp
// Alex E. Johnson

// For CS 411 Fall 2025
// Used in assignment 3, Exercise B
// There is no associated source file
// Based on merge_sort.cpp / By Glenn G. Chappell
#ifndef FILE_INVERSIONS_HPP_INCLUDED
#define FILE_INVERSIONS_HPP_INCLUDED

#include<vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include<utility>
using std::move;
#include <iterator>
using std::begin;
using std::end;
using std::distance;
using std::next;
using std::iterator_traits;
#include <algorithm>
using std::move;
using std::swap;
#include <iostream>
using std::cout;
using std::endl;

template<typename RAIter>
size_t inversions(RAIter first, RAIter last);

template <typename FDIter>
size_t stableCount(FDIter first, FDIter middle, FDIter last)
{
    size_t swaps = 0;
    // Get type of what iterators point to
    using Value = typename iterator_traits<FDIter>::value_type;
    vector<Value> buffer(distance(first, last));
                               // Buffer for temporary copy of data
    auto in1 = first;          // Read location in 1st half
    auto in2 = middle;         // Read location in 2nd half
    auto out = begin(buffer);  // Write location in buffer

    // Merge two sorted lists into a single list in buff.
    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1){  // Must do comparison this way, to be stable.
            swaps += distance(in1, in2);
            *out++ = std::move(*in2++);
        }
        else{
            *out++ = std::move(*in1++);
        }
    }

    // Move remainder of original sequence to buffer.
    // Only one of the following two calls will do anything, since the
    //  other is given an empty source range.
    // NOTE. This is the 3-parameter version of std::move (the "move"
    //  version of std::copy, declared in <algorithm>), not the
    //  1-parameter version (casts to an Rvalue, declared in <utility>).
    move(in1, middle, out);
    move(in2, last, out);

    // Move buffer contents back to original sequence location.
    move(begin(buffer), end(buffer), first);
    cout << swaps << endl;
    return swaps;
}


// mergeSort
// Sort a range using Merge Sort.
// Recursive.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     The value type of FDIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, last) is a valid range.
template <typename FDIter>
size_t mergeCount(FDIter first, FDIter last)
{
    // Compute size of range
    auto size = distance(first, last);

    // BASE CASE

    if (size <= 1)
        return 0;

    // RECURSIVE CASE

    // Create iterator to middle of range
    auto middle = next(first, size/2);

    // Recursively sort the two lists
    size_t count1 = mergeCount(first, middle);
    size_t count2 = mergeCount(middle, last);

    // And merge them
    return stableCount(first, middle, last) + count1 + count2;
}

template<typename RAIter>
size_t inversions(RAIter first, RAIter last){
    size_t a = mergeCount(first,last);
    return a;
}



#endif // #ifndef FILE_INVERSIONS_HPP_INCLUDED