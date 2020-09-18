/**
 * @file       get_sin_wave_sequence.hpp
 * @brief
 * @date       2020-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_GET_SIN_WAVE_SEQUENCE_HPP
#define VISUAL_SORT_GET_SIN_WAVE_SEQUENCE_HPP

#include <vector>
#include <cmath>

template <typename Tp, typename Engine>
std::vector<Tp> get_sin_wave_sequence(int n, Engine & eg)
{
	std::vector<Tp> v;
	v.reserve(n);

	int start = eg();

	for (int i = 0; i < n; ++i) {
		v.push_back(30000 * (1 + std::sin((start + i) / 100.0)));
	}
	return v;
}

#endif // VISUAL_SORT_GET_SIN_WAVE_SEQUENCE_HPP
