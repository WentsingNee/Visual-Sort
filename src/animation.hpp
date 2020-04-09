/**
 * @file       animation.hpp
 * @brief
 * @date       2020-04-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_ANIMATION_HPP
#define VISUAL_SORT_ANIMATION_HPP

#include "animation_base.hpp"

#include <kerbal/algorithm/sort.hpp>

class bubble_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort() override
		{
			kerbal::algorithm::bubble_sort(this->v.begin(), this->v.end(), this->cmp);
		}
};

class selection_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort() override
		{
			kerbal::algorithm::selection_sort(this->v.begin(), this->v.end(), this->cmp);
		}
};

class heap_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort() override
		{
			kerbal::algorithm::heap_sort(this->v.begin(), this->v.end(), this->cmp);
		}
};

class merge_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort() override
		{
			kerbal::algorithm::merge_sort(this->v.begin(), this->v.end(), this->cmp);
		}
};

class insertion_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort() override
		{
			kerbal::algorithm::insertion_sort(this->v.begin(), this->v.end(), this->cmp);
		}
};

class shell_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort() override
		{
			kerbal::algorithm::shell_sort(this->v.begin(), this->v.end(), this->cmp);
		}
};

class quick_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort() override
		{
			kerbal::algorithm::quick_sort(this->v.begin(), this->v.end(), this->cmp);
		}
};

#include <algorithm>

class std_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort() override
		{
			std::sort(this->v.begin(), this->v.end(), this->cmp);
		}
};

class std_stable_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort() override
		{
			std::stable_sort(this->v.begin(), this->v.end(), this->cmp);
		}
};


#include <boost/sort/spinsort/spinsort.hpp>

class boost_spinsort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort() override
		{
			boost::sort::spinsort(this->v.begin(), this->v.end(), this->cmp);
		}
};

#include <boost/sort/sample_sort/sample_sort.hpp>

class boost_sample_sort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort() override
		{
			boost::sort::sample_sort(this->v.begin(), this->v.end(), this->cmp);
		}
};


#include <boost/sort/pdqsort/pdqsort.hpp>

class boost_pdqsort_animation: public animation_base
{
		using animation_base::animation_base;

		virtual void sort() override
		{
			boost::sort::pdqsort(this->v.begin(), this->v.end(), this->cmp);
		}
};



#endif //VISUAL_SORT_ANIMATION_HPP
