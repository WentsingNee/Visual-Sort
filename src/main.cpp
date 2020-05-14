#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/textbox.hpp>

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
	nana::form main_form(nana::API::make_center(500, 200));
	main_form.caption("visual sort");
	main_form.bgcolor(nana::colors::white_smoke);
	main_form.events().destroy([](){
		std::quick_exit(0);
	});

	nana::place place(main_form);
	place.div(
			"<width=15>"
			"<vert "
				"<height=15>"
				"<<al> <a> height=30>"
				"<height=15>"
				"<<dl> <d> height=30>"
				"<height=15>"
				"<<egl> <eg> <width=30> <seedl> <seed> height=30>"
				"<height=15>"
				"< <<delayl> <delay>> <width=15> <<scalel> <scale>> <width=15> <start> height=30>"
				"<height=15>"
			">"
			"<width=15>"
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
			"boost::flat_stable_skort",
			"boost::pdqsort",
			"boost::sample_sort",
			"boost::spinsort",
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
			std::make_unique<boost_flat_stable_sort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<boost_pdqsort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<boost_sample_sort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
			std::make_unique<boost_spinsort_animation, nana::form&, nana::drawing&, std::chrono::microseconds&>,
	};
	int sorting_algorithm_id = 6;
	nana::combox sorting_algorithm_combox(main_form);
	for (const auto & ele : sorting_algorithm_name) {
		sorting_algorithm_combox.push_back(ele);
	}
	sorting_algorithm_combox.events().selected([&]() {
		sorting_algorithm_id = sorting_algorithm_combox.option();
	});
	sorting_algorithm_combox.option(sorting_algorithm_id);
	place["a"] << sorting_algorithm_combox;


	nana::label data_generate_method_label(main_form, "data generate method");
	place["dl"] << data_generate_method_label;
	std::string data_generate_method_name[] = {
			"constant",
			"random",
			"sorted",
			"reverse sorted",
			"nearly sorted",
			"few unique",
			"sawtooth",
			"reverse sawtooth",
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

	int data_generate_method_id = 1;
	nana::combox data_generate_method_combox(main_form);
	for (const auto & ele : data_generate_method_name) {
		data_generate_method_combox.push_back(ele);
	}
	data_generate_method_combox.events().selected([&]() {
		data_generate_method_id = data_generate_method_combox.option();
	});
	data_generate_method_combox.option(data_generate_method_id);
	place["d"] << data_generate_method_combox;


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

	int random_engine_id = 1;
	nana::combox random_engine_combox(main_form);
	for (const auto& ele : random_engine_name) {
		random_engine_combox.push_back(ele);
	}
	random_engine_combox.events().selected([&]() {
		random_engine_id = random_engine_combox.option();
	});
	random_engine_combox.option(random_engine_id);
	place["eg"] << random_engine_combox;

	nana::label random_engine_seed_label(main_form, "seed");
	place["seedl"] << random_engine_seed_label;

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
	place["delayl"] << delay_label;

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
	place["delay"] << delay_text_box;



	nana::label scale_label(main_form, "data scale");
	place["scalel"] << scale_label;

	size_t scale = 500;
	nana::textbox scale_text_box(main_form);
	scale_text_box.set_accept([](wchar_t c) -> bool {
		return c == 8 || c == 127 || std::isdigit(c);
	});
	scale_text_box.events().text_changed([&scale_label, &scale_text_box, &scale]() {
		try {
			scale = std::stoi(scale_text_box.caption());
			scale_text_box.bgcolor(nana::colors::white);
		} catch (...) {
			scale_text_box.bgcolor(nana::colors::indian_red);
		}
	});
	scale_text_box.caption(std::to_string(scale));
	place["scale"] << scale_text_box;

	nana::button start_button(main_form, "start");
	start_button.events().click([&]() {
		nana::form animation_form(nana::API::make_center(1000, 600));
		animation_form.bgcolor(nana::colors::grey);
		animation_form.caption(
			sorting_algorithm_name[sorting_algorithm_id] +
			", " +
			data_generate_method_name[data_generate_method_id] +
			", " +
			random_engine_name[random_engine_id] + " (with seed = " + std::to_string(seed) + ")" +
			", " +
			"scale = " + std::to_string(scale)
		);

		nana::drawing dw(animation_form);

		reseed_engine(seed);
		std::vector<int> v = get_data_wrapper[data_generate_method_id](scale, engine_wrapper[random_engine_id]);
		/*for (auto e : v) {
			std::cout << e << std::endl;
		}*/
		std::unique_ptr<animation_base> animation = generate_animation[sorting_algorithm_id](animation_form, dw, delay);

		std::thread animation_thread([&animation, &v] {
			std::cout << "animation start!" << std::endl;
			animation->start(v.begin(), v.end(), std::less<int>());
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
