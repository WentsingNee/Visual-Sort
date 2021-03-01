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
#include <nana/paint/graphics.hpp>

namespace nana
{
	class form;
	class drawing;
}

#include "template_instantiation/vector.inst.hpp"

#include "sorting_algorithm_united_interface.hpp"
#include "access_hook_iterator.hpp"

class animation_base
{
	public:
		using Ele = int;

	protected:
		nana::form & fm;
		nana::drawing & dw;
		std::chrono::microseconds & delay;

		std::vector<Ele> v;

		void(*const SortAlgo)(Iter first, Iter last, BinaryPredict cmp);


	public:
		animation_base(nana::form & fm, nana::drawing & dw, std::chrono::microseconds & delay,
						   void(*const SortAlgo)(Iter first, Iter last, BinaryPredict cmp))
				: fm(fm), dw(dw), delay(delay), SortAlgo(SortAlgo)
		{
		}

		virtual ~animation_base() = default;

		void start(std::vector<Ele>::iterator first, std::vector<Ele>::iterator last,
				   std::function<bool(const Ele&, const Ele&)> && value_compare);

//		virtual void draw(nana::paint::graphics& graphic) = 0;

};

class standard_animation : public animation_base
{
	public:
		standard_animation(nana::form & fm, nana::drawing & dw, std::chrono::microseconds & delay,
						   void(*const SortAlgo)(Iter first, Iter last, BinaryPredict cmp))
				: animation_base(fm, dw, delay, SortAlgo)
		{
		}

//		std::function<void(nana::paint::graphics&)> event;
//
//		virtual void draw(nana::paint::graphics& graphic) override final
//		{
//			this->event(graphic);
//		}
};


#endif //VISUAL_SORT_ANIMATION_BASE_HPP
