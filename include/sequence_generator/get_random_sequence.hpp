/**
 * @file       get_random_sequence.hpp
 * @brief
 * @date       2020-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_GET_RANDOM_SEQUENCE_HPP
#define VISUAL_SORT_GET_RANDOM_SEQUENCE_HPP

template <typename Tp, typename Engine>
std::vector<Tp> get_random_sequence(int n, Engine & eg)
{
	std::vector<Tp> v;
	v.reserve(n);
	for (int i = 0; i < n; ++i) {
		v.push_back(eg());
	}
	return v;
}

#endif // VISUAL_SORT_GET_RANDOM_SEQUENCE_HPP
