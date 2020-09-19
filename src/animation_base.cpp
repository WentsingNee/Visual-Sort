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

#include <thread>
#include <atomic>

#include <nana/gui/drawing.hpp>
#include <nana/gui/widgets/form.hpp>

void animation_base::start(std::vector<Ele>::iterator first, std::vector<Ele>::iterator last,
						   std::function<bool(const Ele&, const Ele&)>&& value_compare)
{
	int mini;
	int maxi;
	{
		auto p = std::minmax_element(first, last);
		mini = *p.first;
		maxi = *p.second;
	}

	v.assign(first, last);

	size_t n = v.size();

	auto draw_one_bar = [this, n, mini, maxi](nana::paint::graphics& graphic, size_t i, const nana::color& color) {
		int left = fm.size().width * i / n;
		int right = fm.size().width * (i + 1) / n;

		int height;
		if (maxi == mini) {
			height = fm.size().height / 2;
		} else {
			height = ((double)v[i] - (double)mini) / ((double)maxi - (double)mini) * fm.size().height;
		}
		graphic.rectangle(nana::rectangle(left, fm.size().height - height, right - left, height), true, color);
	};


	std::atomic_size_t cmp_cnt(0);
	{
		size_t highlight[2];
		this->dw.draw([n, &highlight, &draw_one_bar, &cmp_cnt](nana::paint::graphics& graphic) {
			for (size_t i = 0; i < n; ++i) {
				nana::color color = nana::colors::white_smoke;
				if (i == highlight[0]) {
					color = nana::colors::red;
				} else if (i == highlight[1]) {
					color = nana::colors::green;
				}
				draw_one_bar(graphic, i, color);
			}
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
				nana::color color = nana::colors::green;
				draw_one_bar(graphic, i, color);
			}
			for (; i < n; ++i) {
				nana::color color = nana::colors::white_smoke;
				draw_one_bar(graphic, i, color);
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
		this->dw.draw([n, draw_one_bar, cmp_cnt = cmp_cnt.load()](nana::paint::graphics& graphic) {
			nana::color color = nana::colors::green;
			for (size_t i = 0; i < n; ++i) {
				draw_one_bar(graphic, i, color);
			}
			graphic.string({ 10, 10 }, "compare times: " + std::to_string(cmp_cnt));
		});
	}
}