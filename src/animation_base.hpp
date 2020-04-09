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
#include <thread>
#include <vector>

class animation_base
{
	public:
		using Ele = std::pair<int, int>;

	protected:
		nana::form & fm;
		nana::drawing & dw;
		std::chrono::microseconds & delay;

		std::vector<Ele> v;
		std::function<bool(const Ele&, const Ele&)> cmp;

		int mini{};
		int maxi{};
		int highlight[2]{};

	public:
		animation_base(nana::form & fm, nana::drawing & dw, std::chrono::microseconds & delay) : fm(fm), dw(dw), delay(delay)
		{
		}

		virtual ~animation_base() = default;

		template <typename Iterator, typename ValueCompare>
		void prepare(Iterator first, Iterator last, ValueCompare value_compare)
		{
			v.clear();

			mini = *std::min_element(first, last);
			maxi = *std::max_element(first, last);

			int i = 0;
			while (first != last) {
				v.push_back({*first, i});
				++first;
				++i;
			}

			this->cmp = [this, &value_compare](const Ele& lhs, const Ele& rhs) {
				highlight[0] = lhs.second;
				highlight[1] = rhs.second;
				this->dw.update();
				std::this_thread::sleep_for(this->delay);
				return value_compare(lhs.first, rhs.first);
			};
		}

		void start()
		{
			this->sort();
			this->dw.update();
		}

		virtual void sort() = 0;

		void draw(nana::paint::graphics& graphic) const
		{
			size_t n = v.size();

			for (size_t i = 0; i < n; ++i) {
				int left = fm.size().width * i / n;
				int right = fm.size().width * (i + 1) / n;

				int height;
				if (maxi == mini) {
					height = fm.size().height / 2;
				} else {
					height = (v[i].first - mini) / double(maxi - mini) * fm.size().height;
				}
				nana::color color = nana::colors::white_smoke;
				if (v[i].second == highlight[0]) {
					color = nana::colors::red;
				} else if (v[i].second == highlight[1]) {
					color = nana::colors::green;
				}
				graphic.rectangle(nana::rectangle(left, fm.size().height - height, right - left, height), true, color);
			}
		}
};


#endif //VISUAL_SORT_ANIMATION_BASE_HPP
