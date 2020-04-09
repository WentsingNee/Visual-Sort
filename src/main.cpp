#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/scroll.hpp>

#include <iostream>
#include <thread>
#include <memory>


#include "get_data.hpp"
#include "animation.hpp"

#include <kerbal/container/nonmember_container_access.hpp>

#include <kerbal/random/linear_congruential_engine.hpp>
#include <kerbal/random/mersenne_twister_engine.hpp>

int main()
{
	nana::form main_form(nana::API::make_center(1000, 400));
	main_form.caption("visual sort");
	main_form.bgcolor(nana::colors::white_smoke);
	main_form.events().destroy([](){
		std::quick_exit(0);
	});

	nana::place place(main_form);
	place.div(
			"<width=15><vert "
			"<height=15>"
			"<al height=30>"
			"<a>"
			"<dl height=30>"
			"<d>"
			"<egl height=30>"
			"< <eg><seed> height=30>"
			"<height=15>"
			"<start height=30>"
			"<height=15>"
			"><width=15>"
	);



	nana::label sorting_algorithm_label(main_form, "sorting algorithm");
	place["al"] << sorting_algorithm_label;
	std::string sorting_algorithm_name[] = {
			"bubble sort",
			"selection sort",
			"heap sort",
			"merge sort",
			"insertion sort",
			"shell sort",
			"quick sort",
			"std::sort",
			"std::stable_sort",
			"boost::spinsort",
			"boost::sample_sort",
			"boost::pdqsort",
	};
	std::function<std::unique_ptr<animation_base>(nana::form& animation_form,
												  nana::drawing& dw,
												  std::chrono::microseconds& delay)> generate_animation[] = {
			std::make_unique<bubble_sort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<selection_sort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<heap_sort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<merge_sort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<insertion_sort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<shell_sort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<quick_sort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<std_sort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<std_stable_sort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<boost_spinsort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<boost_sample_sort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<boost_pdqsort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
	};
	nana::radio_group sorting_algorithm_group;
	int sorting_algorithm_id = 0;
	nana::checkbox sorting_algorithm_radios[kerbal::container::size(sorting_algorithm_name)];

	for (int i = 0; i < kerbal::container::size(sorting_algorithm_name); ++i) {
		nana::checkbox& radio = sorting_algorithm_radios[i];
		sorting_algorithm_group.add(radio);
		radio.create(main_form, true);
		radio.radio(true);
		radio.bgcolor(nana::colors::white_smoke);
		radio.caption(sorting_algorithm_name[i]);
		if (sorting_algorithm_id == i) {
			radio.check(true);
		}
		radio.events().click([i, &sorting_algorithm_id]() {
			sorting_algorithm_id = i;
		});
		place["a"] << radio;
	}


	nana::label data_generate_method_label(main_form, "data generate method");
	place["dl"] << data_generate_method_label;
	std::string data_generate_method_name[] = {
			"const",
			"random",
			"sorted",
			"reverse",
			"nearly_sorted",
			"few_unique",
			"sawtooth",
			"reverse_sawtooth",
			"sin",
	};
	std::function<std::vector<int>(int, std::function<int()> &)> get_data_wrapper[] = {
			get_const<int, std::function<int()> >,
			get_random<int, std::function<int()> >,
			get_sorted<int, std::function<int()> >,
			get_reverse<int, std::function<int()> >,
			get_nearly_sorted<int, std::function<int()> >,
			get_few_unique<int, std::function<int()> >,
			get_sawtooth_array<int, std::function<int()> >,
			get_reverse_sawtooth_array<int, std::function<int()> >,
			get_sin<int, std::function<int()> >,
	};

	nana::radio_group data_generate_method_group;
	int data_generate_method_id = 1;
	nana::checkbox data_generate_method_radios[kerbal::container::size(data_generate_method_name)];

	for (int i = 0; i < kerbal::container::size(data_generate_method_name); ++i) {
		nana::checkbox& radio = data_generate_method_radios[i];
		data_generate_method_group.add(radio);
		radio.create(main_form, true);
		radio.radio(true);
		radio.bgcolor(nana::colors::white_smoke);
		radio.caption(data_generate_method_name[i]);
		if (data_generate_method_id == i) {
			radio.check(true);
		}
		radio.events().click([i, &data_generate_method_id]() {
			data_generate_method_id = i;
		});
		place["d"] << radio;
	}


	nana::label random_engine_label(main_form, "random engine");
	place["egl"] << random_engine_label;
	std::string random_engine_name[] = {
			"minstd_rand",
			"minstd_rand0",
			"mt19937",
	};
	kerbal::random::minstd_rand minstd_rand;
	kerbal::random::minstd_rand0 minstd_rand0;
	kerbal::random::mt19937 mt19937;
	auto reseed_engine = [&](int seed) {
		minstd_rand.seed(seed);
		minstd_rand0.seed(seed);
		mt19937 = kerbal::random::mt19937(seed);
	};

	std::function<int()> engine_wrapper[] = {
			[&minstd_rand]() { return minstd_rand();},
			[&minstd_rand0]() { return minstd_rand0();},
			[&mt19937]() { return mt19937();},
	};
	nana::radio_group random_engine_group;
	int random_engine_id = 1;
	nana::checkbox random_engine_radios[kerbal::container::size(random_engine_name)];

	for (int i = 0; i < kerbal::container::size(random_engine_name); ++i) {
		nana::checkbox& radio = random_engine_radios[i];
		random_engine_group.add(radio);
		radio.create(main_form, true);
		radio.radio(true);
		radio.bgcolor(nana::colors::white_smoke);
		radio.caption(random_engine_name[i]);
		if (random_engine_id == i) {
			radio.check(true);
		}
		radio.events().click([i, &random_engine_id]() {
			random_engine_id = i;
		});
		place["eg"] << radio;
	}

	nana::label random_engine_seed_label(main_form, "seed");
	place["seed"] << random_engine_seed_label;

	int seed = 0;
	nana::textbox random_engine_seed_textbox(main_form);
	random_engine_seed_textbox.set_accept([](wchar_t c) -> bool {
		return c == 8 || c == 127 || std::isdigit(c);
	});
	random_engine_seed_textbox.events().text_changed([&seed, &random_engine_seed_textbox](){
		try {
			seed = std::stoi(random_engine_seed_textbox.caption());
			random_engine_seed_textbox.bgcolor(nana::colors::white);
		} catch (...) {
			random_engine_seed_textbox.bgcolor(nana::colors::indian_red);
		}
	});
	random_engine_seed_textbox.caption("0");
	place["seed"] << random_engine_seed_textbox;


	nana::label delay_label(main_form, "delay (us)");
	place["start"] << delay_label;

	using namespace std::chrono_literals;
	std::chrono::microseconds delay = 50us;
	nana::textbox delay_text_box(main_form);
	delay_text_box.caption("50");
	delay_text_box.set_accept([](wchar_t c) -> bool {
		return c == 8 || c == 127 || std::isdigit(c);
	});
	delay_text_box.events().text_changed([&delay_label, &delay_text_box, &delay]() {
		try {
			int i = std::stoi(delay_text_box.caption());
			delay = std::chrono::microseconds(i);
			delay_text_box.bgcolor(nana::colors::white);
		} catch (...) {
			delay_text_box.bgcolor(nana::colors::indian_red);
		}
	});
	place["start"] << delay_text_box;

	nana::button start_button(main_form, "start");
	start_button.events().click([&]() {
		nana::form animation_form(nana::API::make_center(1000, 600));
		animation_form.bgcolor(nana::colors::grey);
		animation_form.caption(
			sorting_algorithm_name[sorting_algorithm_id] +
			", " +
			data_generate_method_name[data_generate_method_id] +
			", " +
			random_engine_name[random_engine_id] + " (with seed = " +
			std::to_string(seed) + ")"
		);

		nana::drawing dw(animation_form);

		int n = 1000;
		reseed_engine(seed);
		std::vector<int> v = get_data_wrapper[data_generate_method_id](n, engine_wrapper[random_engine_id]);
		std::unique_ptr<animation_base> animation = generate_animation[sorting_algorithm_id](animation_form, dw, delay);
		animation->prepare(v.begin(), v.end(), std::less<int>());

		dw.draw(std::bind(&animation_base::draw, animation.get(), std::placeholders::_1));
		std::thread animation_thread([&animation] {
			std::cout << "animation start!" << std::endl;
			animation->start();
			std::cout << "down!" << std::endl;
		});
		animation_form.show();
		nana::exec();
		animation_thread.join();

	});
	place["start"] << start_button;

	place.collocate();

	main_form.show();

	nana::exec();

	return 0;
}
