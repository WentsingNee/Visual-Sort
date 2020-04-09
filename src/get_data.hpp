/**
 * @file       get_data.hpp
 * @brief
 * @date       2020-04-02
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_GET_DATA_HPP
#define VISUAL_SORT_GET_DATA_HPP

#include <algorithm>
#include <vector>

#include <kerbal/algorithm/modifier.hpp>

template <typename Tp, typename Engine>
std::vector<Tp> get_const(int n, Engine & eg)
{
	std::vector<Tp> v(n, eg());
	return v;
}


template <typename Tp, typename Engine>
std::vector<Tp> get_random(int n, Engine & eg)
{
	std::vector<Tp> v;
	v.reserve(n);
	for (int i = 0; i < n; ++i) {
		v.push_back(eg());
	}
	return v;
}


template <typename Tp, typename Engine>
std::vector<Tp> get_sorted(int n, Engine & eg)
{
	std::vector<Tp> v = get_random<Tp>(n, eg);
	std::sort(v.begin(), v.end());
	return v;
}


template <typename Tp, typename Engine>
std::vector<Tp> get_reverse(int n, Engine & eg)
{
	std::vector<Tp> v = get_random<Tp>(n, eg);
	std::sort(v.begin(), v.end(), std::greater<Tp>());
	return v;
}

template <typename Tp, typename Engine>
std::vector<Tp> get_nearly_sorted(int n, Engine & eg)
{
	std::vector<Tp> v = get_sorted<Tp>(n, eg);

	for (int i = 0; i < v.size() / 20; ++i) {
		int lhs = eg() % v.size();
		int rhs = eg() % v.size();
		if (lhs != rhs) {
			std::swap(v[lhs], v[rhs]);
		}
	}
	return v;
}

template <typename Tp, typename Engine>
std::vector<Tp> get_few_unique(int n, Engine & eg)
{
	std::vector<Tp> v0 = get_sorted<int>(n / 30 + 1, eg);

	std::vector<Tp> v;

	for (int i = 0; i < n; ++i) {
		int idx = eg() % v0.size();
		v.push_back(v0[idx]);
	}
	return v;
}

namespace detail
{

	template <typename BidirectionalIterator, typename Compare>
	BidirectionalIterator make_sawtooth(BidirectionalIterator first, BidirectionalIterator last, Compare compare)
	{
		while (first != last) {
			--last;
			if (first != last) {
				if (compare(*last, *first)) {
					kerbal::algorithm::iter_swap(first, last);
				}
				++first;
			} else {
				break;
			}
		}
		return first;
	}

	template <typename BidirectionalIterator, typename Compare>
	void sawtooth(BidirectionalIterator first, BidirectionalIterator last, Compare compare)
	{
		typedef BidirectionalIterator iterator;

		if (first == last) {
			return;
		}

		if (kerbal::iterator::next(first) == last) {
			return;
		}

		iterator mid(make_sawtooth(first, last, compare));
		sawtooth(first, mid, compare);
		sawtooth(mid, last, compare);
	}
}

template <typename Tp, typename Engine>
std::vector<Tp> get_sawtooth_array(int n, Engine & eg)
{
	std::vector<Tp> v = get_random<Tp>(n, eg);
	detail::sawtooth(v.begin(), v.end(), std::less<Tp>());
	return v;
}

template <typename Tp, typename Engine>
std::vector<Tp> get_reverse_sawtooth_array(int n, Engine & eg)
{
	std::vector<Tp> v = get_random<Tp>(n, eg);
	detail::sawtooth(v.begin(), v.end(), std::greater<Tp>());
	return v;
}

#include <cmath>

template <typename Tp, typename Engine>
std::vector<Tp> get_sin(int n, Engine & eg)
{
	std::vector<Tp> v;
	v.reserve(n);

	for (int i = 0; i < n; ++i) {
		v.push_back(60000 * (1 + std::sin(i / 100.0)));
	}
	return v;
}

#endif //VISUAL_SORT_GET_DATA_HPP
