/**
 * @file       get_nearly_sorted_sequence.hpp
 * @brief
 * @date       2020-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_GET_NEARLY_SORTED_SEQUENCE_HPP
#define VISUAL_SORT_GET_NEARLY_SORTED_SEQUENCE_HPP

#include <vector>
#include "get_sorted_sequence.hpp"

template <typename Tp, typename Engine>
std::vector<Tp> get_nearly_sorted_sequence(int n, Engine & eg)
{
	std::vector<Tp> v = get_sorted_sequence<Tp>(n, eg);

	for (typename std::vector<Tp>::size_type i = 0; i < v.size() / 20; ++i) {
		int lhs = eg() % v.size();
		int rhs = eg() % v.size();
		if (lhs != rhs) {
			std::swap(v[lhs], v[rhs]);
		}
	}
	return v;
}

#endif // VISUAL_SORT_GET_NEARLY_SORTED_SEQUENCE_HPP
