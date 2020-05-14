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


	public:
		animation_base(nana::form & fm, nana::drawing & dw, std::chrono::microseconds & delay) : fm(fm), dw(dw), delay(delay)
		{
		}

		virtual ~animation_base() = default;

		template <typename Iterator, typename ValueCompare>
		void start(Iterator first, Iterator last, ValueCompare value_compare)
		{
			int mini = *std::min_element(first, last);
			int maxi = *std::max_element(first, last);

			{
				v.clear();

				int i = 0;
				while (first != last) {
					v.push_back({ *first, i });
					++first;
					++i;
				}
			}

			size_t n = v.size();

			auto draw_one_ele = [this, n, mini, maxi](nana::paint::graphics& graphic, size_t i, const nana::color& color) {
				int left = fm.size().width * i / n;
				int right = fm.size().width * (i + 1) / n;

				int height;
				if (maxi == mini) {
					height = fm.size().height / 2;
				} else {
					height = ((double)v[i].first - (double)mini) / ((double)maxi - (double)mini) * fm.size().height;
				}
				graphic.rectangle(nana::rectangle(left, fm.size().height - height, right - left, height), true, color);
			};


			size_t cmp_cnt = 0;
			{
				int highlight[2];
				dw.draw([this, n, &highlight, &draw_one_ele, &cmp_cnt](nana::paint::graphics& graphic) {
					for (size_t i = 0; i < n; ++i) {
						nana::color color = nana::colors::white_smoke;
						if (v[i].second == highlight[0]) {
							color = nana::colors::red;
						} else if (v[i].second == highlight[1]) {
							color = nana::colors::green;
						}
						draw_one_ele(graphic, i, color);
					}
					graphic.string({ 10, 10 }, "compare times: " + std::to_string(cmp_cnt));
				});
				this->sort([this, &value_compare, &highlight, &cmp_cnt](const Ele& lhs, const Ele& rhs) {
					highlight[0] = lhs.second;
					highlight[1] = rhs.second;
					++cmp_cnt;
					this->dw.update();
					std::this_thread::sleep_for(this->delay);
					return value_compare(lhs.first, rhs.first);
				});
				dw.clear();
			}

			{
				size_t j = 0;
				dw.draw([&j, n, &draw_one_ele, cmp_cnt](nana::paint::graphics& graphic) {
					for (size_t i = 0; i < n; ++i) {
						nana::color color = j < i ? nana::colors::white_smoke : nana::colors::green;
						draw_one_ele(graphic, i, color);
					}
					graphic.string({ 10, 10 }, "compare times: " + std::to_string(cmp_cnt));
				});
				for (j = 0; j < n; ++j) {
					this->dw.update();
					std::this_thread::sleep_for(this->delay);
				}
				dw.clear();
			}
			{
				dw.draw([n, draw_one_ele, cmp_cnt](nana::paint::graphics& graphic) {
					for (size_t i = 0; i < n; ++i) {
						nana::color color = nana::colors::green;
						draw_one_ele(graphic, i, color);
					}
					graphic.string({ 10, 10 }, "compare times: " + std::to_string(cmp_cnt));
				});
			}
		}

		virtual void sort(std::function<bool(const Ele&, const Ele&)>&& cmp) = 0;

};


#endif //VISUAL_SORT_ANIMATION_BASE_HPP
