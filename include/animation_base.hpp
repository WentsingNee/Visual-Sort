/**
 * @file       animation_base.hpp
 * @brief
 * @date       2020-04-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_ANIMATION_BASE_HPP
#define VISUAL_SORT_ANIMATION_BASE_HPP

#include <chrono>
#include <functional>

namespace nana
{
	class form;
	class drawing;
}

#include "template_instantiation/vector.inst.hpp"

#include "sorting_algorithm_united_interface.hpp"

class animation_base
{
	public:
		using Ele = int;

	protected:
		nana::form & fm;
		nana::drawing & dw;
		std::chrono::microseconds & delay;

		std::vector<Ele> v;


	public:
		animation_base(nana::form & fm, nana::drawing & dw, std::chrono::microseconds & delay)
				: fm(fm), dw(dw), delay(delay)
		{
		}

		virtual ~animation_base() = default;

		void start(std::vector<Ele>::iterator first, std::vector<Ele>::iterator last,
				   std::function<bool(const Ele&, const Ele&)> && value_compare);

		virtual void sort(std::function<bool(const Ele&, const Ele&)>&& cmp) = 0;

};

template <void(*SortAlgo)(Iter first, Iter last, BinaryPredict cmp)>
class standard_animation : public animation_base
{
		using animation_base::animation_base;

		virtual void sort(std::function<bool(const Ele&, const Ele&)>&& cmp) override
		{
			SortAlgo(this->v.begin(), this->v.end(), cmp);
		}
};


#endif //VISUAL_SORT_ANIMATION_BASE_HPP
