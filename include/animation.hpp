/**
 * @file       animation.hpp
 * @brief
 * @date       2020-04-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_ANIMATION_HPP
#define VISUAL_SORT_ANIMATION_HPP

#include "animation_base.hpp"

#include <kerbal/algorithm/sort.hpp>

class std_make_heap_then_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort(std::function<bool(const Ele&, const Ele&)>&& cmp) override
		{
			std::make_heap(this->v.begin(), this->v.end(), cmp);
			std::sort_heap(this->v.begin(), this->v.end(), cmp);
		}
};


#include <cstdlib>

template <typename Iterator, typename Compare>
void c_qsort_wrapper(Iterator first, Iterator last, Compare cmp)
{
	typedef typename kerbal::iterator::iterator_traits<Iterator>::value_type value_type;

	static Compare * cmp_sta(&cmp); // qsort can not receive lambda with capture list

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


class c_qsort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort(std::function<bool(const Ele&, const Ele&)>&& cmp) override
		{
			c_qsort_wrapper(this->v.begin(), this->v.end(), cmp);
		}
};


#include <kerbal/ompalgo/sort/quick_sort.hpp>

class kerbal_omp_quick_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort(std::function<bool(const Ele&, const Ele&)>&& cmp) override
		{
			::omp_set_num_threads(4);
			kerbal::ompalgo::quick_sort(this->v.begin(), this->v.end(), cmp);
		}
};


//#include <kerbal/ompalgo/sort/merge_sort.hpp>
//
//class kerbal_omp_merge_sort_animation: public animation_base
//{
//		using animation_base::animation_base;
//
//		virtual void sort(std::function<bool(const Ele&, const Ele&)>&& cmp) override
//		{
//			::omp_set_num_threads(4);
////#pragma omp parallel
////#pragma omp single
//			kerbal::ompalgo::merge_sort(this->v.begin(), this->v.end(), cmp);
//		}
//};

#include <kerbal/ompalgo/sort/shell_sort.hpp>

class kerbal_omp_shell_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort(std::function<bool(const Ele&, const Ele&)>&& cmp) override
		{
			::omp_set_num_threads(4);
			kerbal::ompalgo::shell_sort(this->v.begin(), this->v.end(), cmp);
		}
};


#endif //VISUAL_SORT_ANIMATION_HPP
