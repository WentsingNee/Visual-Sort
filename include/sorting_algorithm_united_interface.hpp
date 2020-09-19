/**
 * @file       sorting_algorithm_united_interface.hpp
 * @brief
 * @date       2020-09-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_SORTING_ALGORITHM_UNITED_INTERFACE_HPP
#define VISUAL_SORT_SORTING_ALGORITHM_UNITED_INTERFACE_HPP

#include <vector>
#include <functional>

typedef std::vector<int>::iterator Iter;

typedef std::function<bool(const Iter::value_type&, const Iter::value_type&)> BinaryPredict;

#endif // VISUAL_SORT_SORTING_ALGORITHM_UNITED_INTERFACE_HPP
