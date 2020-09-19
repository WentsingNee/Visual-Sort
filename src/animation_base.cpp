/**
 * @file       animation_base.cpp
 * @brief
 * @date       2020-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#include <animation_base.hpp>

#include <algorithm>
#include <thread>
#include <atomic>

#include <nana/gui/drawing.hpp>
#include <nana/gui/widgets/form.hpp>

void animation_base::start(std::vector<Ele>::iterator first, std::vector<Ele>::iterator last,
						   std::function<bool(const Ele&, const Ele&)>&& value_compare)
{
	v.assign(first, last);
	size_t n = v.size();

	int mini;
	int maxi;
	{
		auto p = std::minmax_element(v.begin(), v.end());
		mini = *p.first;
		maxi = *p.second;
	}

	auto draw_one_bar = [this, n, mini, maxi](nana::paint::graphics& graphic, size_t i, const nana::color& color) {
		const int width = graphic.width();
		const int height = graphic.height();

		int left = width * i / n;
		int right = width * (i + 1) / n;

		int bar_height;
		if (maxi == mini) {
			bar_height = height / 2;
		} else {
			bar_height = ((double)v[i] - (double)mini) / ((double)maxi - (double)mini) * height;
		}
		graphic.rectangle(nana::rectangle(left, height - bar_height, right - left, bar_height), true, color);
	};


	std::atomic_size_t cmp_cnt(0);
	{
		size_t highlight[2];
		this->dw.draw([n, &highlight, &draw_one_bar, &cmp_cnt](nana::paint::graphics& graphic) {
			for (size_t i = 0; i < n; ++i) {
				draw_one_bar(graphic, i, nana::colors::white_smoke);
			}
			draw_one_bar(graphic, highlight[0], nana::colors::red);
			draw_one_bar(graphic, highlight[1], nana::colors::green);
			graphic.string({ 10, 10 }, "compare times: " + std::to_string(cmp_cnt));
		});
		using namespace std::chrono_literals;
		this->sort([this, &value_compare, &highlight, &cmp_cnt](const Ele& lhs, const Ele& rhs) {
			highlight[0] = &lhs - &*this->v.begin();
			highlight[1] = &rhs - &*this->v.begin();
			++cmp_cnt;
			if (cmp_cnt % 10 == 0) {
				this->dw.update();
				std::this_thread::sleep_for(this->delay);
			}
			return value_compare(lhs, rhs);
		});
		this->dw.clear();
	}

	{
		size_t j = 0;
		this->dw.draw([&j, n, &draw_one_bar, cmp_cnt_caption = ("compare times: " + std::to_string(cmp_cnt))](nana::paint::graphics& graphic) {
			size_t i = 0;
			for (; i < j; ++i) {
				draw_one_bar(graphic, i, nana::colors::green);
			}
			for (; i < n; ++i) {
				draw_one_bar(graphic, i, nana::colors::white_smoke);
			}
			graphic.string({ 10, 10 }, cmp_cnt_caption);
		});
		for (j = 0; j <= n; j += 10) {
			this->dw.update();
			std::this_thread::sleep_for(this->delay);
		}
		this->dw.clear();
	}
	{
		this->dw.draw([n, draw_one_bar, cmp_cnt_caption = ("compare times: " + std::to_string(cmp_cnt))](nana::paint::graphics& graphic) {
			for (size_t i = 0; i < n; ++i) {
				draw_one_bar(graphic, i, nana::colors::green);
			}
			graphic.string({ 10, 10 }, cmp_cnt_caption);
		});
		this->dw.update();
	}
}