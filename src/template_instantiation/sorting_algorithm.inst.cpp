/**
 * @file       sorting_algorithm.inst.cpp
 * @brief
 * @date       2020-09-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#include "template_instantiation/sorting_algorithm.inst.hpp"

template void std::sort(Iter first, Iter last, BinaryPredict cmp);
template void std::stable_sort(Iter first, Iter last, BinaryPredict cmp);

template void kerbal::algorithm::bubble_sort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::selection_sort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::heap_sort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::merge_sort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::inplace_merge_sort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::stable_sort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::insertion_sort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::directly_insertion_sort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::quick_sort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::nonrecursive_qsort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::intro_sort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::nonrecursive_intro_sort(Iter first, Iter last, BinaryPredict cmp);

void shell_sort_hibbard_sequence_wrapper(Iter first, Iter last, BinaryPredict cmp)
{
	typedef typename kerbal::iterator::iterator_traits<Iter>::difference_type difference_type;
	kerbal::algorithm::shell_sort(first, last, cmp, kerbal::algorithm::shell_sort_hibbard_policy<difference_type>());
}

void shell_sort_minimun_limit_hibbard_sequence_wrapper(Iter first, Iter last, BinaryPredict cmp)
{
	typedef typename kerbal::iterator::iterator_traits<Iter>::difference_type difference_type;
	kerbal::algorithm::shell_sort(first, last, cmp, kerbal::algorithm::shell_sort_minimun_limit_hibbard_policy<difference_type>());
}

void shell_sort_reduce_by_half_wrapper(Iter first, Iter last, BinaryPredict cmp)
{
	typedef typename kerbal::iterator::iterator_traits<Iter>::difference_type difference_type;
	kerbal::algorithm::shell_sort(first, last, cmp, kerbal::algorithm::shell_sort_reduce_by_half_policy<difference_type>());
}

void shell_sort_q_wrapper(Iter first, Iter last, BinaryPredict cmp)
{
	typedef typename kerbal::iterator::iterator_traits<Iter>::difference_type difference_type;
	kerbal::algorithm::shell_sort(first, last, cmp, kerbal::algorithm::shell_sort_q_policy<difference_type>());
}

template void boost::sort::flat_stable_sort(Iter first, Iter last, BinaryPredict cmp);
template void boost::sort::pdqsort(Iter first, Iter last, BinaryPredict cmp);
template void boost::sort::sample_sort(Iter first, Iter last, BinaryPredict cmp);
template void boost::sort::spinsort(Iter first, Iter last, BinaryPredict cmp);

template void gfx::timsort(Iter first, Iter last, BinaryPredict cmp);