/**
 * @file       sorting_algorithm.inst.hpp
 * @brief
 * @date       2020-09-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_SORTING_ALGORITHM_INST_HPP
#define VISUAL_SORT_SORTING_ALGORITHM_INST_HPP

#include <kerbal/algorithm/sort.hpp>
#include <algorithm>

#ifdef _MSC_VER
#	include <ciso646>
#endif

#if BOOST_SORT_SUPPORT

#include <boost/sort/block_indirect_sort/block_indirect_sort.hpp>
#include <boost/sort/flat_stable_sort/flat_stable_sort.hpp>
#include <boost/sort/heap_sort/heap_sort.hpp>
#include <boost/sort/pdqsort/pdqsort.hpp>
#include <boost/sort/sample_sort/sample_sort.hpp>
#include <boost/sort/spinsort/spinsort.hpp>
#include <boost/sort/spreadsort/integer_sort.hpp>
#include <boost/sort/spreadsort/spreadsort.hpp>

#endif

#include "gfx/timsort.hpp"


#include "sorting_algorithm_united_interface.hpp"

extern template void std::sort(Iter first, Iter last, BinaryPredict cmp);
extern template void std::stable_sort(Iter first, Iter last, BinaryPredict cmp);
void std_parallel_sort_wrapper(Iter first, Iter last, BinaryPredict cmp);
void std_parallel_stable_sort_wrapper(Iter first, Iter last, BinaryPredict cmp);
void cqsort_wrapper(Iter first, Iter last, BinaryPredict cmp);

extern template void kerbal::algorithm::bubble_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void kerbal::algorithm::selection_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void kerbal::algorithm::heap_sort(Iter first, Iter last, BinaryPredict cmp);
void std_make_heap_then_sort_wrapper(Iter first, Iter last, BinaryPredict cmp);

extern template void kerbal::algorithm::merge_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void kerbal::algorithm::inplace_merge_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void kerbal::algorithm::stable_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void kerbal::algorithm::insertion_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void kerbal::algorithm::directly_insertion_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void kerbal::algorithm::quick_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void kerbal::algorithm::nonrecursive_qsort(Iter first, Iter last, BinaryPredict cmp);
extern template void kerbal::algorithm::intro_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void kerbal::algorithm::nonrecursive_intro_sort(Iter first, Iter last, BinaryPredict cmp);

void shell_sort_hibbard_sequence_wrapper(Iter first, Iter last, BinaryPredict cmp);
void shell_sort_minimun_limit_hibbard_sequence_wrapper(Iter first, Iter last, BinaryPredict cmp);
void shell_sort_reduce_by_half_wrapper(Iter first, Iter last, BinaryPredict cmp);
void shell_sort_q_wrapper(Iter first, Iter last, BinaryPredict cmp);

void radix_sort_wrapper(Iter first, Iter last, BinaryPredict cmp);

void omp_quick_sort_wrapper(Iter first, Iter last, BinaryPredict cmp);
void omp_shell_sort_wrapper(Iter first, Iter last, BinaryPredict cmp);

#if BOOST_SORT_SUPPORT

extern template void boost::sort::block_indirect_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void boost::sort::flat_stable_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void boost::sort::heap_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void boost::sort::pdqsort(Iter first, Iter last, BinaryPredict cmp);
extern template void boost::sort::sample_sort(Iter first, Iter last, BinaryPredict cmp);
extern template void boost::sort::spinsort(Iter first, Iter last, BinaryPredict cmp);

void boost_spreadsort_wrapper(Iter first, Iter last, BinaryPredict);
void boost_parallel_stable_sort_wrapper(Iter first, Iter last, BinaryPredict cmp);

#endif

extern template void gfx::timsort(Iter first, Iter last, BinaryPredict cmp);

void freedom_implement(Iter first, Iter last, BinaryPredict cmp);


#endif // VISUAL_SORT_SORTING_ALGORITHM_INST_HPP
