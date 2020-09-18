/**
 * @file       get_sawtooth_sequence.hpp
 * @brief
 * @date       2020-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_GET_SAWTOOTH_SEQUENCE_HPP
#define VISUAL_SORT_GET_SAWTOOTH_SEQUENCE_HPP

#include <vector>
#include <kerbal/algorithm/swap.hpp>
#include "get_random_sequence.hpp"

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
std::vector<Tp> get_sawtooth_sequence(int n, Engine & eg)
{
	std::vector<Tp> v = get_random_sequence<Tp>(n, eg);
	detail::sawtooth(v.begin(), v.end(), std::less<Tp>());
	return v;
}

template <typename Tp, typename Engine>
std::vector<Tp> get_reverse_sawtooth_sequence(int n, Engine & eg)
{
	std::vector<Tp> v = get_random_sequence<Tp>(n, eg);
	detail::sawtooth(v.begin(), v.end(), std::greater<Tp>());
	return v;
}

#endif // VISUAL_SORT_GET_SAWTOOTH_SEQUENCE_HPP
