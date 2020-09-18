/**
 * @file       get_sorted_sequence.hpp
 * @brief
 * @date       2020-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_GET_SORTED_SEQUENCE_HPP
#define VISUAL_SORT_GET_SORTED_SEQUENCE_HPP

#include <vector>
#include <algorithm>
#include "get_random_sequence.hpp"

template <typename Tp, typename Engine>
std::vector<Tp> get_sorted_sequence(int n, Engine & eg)
{
	std::vector<Tp> v = get_random_sequence<Tp>(n, eg);
	std::sort(v.begin(), v.end());
	return v;
}

template <typename Tp, typename Engine>
std::vector<Tp> get_reverse_sequence(int n, Engine & eg)
{
	std::vector<Tp> v = get_random_sequence<Tp>(n, eg);
	std::sort(v.begin(), v.end(), std::greater<Tp>());
	return v;
}

#endif // VISUAL_SORT_GET_SORTED_SEQUENCE_HPP
