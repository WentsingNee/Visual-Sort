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

#include <kerbal/iterator/iterator.hpp>
#include <vector>
#include <algorithm>
#include <functional>
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

template <typename Tp, typename Engine>
std::vector<Tp> get_pipe_organ(int n, Engine & /*eg*/)
{
//	std::vector<Tp> v = get_random_sequence<Tp>(n, eg);
//	typename std::vector<Tp>::iterator mid(kerbal::iterator::midden_iterator(v.begin(), v.end()));
//	std::sort(v.begin(), mid, std::less<Tp>());
//	std::sort(mid, v.end(), std::greater<Tp>());

	std::vector<Tp> v(n, 0);
	int i = 0;
	for (; i < n / 2; ++i) {
		v[i] = i;
	}
	for (; i < n; ++i) {
		v[i] = n - i;
	}
	return v;
}

#endif // VISUAL_SORT_GET_SORTED_SEQUENCE_HPP
