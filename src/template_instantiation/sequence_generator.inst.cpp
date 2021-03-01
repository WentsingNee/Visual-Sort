/**
 * @file       sequence_generator.inst.cpp
 * @brief
 * @date       2020-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#include <sequence_generator/get_constant_sequence.hpp>
#include <sequence_generator/get_few_unique_sequence.hpp>
#include <sequence_generator/get_nearly_sorted_sequence.hpp>
#include <sequence_generator/get_perlin_noise_sequence.hpp>
#include <sequence_generator/get_random_sequence.hpp>
#include <sequence_generator/get_sawtooth_sequence.hpp>
#include <sequence_generator/get_sin_wave_sequence.hpp>
#include <sequence_generator/get_sorted_sequence.hpp>

#include <polymorphic_random_engine.hpp>

template std::vector<int> get_constant_sequence(int, polymorphic_random_engine&);
template std::vector<int> get_random_sequence(int, polymorphic_random_engine&);
template std::vector<int> get_sorted_sequence(int, polymorphic_random_engine&);
template std::vector<int> get_reverse_sequence(int, polymorphic_random_engine&);
template std::vector<int> get_pipe_organ(int, polymorphic_random_engine&);
template std::vector<int> get_nearly_sorted_sequence(int, polymorphic_random_engine&);
template std::vector<int> get_few_unique_sequence(int, polymorphic_random_engine&);
template std::vector<int> get_sawtooth_sequence(int, polymorphic_random_engine&);
template std::vector<int> get_reverse_sawtooth_sequence(int, polymorphic_random_engine&);
template std::vector<int> get_sin_wave_sequence(int, polymorphic_random_engine&);
template std::vector<int> get_perlin_noise_sequence(int, polymorphic_random_engine&);
