/**
 * @file       access_hook_iterator.hpp
 * @brief
 * @date       2020-09-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_ACCESS_HOOK_ITERATOR_HPP
#define VISUAL_SORT_ACCESS_HOOK_ITERATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/addable.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/operators/subtractable.hpp>

#include <iterator>
#include <functional>

template <typename Iter>
class access_hook_iterator:
		public kerbal::operators::dereferenceable<
				access_hook_iterator<Iter>,
				typename Iter::pointer
		>, // it->
		public kerbal::operators::incrementable<
				access_hook_iterator<Iter>
		>, // it++

		public kerbal::operators::decrementable<
				access_hook_iterator<Iter>
		>, // it--

		public kerbal::operators::addable<
				access_hook_iterator<Iter>,
				typename kerbal::iterator::iterator_traits<Iter>::difference_type
		>, // it + N
		public kerbal::operators::addable_left<
				access_hook_iterator<Iter>,
				typename kerbal::iterator::iterator_traits<Iter>::difference_type
		>, // N + it
		public kerbal::operators::subtractable<
				access_hook_iterator<Iter>,
				typename kerbal::iterator::iterator_traits<Iter>::difference_type
		> // it - N
{
	private:
		typedef Iter Base;

		Base current;

	public:
		typedef typename Base::iterator_category	iterator_category;
		typedef typename Base::value_type			value_type;
		typedef typename Base::difference_type		difference_type;
		typedef typename Base::pointer				pointer;
		typedef typename Base::reference			reference;

	public:
		std::function<void()> access_hook;

	public:
		access_hook_iterator(Iter current = Iter(), std::function<void()> && access_hook = nullptr):
				current(current), access_hook(access_hook)
		{
		}

		reference operator*() const
		{
			if (access_hook) {
				access_hook();
			}
			return *current;
		}

		KERBAL_CONSTEXPR14
		access_hook_iterator& operator++()
		{
			++this->current;
			return static_cast<access_hook_iterator&>(*this);
		}

		friend KERBAL_CONSTEXPR
		bool operator==(const access_hook_iterator & lhs, const access_hook_iterator & rhs)
		{
			return lhs.current == rhs.current;
		}

		friend KERBAL_CONSTEXPR
		bool operator!=(const access_hook_iterator & lhs, const access_hook_iterator & rhs)
		{
			return lhs.current != rhs.current;
		}

		KERBAL_CONSTEXPR14
		access_hook_iterator& operator--()
		{
			--this->current;
			return static_cast<access_hook_iterator&>(*this);
		}

		friend KERBAL_CONSTEXPR
		difference_type operator-(const access_hook_iterator & lhs, const access_hook_iterator & rhs)
		{
			return lhs.current - rhs.current;
		}

		KERBAL_CONSTEXPR14
		access_hook_iterator& operator+=(const difference_type & delta)
		{
			this->current += delta;
			return static_cast<access_hook_iterator&>(*this);
		}

		KERBAL_CONSTEXPR14
		access_hook_iterator& operator-=(const difference_type & delta)
		{
			this->current -= delta;
			return static_cast<access_hook_iterator&>(*this);
		}

		KERBAL_CONSTEXPR14
		reference operator[](const difference_type & dist) const
		{
			return *(static_cast<const access_hook_iterator&>(*this) + dist);
		}

		friend KERBAL_CONSTEXPR
		bool operator<(const access_hook_iterator & lhs, const access_hook_iterator & rhs)
		{
			return lhs.current < rhs.current;
		}

		friend KERBAL_CONSTEXPR
		bool operator<=(const access_hook_iterator & lhs, const access_hook_iterator & rhs)
		{
			return lhs.current <= rhs.current;
		}

		friend KERBAL_CONSTEXPR
		bool operator>(const access_hook_iterator & lhs, const access_hook_iterator & rhs)
		{
			return lhs.current > rhs.current;
		}

		friend KERBAL_CONSTEXPR
		bool operator>=(const access_hook_iterator & lhs, const access_hook_iterator & rhs)
		{
			return lhs.current >= rhs.current;
		}

};

#endif // VISUAL_SORT_ACCESS_HOOK_ITERATOR_HPP
