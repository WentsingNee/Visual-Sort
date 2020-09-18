/**
 * @file       get_constant_sequence.hpp
 * @brief
 * @date       2020-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_GET_CONSTANT_SEQUENCE_HPP
#define VISUAL_SORT_GET_CONSTANT_SEQUENCE_HPP

#include <vector>

template <typename Tp, typename Engine>
std::vector<Tp> get_constant_sequence(int n, Engine & eg)
{
	std::vector<Tp> v(n, eg());
	return v;
}

#endif // VISUAL_SORT_GET_CONSTANT_SEQUENCE_HPP
