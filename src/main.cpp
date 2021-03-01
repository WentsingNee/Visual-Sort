#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/textbox.hpp>

#include <iostream>
#include <thread>
#include <memory>


#include "template_instantiation/sequence_generator.inst.hpp"
#include "template_instantiation/sorting_algorithm.inst.hpp"
#include "template_instantiation/vector.inst.hpp"

#include "animation.hpp"

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/container/nonmember_container_access.hpp>
#include <kerbal/random/linear_congruential_engine.hpp>
#include <kerbal/random/mersenne_twister_engine.hpp>
#include "polymorphic_random_engine.hpp"

struct sorting_algorithms_module
{
		static constexpr const char * const sorting_algorithm_name[] = {
				"std::sort",
				"std::stable_sort",
				"std_parallel_sort",
				"std_parallel_stable_sort",
				"c qsort",
				"bubble sort",
				"selection sort",
				"heap sort",
				"std::make_heap then sort",
				"merge sort",
				"inplace merge sort",
				"stable sort",
				"insertion sort",
				"directly insertion sort",
				"quick sort",
				"nonrecursive qsort",
				"intro sort",
				"nonrecursive intro sort",
				"shell sort (hibbard sequence)",
				"shell sort (minimun limit hibbard sequence)",
				"shell sort (reduce by half)",
				"shell sort (q)",
				"radix sort",
				"kerbal::omp::quick_sort",
//				"kerbal::omp::merge_sort",
				"kerbal::omp::shell_sort",
#if BOOST_SORT_SUPPORT
				"boost::block_indirect_sort",
				"boost::flat_stable_sort",
				"boost::heap_sort",
				"boost::pdqsort",
				"boost::sample_sort",
				"boost::spinsort",
				"boost::spreadsort",
				"boost::parallel_stable_sort",
#endif
				"gfx::timsort",
				"freedom implement",
		};

//		template <typename Animation>
//		static constexpr auto make_u = [](nana::form& animation_form,
//										  nana::drawing& dw,
//										  std::chrono::microseconds& delay) -> std::unique_ptr<animation_base> {
//			return std::make_unique<Animation>(animation_form, dw, delay);
//		};

		template <typename Animation>
		static
		std::unique_ptr<animation_base>
		make_u(nana::form& animation_form, nana::drawing& dw, std::chrono::microseconds& delay)
		{
			return std::make_unique<Animation>(animation_form, dw, delay);
		};

		template <void(* SortAlgo)(Iter first, Iter last, BinaryPredict cmp)>
		static
		std::unique_ptr<animation_base>
		make_s(nana::form& animation_form, nana::drawing& dw, std::chrono::microseconds& delay)
		{
			return std::make_unique<standard_animation>(animation_form, dw, delay, SortAlgo);
		};

		static constexpr std::unique_ptr<animation_base>(* const generate_animation[])(nana::form&, nana::drawing&, std::chrono::microseconds&)
			 = {
				make_s<std::sort>,
				make_s<std::stable_sort>,
				make_s<std_parallel_sort_wrapper>,
				make_s<std_parallel_stable_sort_wrapper>,
				make_s<cqsort_wrapper>,
				make_s<kerbal::algorithm::bubble_sort>,
				make_s<kerbal::algorithm::selection_sort>,
				make_s<kerbal::algorithm::heap_sort>,
				make_s<std_make_heap_then_sort_wrapper>,
				make_s<kerbal::algorithm::merge_sort>,
				make_s<kerbal::algorithm::inplace_merge_sort>,
				make_s<kerbal::algorithm::stable_sort>,
				make_s<kerbal::algorithm::insertion_sort>,
				make_s<kerbal::algorithm::directly_insertion_sort>,
				make_s<kerbal::algorithm::quick_sort>,
				make_s<kerbal::algorithm::nonrecursive_qsort>,
				make_s<kerbal::algorithm::intro_sort>,
				make_s<kerbal::algorithm::nonrecursive_intro_sort>,
				make_s<shell_sort_hibbard_sequence_wrapper>,
				make_s<shell_sort_minimun_limit_hibbard_sequence_wrapper>,
				make_s<shell_sort_reduce_by_half_wrapper>,
				make_s<shell_sort_q_wrapper>,
				make_s<radix_sort_wrapper>,
				make_s<omp_quick_sort_wrapper>,
//				make_s<kerbal_omp_merge_sort_animation>,
				make_s<omp_shell_sort_wrapper>,
#if BOOST_SORT_SUPPORT
				make_s<boost::sort::block_indirect_sort>,
				make_s<boost::sort::flat_stable_sort>,
				make_s<boost::sort::heap_sort>,
				make_s<boost::sort::pdqsort>,
				make_s<boost::sort::sample_sort>,
				make_s<boost::sort::spinsort>,
				make_s<boost_spreadsort_wrapper>,
				make_s<boost_parallel_stable_sort_wrapper>,
#endif
				make_s<gfx::timsort>,
				make_s<freedom_implement>,
		};

		KERBAL_STATIC_ASSERT(kerbal::container::size(sorting_algorithm_name) == kerbal::container::size(generate_animation), "not equal array length");

		sorting_algorithms_module(nana::form&, nana::place& place, nana::label& label, int& id,
								  nana::combox& combox)
		{
			place["al"] << label;
			id = 0;
			for (const auto& ele : sorting_algorithm_name) {
				combox.push_back(ele);
			}
			combox.events().selected([&]() {
				id = combox.option();
			});
			combox.option(id);
			place["a"] << combox;
		}
};

constexpr const char * const sorting_algorithms_module::sorting_algorithm_name [];
constexpr std::unique_ptr<animation_base>(* const sorting_algorithms_module::generate_animation[])(nana::form&, nana::drawing&, std::chrono::microseconds&);

struct sequence_generator_module
{
		static constexpr const char* const sequence_generator_name[] = {
				"constant",
				"random",
				"sorted",
				"reverse sorted",
				"pipe organ",
				"nearly sorted",
				"few unique",
				"push back",
				"sawtooth",
				"reverse sawtooth",
				"sin",
				"perlin_noise",
		};

		static constexpr std::vector<int> (* const sequence_generator[])(int, polymorphic_random_engine&) = {
				get_constant_sequence,
				get_random_sequence,
				get_sorted_sequence,
				get_reverse_sequence,
				get_pipe_organ,
				get_nearly_sorted_sequence,
				get_few_unique_sequence,
				get_push_back_sequence,
				get_sawtooth_sequence,
				get_reverse_sawtooth_sequence,
				get_sin_wave_sequence,
				get_perlin_noise_sequence,
		};

};

constexpr const char * const sequence_generator_module::sequence_generator_name [];
constexpr std::vector<int> (* const sequence_generator_module::sequence_generator[])(int, polymorphic_random_engine&);


int main()
{
	nana::form main_form(nana::API::make_center(500, 200));
	main_form.caption("visual sort");
	main_form.bgcolor(nana::colors::white_smoke);
	main_form.events().destroy([]() {
		std::quick_exit(0);
	});

	nana::place place(main_form);
	place.div(
			"<width=15>"
			"<vert "
			"<height=15>"
			"<<al width=35%> <a> height=30>"
			"<height=15>"
			"<<seq_gen_lable width=35%> <seq_gen_combox> height=30>"
			"<height=15>"
			"<<egl width=30%> <eg width=30%> <width=30> <seedl> <seed> height=30>"
			"<height=15>"
			"< <<delayl> <delay>> <width=15> <<scalel> <scale>> <width=15> <start> height=30>"
			"<height=15>"
			">"
			"<width=15>"
	);


	nana::label sorting_algorithm_label(main_form, "sorting algorithm");
	int sorting_algorithm_id;
	nana::combox sorting_algorithm_combox(main_form);
	sorting_algorithms_module(main_form, place, sorting_algorithm_label, sorting_algorithm_id,
							  sorting_algorithm_combox);

	nana::label data_generate_method_label(main_form, "sequence generator");
	place["seq_gen_lable"] << data_generate_method_label;

	int sequence_generator_id = 1;
	nana::combox sequence_generator_combox(main_form);
	for (const auto& ele : sequence_generator_module::sequence_generator_name) {
		sequence_generator_combox.push_back(ele);
	}
	sequence_generator_combox.events().selected([&]() {
		sequence_generator_id = sequence_generator_combox.option();
	});
	sequence_generator_combox.option(sequence_generator_id);
	place["seq_gen_combox"] << sequence_generator_combox;


	nana::label random_engine_label(main_form, "random engine");
	place["egl"] << random_engine_label;
	std::string random_engine_name[] = {
			"minstd_rand",
			"minstd_rand0",
			"mt19937",
	};
	std::unique_ptr<polymorphic_random_engine> polymorphic_random_engine = nullptr;

	int random_engine_id = 1;
	nana::combox random_engine_combox(main_form);
	for (const auto& ele : random_engine_name) {
		random_engine_combox.push_back(ele);
	}
	random_engine_combox.events().selected([&]() {
		random_engine_id = random_engine_combox.option();
		switch (random_engine_id) {
			case 0:
				polymorphic_random_engine = std::make_unique<polymorphic_random_engine_wrapper<kerbal::random::minstd_rand>>();
				break;
			case 1:
				polymorphic_random_engine = std::make_unique<polymorphic_random_engine_wrapper<kerbal::random::minstd_rand0>>();
				break;
			case 2:
				polymorphic_random_engine = std::make_unique<polymorphic_random_engine_wrapper<kerbal::random::mt19937>>();
				break;
		}

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
	random_engine_seed_textbox.events().text_changed([&seed, &random_engine_seed_textbox]() {
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
	std::chrono::microseconds delay = 10000us;
	nana::textbox delay_text_box(main_form);
	delay_text_box.caption(std::to_string(delay.count()));
	delay_text_box.set_accept([](wchar_t c) -> bool {
		return c == 8 || c == 127 || std::isdigit(c);
	});
	delay_text_box.events().text_changed([&delay_text_box, &delay]() {
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

	size_t scale = 1500;
	nana::textbox scale_text_box(main_form);
	scale_text_box.set_accept([](wchar_t c) -> bool {
		return c == 8 || c == 127 || std::isdigit(c);
	});
	scale_text_box.events().text_changed([&scale_text_box, &scale]() {
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
				std::string(sorting_algorithms_module::sorting_algorithm_name[sorting_algorithm_id]) +
				", " +
				sequence_generator_module::sequence_generator_name[sequence_generator_id] +
				", " +
				random_engine_name[random_engine_id] + " (with seed = " + std::to_string(seed) + ")" +
				", " +
				"scale = " + std::to_string(scale)
		);

		nana::drawing dw(animation_form);
		polymorphic_random_engine->seed(seed);
		std::vector<int> v = sequence_generator_module::sequence_generator[sequence_generator_id]
				(scale, *polymorphic_random_engine);
		//for (auto e : v) {
		//	std::cout << e << std::endl;
		//}
		std::unique_ptr<animation_base> animation = sorting_algorithms_module::generate_animation[sorting_algorithm_id](
				animation_form, dw, delay);

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
