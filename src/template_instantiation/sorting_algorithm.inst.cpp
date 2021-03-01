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


#include <parallel/algorithm>

void std_parallel_sort_wrapper(Iter first, Iter last, BinaryPredict cmp)
{
	std::__parallel::sort(first, last, cmp);
}

void std_parallel_stable_sort_wrapper(Iter first, Iter last, BinaryPredict cmp)
{
	std::__parallel::stable_sort(first, last, cmp);
}

#include <cstdlib>

void cqsort_wrapper(Iter first, Iter last, BinaryPredict cmp)
{
	typedef typename kerbal::iterator::iterator_traits<Iter>::value_type value_type;

	static BinaryPredict * cmp_sta(&cmp); // qsort can not receive lambda with capture list

	cmp_sta = &cmp; // reassign the cmp object

	qsort(&*first, last - first, sizeof(value_type), [](const void * a, const void * b) {
		value_type arg1 = *static_cast<const value_type*>(a);
		value_type arg2 = *static_cast<const value_type*>(b);

		if ((*cmp_sta)(arg1, arg2))
			return -1;
		if ((*cmp_sta)(arg2, arg1))
			return 1;
		return 0;
	});
}

template void kerbal::algorithm::bubble_sort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::selection_sort(Iter first, Iter last, BinaryPredict cmp);
template void kerbal::algorithm::heap_sort(Iter first, Iter last, BinaryPredict cmp);
void std_make_heap_then_sort_wrapper(Iter first, Iter last, BinaryPredict cmp)
{
	std::make_heap(first, last, cmp);
	std::sort_heap(first, last, cmp);
}

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


#include <kerbal/algorithm/sort/contiguously_radix_sort.hpp>

void radix_sort_wrapper(Iter first, Iter last, BinaryPredict)
{
	kerbal::algorithm::detail::contiguously_radix_sort(first, last, kerbal::type_traits::false_type(), std::forward_iterator_tag());
//	kerbal::algorithm::radix_sort(first, last);
}

#include <kerbal/ompalgo/sort/quick_sort.hpp>
#include <kerbal/ompalgo/sort/shell_sort.hpp>

void omp_quick_sort_wrapper(Iter first, Iter last, BinaryPredict cmp)
{
	::omp_set_num_threads(4);
	kerbal::ompalgo::quick_sort(first, last, cmp);
}

void omp_shell_sort_wrapper(Iter first, Iter last, BinaryPredict cmp)
{
	::omp_set_num_threads(4);
	kerbal::ompalgo::shell_sort(first, last, cmp);
}

#if BOOST_SORT_SUPPORT

template void boost::sort::block_indirect_sort(Iter first, Iter last, BinaryPredict cmp);
template void boost::sort::flat_stable_sort(Iter first, Iter last, BinaryPredict cmp);
template void boost::sort::heap_sort(Iter first, Iter last, BinaryPredict cmp);
template void boost::sort::pdqsort(Iter first, Iter last, BinaryPredict cmp);
template void boost::sort::sample_sort(Iter first, Iter last, BinaryPredict cmp);
template void boost::sort::spinsort(Iter first, Iter last, BinaryPredict cmp);

void boost_spreadsort_wrapper(Iter first, Iter last, BinaryPredict)
{
	boost::sort::spreadsort::spreadsort(first, last);
}

#include <boost/sort/parallel_stable_sort/parallel_stable_sort.hpp>

void boost_parallel_stable_sort_wrapper(Iter first, Iter last, BinaryPredict cmp)
{
	std::cout << omp_get_max_threads() << std::endl;
	boost::sort::parallel_stable_sort(first, last, cmp, omp_get_max_threads());
}

#else

#pragma message "boost::sort not support"

#endif

template void gfx::timsort(Iter first, Iter last, BinaryPredict cmp);

#include <omp.h>

//void parallel_merge(int threads_num, size_t per, int i, int j)
//{
//
//}

template <typename ForwardIterator, typename BinaryPredict>
void omp_inplace_merge(ForwardIterator first, ForwardIterator mid, ForwardIterator last, BinaryPredict cmp)
{
	typedef ForwardIterator iterator;
	typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

	difference_type left_len(kerbal::iterator::distance(first, mid));
	difference_type right_len(kerbal::iterator::distance(mid, last));

	if (left_len == 0) {
		return;
	}
	if (right_len == 0) {
		return;
	}
	if (left_len == 1 && right_len == 1) {
		if (cmp(*mid, *first)) { // *first > *mid
			kerbal::algorithm::iter_swap(first, mid);
		}
		return;
	}

	iterator lmid(first);
	iterator rmid(mid);

	if (left_len >= right_len) {
		lmid = kerbal::iterator::midden_iterator(first, mid);
		rmid = kerbal::algorithm::lower_bound(mid, last, *lmid, cmp);
	} else {
		rmid = kerbal::iterator::midden_iterator(mid, last);
		lmid = kerbal::algorithm::upper_bound(first, mid, *rmid, cmp);
	}
	mid = kerbal::algorithm::rotate(lmid, mid, rmid);

#	pragma omp parallel sections
	{
#		pragma omp section
		{
			kerbal::algorithm::inplace_merge(first, lmid, mid, cmp);
		}
#		pragma omp section
		{
			kerbal::algorithm::inplace_merge(mid, rmid, last, cmp);
		}
	}
}

#include <kerbal/algorithm/sort/msvc_like_intro_sort.hpp>

void freedom_implement(Iter first, Iter last, BinaryPredict cmp)
{
	kerbal::algorithm::msvc_like_intro_sort(first, last, cmp);
}

void multi_sort(Iter first, Iter last, BinaryPredict cmp)
{
	typedef Iter iterator;
	typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

	const difference_type dist(kerbal::iterator::distance(first, last));
	int threads_num = 0;
	difference_type per = 0;

#	pragma omp parallel
	{
#		pragma omp single
		{
			threads_num = omp_get_num_threads();
			per = (dist / threads_num) + (dist % threads_num != 0);
		}
#		pragma omp barrier

		int thrd_id = omp_get_thread_num();
		iterator section_first(kerbal::iterator::next(first, thrd_id * per));
		iterator section_last((thrd_id == threads_num - 1) ? last : kerbal::iterator::next(section_first, per));
		kerbal::algorithm::sort(section_first, section_last, cmp);

	} // omp parallel

	omp_set_nested(6);

	struct re_merge
	{
			iterator first;
			iterator last;
			int threads_num;
			difference_type per;
			BinaryPredict & cmp;

			void operator()(int i, int j)
			{
				if (j - i == 1 or j - i == 0) {
					return;
				}
				int h = (j - i) / 2;
				int m = i + h;

#				pragma omp parallel sections
				{
#					pragma omp section
					{
						(*this)(i, m);
					}
#					pragma omp section
					{
						(*this)(m, j);
					}
				}
				iterator section_first(kerbal::iterator::next(first, i * per));
				iterator section_mid(kerbal::iterator::next(section_first, h * per));
				iterator section_last((j == threads_num - 1) ? last : kerbal::iterator::next(section_mid, (j - m) * per));
				omp_inplace_merge(section_first, section_mid, section_last, cmp);
//				std::inplace_merge(section_first, section_mid, section_last, cmp);
			}
	};

	re_merge re{first, last, threads_num, per, cmp};


//	struct re_merge
//	{
//			iterator first;
//			iterator last;
//			int threads_num;
//			difference_type per;
//			BinaryPredict cmp;
//
//			void operator()(int i, int j)
//			{
//				if (j - i == 1 or j - i == 0) {
//					return;
//				}
//				int h = (j - i) / 2;
//				int m = i + h;
//
//#				pragma omp parallel sections
//				{
//#					pragma omp section
//					{
//						(*this)(i, m);
//					}
//#					pragma omp section
//					{
//						(*this)(m, j);
//					}
//				}
//				iterator section_first(kerbal::iterator::next(first, i * per));
//				iterator section_mid(kerbal::iterator::next(section_first, h * per));
//				iterator section_last((j == threads_num - 1) ? last : kerbal::iterator::next(section_mid, (j - m) * per));
////				kerbal::algorithm::inplace_merge(section_first, section_mid, section_last);
//				std::inplace_merge(section_first, section_mid, section_last, cmp);
//			}
//	};
//
//	re_merge re{first, last, threads_num, per, cmp};

	re(0, threads_num);
}