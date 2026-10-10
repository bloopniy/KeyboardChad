
#include "TextWidget.hpp"
#include "window_factory.hpp"
#include "Elements.hpp"
#include "WordList.hpp"
#include "word_counter.hpp"
#include <chrono>

namespace kbchad {
	using namespace tui;
	
	void Typing_Window::reset_input(const std::string sentence) {
		input_->updateSentence(sentence);
		context_.errors      = 0;
		context_.start_time  = 0l;
		context_.end_time    = 0l;
		context_.text_size   = sentence.size();
		context_.words_count = word_count(sentence);
	}

	std::shared_ptr<Input> Typing_Window::input() {
		return input_;
	}

	Typing_Session_Context Typing_Window::context() {
		return context_;
	}

	WordList Typing_Window::word_list() {
		return word_list_;
	}


	void Typing_Window::press_key(Key key) {
		using namespace std::chrono;
		pressOrDefault(key, [&](){
			input_->press(key);
			if (context_.start_time == 0) 
				context_.start_time = duration_cast<milliseconds>(
       				system_clock::now().time_since_epoch())
				.count();

			if (input_->isEnd()) {
				context_.errors      = input_->getMisses();
				context_.end_time    = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();;
			}
		});
	}

	Typing_Window type_window(WordList dict) {

		Typing_Window w = Typing_Window {
			std::make_shared<tui::size::FullScreen>(),
			(Typing_Session_Context){0},
			dict,
			Input{""},
		};

		w.reset_input(w.word_list().generateSentence(12));

 		w.setContent({
			text("KeyboardChad") | centerX,
			w.input() | centerX | centerY,
			text("[esc] exit | [ent] restart") | buttom | centerX
		});	
		
		w.mapping(Key::ENTER, [&](){
			w.reset_input(w.word_list().generateSentence(12));
		});
		return w;
	}

	tui::Window statistic_window(Typing_Window& tw) {
		tui::Window w = tui::Window{std::make_shared<tui::size::FullScreen>()};	
		
		const float acc = tw.context().errors > 0 ? 100.0 - (100.0 * tw.context().errors / tw.context().text_size) : 100;
		const float wpm = (tw.context().words_count * 60000.0 / (tw.context().end_time - tw.context().start_time)) - tw.context().errors;

		// TODO add record notification
		auto stat_text = std::make_shared<tui::TextWidget>(
			"WPM: " + std::to_string(wpm) + 
			" ACC: " + std::to_string(acc) + "%(" + std::to_string(tw.context().errors) + ")e"
		);

		w.setContent({
			text("KeyboardChad") | centerX,
			stat_text | centerX | centerY, 
			text("[esc] exit [entr] restart") | buttom | centerX
		});
	
		w.mapping(Key::ENTER, [&](){
			tw.reset_input(tw.word_list().generateSentence(12));
		});

		return w;
	}

	tui::Window profile_window(Typing_Session_Context c) {
		tui::Window w = tui::Window{std::make_shared<tui::size::FullScreen>()};	

		return w;

	}
};
