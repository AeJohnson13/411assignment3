// contigsum.hpp
// Alex E. Johnson

// For CS 411 Fall 2025
// Used in assignment 3, Exercise A
// There is no associated source file
#ifndef FILE_CONTIGSUM_HPP_INCLUDED
#define FILE_CONTIGSUM_HPP_INCLUDED

#include <algorithm>
//for std::max
#include <vector>
// for std::max({})
#include <array>
// for std::array

// contigSumRecur
// given a sequence of integers returns an array containing: 
// [0] A. The GCS of the sequence.
// [1] B. The greatest possible sum of a contiguous subsequence that includes the first value in the sequence, or zero if all such sums are negative.
// [2] C. The greatest possible sum of a contiguous subsequence that includes the last value in the sequence, or zero if all such sums are negative.
// [3] D. The sum of the entire sequence.

template <typename RAIter>
std::array<int, 4> contigSumRecur(RAIter first, RAIter last)
{
    auto length = last - first;
    // Base Case
    if (length == 1)
    {
        auto val = *first;
        if (val > 0)
            return {val, val, val, val};
        else
            return {val, 0, 0, val};
    }
    // Recursive Case
    else
    {
        auto middle = first + length / 2;

        auto left = contigSumRecur(first, middle);
        auto right = contigSumRecur(middle, last);

        // maximum subarray
        int A =std::max({left[0], right[0], (left[2] + right[1])});

        // maximum left aligned array
        int B =std::max({left[1], left[3] + right[1], 0});

        // maximum right aligned array
        int C =std::max({right[2], right[3] + left[2], 0});

        // total sum
        int D = left[3] + right[3];

        return {A, B, C, D};
    }
}


// ContigSum
// wrapper function for contigSumRecur
// returns maximum contiguous sum
// of a given sequence
template <typename RAIter>
int contigSum(RAIter first, RAIter last)
{
    if (first == last)
        return 0;

    auto result = contigSumRecur(first, last);
    return std::max(0, result[0]);
}

#endif // #ifndef FILE_CONTIGSUM_HPP_INCLUDED