/**
 * @file       polymorphic_random_engine.hpp
 * @brief
 * @date       2020-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef VISUAL_SORT_POLYMORPHIC_RANDOM_ENGINE_HPP
#define VISUAL_SORT_POLYMORPHIC_RANDOM_ENGINE_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>

class polymorphic_random_engine
{
	public:
		virtual ~polymorphic_random_engine() noexcept = default;

		virtual kerbal::compatibility::uint32_t operator()() = 0;
		virtual kerbal::compatibility::uint32_t min() const = 0;
		virtual kerbal::compatibility::uint32_t max() const = 0;
		virtual void seed(int) = 0;
};

template <typename Engine>
class polymorphic_random_engine_wrapper: public polymorphic_random_engine
{
	public:
		Engine eg;

		virtual kerbal::compatibility::uint32_t operator()() override
		{
			return eg();
		}

		virtual kerbal::compatibility::uint32_t min() const override
		{
			return eg.min();
		}

		virtual kerbal::compatibility::uint32_t max() const override
		{
			return eg.max();
		}

		virtual void seed(int seed) override
		{
			return eg.seed(seed);
		}

};

#endif // VISUAL_SORT_POLYMORPHIC_RANDOM_ENGINE_HPP
