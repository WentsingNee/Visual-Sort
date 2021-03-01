/**
 * @file       sequence_generator.inst.hpp
 * @brief
 * @date       2020-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_SEQUENCE_GENERATOR_INST_HPP
#define VISUAL_SORT_SEQUENCE_GENERATOR_INST_HPP


#include <template_instantiation/vector.inst.hpp>
#include <kerbal/random/uniform_real_distribution.hpp>

#include "polymorphic_random_engine.hpp"

template <typename Tp, typename Engine> std::vector<Tp> get_constant_sequence(int, Engine&);
template <typename Tp, typename Engine> std::vector<Tp> get_random_sequence(int, Engine&);
template <typename Tp, typename Engine> std::vector<Tp> get_sorted_sequence(int, Engine&);
template <typename Tp, typename Engine> std::vector<Tp> get_reverse_sequence(int, Engine&);
template <typename Tp, typename Engine> std::vector<Tp> get_pipe_organ(int, Engine&);
template <typename Tp, typename Engine> std::vector<Tp> get_nearly_sorted_sequence(int, Engine&);
template <typename Tp, typename Engine> std::vector<Tp> get_few_unique_sequence(int, Engine&);
template <typename Tp, typename Engine> std::vector<Tp> get_sawtooth_sequence(int, Engine&);
template <typename Tp, typename Engine> std::vector<Tp> get_reverse_sawtooth_sequence(int, Engine&);
template <typename Tp, typename Engine> std::vector<Tp> get_sin_wave_sequence(int, Engine&);
template <typename Tp, typename Engine> std::vector<Tp> get_perlin_noise_sequence(int, Engine&);

extern template std::vector<int> get_constant_sequence(int, polymorphic_random_engine&);
extern template std::vector<int> get_random_sequence(int, polymorphic_random_engine&);
extern template std::vector<int> get_sorted_sequence(int, polymorphic_random_engine&);
extern template std::vector<int> get_reverse_sequence(int, polymorphic_random_engine&);
extern template std::vector<int> get_pipe_organ(int, polymorphic_random_engine&);
extern template std::vector<int> get_nearly_sorted_sequence(int, polymorphic_random_engine&);
extern template std::vector<int> get_few_unique_sequence(int, polymorphic_random_engine&);
extern template std::vector<int> get_sawtooth_sequence(int, polymorphic_random_engine&);
extern template std::vector<int> get_reverse_sawtooth_sequence(int, polymorphic_random_engine&);
extern template std::vector<int> get_sin_wave_sequence(int, polymorphic_random_engine&);
extern template std::vector<int> get_perlin_noise_sequence(int, polymorphic_random_engine&);

template <typename Tp, typename Engine>
std::vector<Tp> get_push_back_sequence(int n, Engine& eg)
{
	std::vector<Tp> v;
	v.reserve(n);
	int r = n / 20;
	for (int i = 0; i < n - r; ++i) {
		v.push_back(eg());
	}
	std::sort(v.begin(), v.end());
	for (int i = 0; i < r; ++i) {
		v.push_back(eg());
	}
	return v;
}

#endif // VISUAL_SORT_SEQUENCE_GENERATOR_INST_HPP
