/**
 * @file       get_perlin_noise_sequence.hpp
 * @brief
 * @date       2020-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_GET_PERLIN_NOISE_SEQUENCE_HPP
#define VISUAL_SORT_GET_PERLIN_NOISE_SEQUENCE_HPP

#include <vector>
#include <iostream>
#include <kerbal/random/perlin_noise.hpp>

template <typename Tp, typename Engine>
std::vector<Tp> get_perlin_noise_sequence(int n, Engine & eg)
{
	std::vector<Tp> v;
	v.reserve(n);

	kerbal::random::perlin_noise<> noise(eg);

	for (int i = 0; i < n; ++i) {
		auto r = 6000 * noise(i * 0.01);
//		std::cout << r << std::endl;
		v.push_back(r);
	}
	return v;
}

#endif // VISUAL_SORT_GET_PERLIN_NOISE_SEQUENCE_HPP
