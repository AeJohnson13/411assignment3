// inversions.hpp
// Alex E. Johnson

// For CS 411 Fall 2025
// Used in assignment 3, Exercise B
// There is no associated source file
// Based on merge_sort.cpp / By Glenn G. Chappell
#ifndef FILE_INVERSIONS_HPP_INCLUDED
#define FILE_INVERSIONS_HPP_INCLUDED

#include <vector>
// for std::vector
#include <cstddef>
// for std::size_t
#include <utility>
// for std::move
#include <iterator>
// for std::begin
// for std::end
// for std::distance
// for std::next
// for std::iterator_traits
#include <algorithm>
// for std::move - the one wiht three parameter

template <typename RAIter>
size_t inversions(RAIter first, RAIter last);

// Merge two halves of a sequence, each sorted, into a single sorted
// sequence in the same location. Merge is done in a stable manner. Tracks and
// returns the number of inversions done
// Requirements on Types:
//     FDIter is a forward iterator type.
//     The value type of FDIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, middle) and [middle, last) are valid ranges, each sorted
//      by <.
// stableCount
template <typename FDIter>
size_t stableCount(FDIter first, FDIter middle, FDIter last)
{
    std::size_t swaps = 0;
    // Get type of what iterators point to
    using Value = typename std::iterator_traits<FDIter>::value_type;
    std::vector<Value> buffer(distance(first, last));
    // Buffer for temporary copy of data
    auto in1 = first;              // Read location in 1st half
    auto in2 = middle;             // Read location in 2nd half
    auto out = std::begin(buffer); // Write location in buffer
    auto dist = std::distance(in1, in2);

    // Merge two sorted lists into a single list in buff.
    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1)
        { // Must do comparison this way, to be stable.
            *out++ = std::move(*in2++);
            swaps += dist;
        }
        else
        {
            *out++ = std::move(*in1++);
            dist--;
        }
    }

    // Move remainder of original sequence to buffer.
    // Only one of the following two calls will do anything, since the
    //  other is given an empty source range.
    // NOTE. This is the 3-parameter version of std::move (the "move"
    //  version of std::copy, declared in <algorithm>), not the
    //  1-parameter version (casts to an Rvalue, declared in <utility>).
    std::move(in1, middle, out);
    std::move(in2, last, out);

    // Move buffer contents back to original sequence location.
    std::move(std::begin(buffer), std::end(buffer), first);
    return swaps;
}

// mergeCount
// Sort a range using Merge Sort. Tracks and returns
// the number of inversions done in all recursive calls
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
    auto size = std::distance(first, last);

    // BASE CASE

    if (size <= 1)
        return 0;

    // RECURSIVE CASE

    // Create iterator to middle of range
    auto middle = std::next(first, size / 2);

    // Recursively sort the two lists
    std::size_t count1 = mergeCount(first, middle);
    std::size_t count2 = mergeCount(middle, last);

    // And merge them
    return stableCount(first, middle, last) + count1 + count2;
}

template <typename RAIter>
size_t inversions(RAIter first, RAIter last)
{
    return mergeCount(first, last);
}

#endif // #ifndef FILE_INVERSIONS_HPP_INCLUDED