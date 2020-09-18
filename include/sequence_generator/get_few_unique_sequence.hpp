/**
 * @file       get_few_unique_sequence.hpp
 * @brief
 * @date       2020-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_GET_FEW_UNIQUE_SEQUENCE_HPP
#define VISUAL_SORT_GET_FEW_UNIQUE_SEQUENCE_HPP

#include <vector>
#include "get_sorted_sequence.hpp"

template <typename Tp, typename Engine>
std::vector<Tp> get_few_unique_sequence(int n, Engine & eg)
{
	std::vector<Tp> v0 = get_sorted_sequence<Tp>(15, eg);

	std::vector<Tp> v;

	for (int i = 0; i < n; ++i) {
		int idx = eg() % v0.size();
		v.push_back(v0[idx]);
	}
	return v;
}

#endif // VISUAL_SORT_GET_FEW_UNIQUE_SEQUENCE_HPP
