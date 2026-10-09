
#include "TextWidget.hpp"
#include "window_factory.hpp"
#include "Elements.hpp"
#include "word_counter.hpp"

namespace kbchad {
	using namespace tui;

	void Typing_Window::reset_input(std::string& sentence) {
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

	Typing_Window typeWindow() {
		Typing_Window w = Typing_Window {
			std::make_shared<tui::size::FullScreen>(),
			(Typing_Session_Context){0},
			Input{ "todo this bullshit" },
		};

 		w.setContent({
			text("KeyboardChad"),
			w.input() | centerX | centerY,
			text("[esc] exit | [ent] restart")
		});	
		
		w.mapping(Key::ENTER, reset_input);
		return w;
	}

	tui::Window statisticWindow(Typing_Session_Context& c) {
		tui::Window w = tui::Window{std::make_shared<tui::size::FullScreen>()};	
		
		const float acc = c.errors > 0 ? 100.0 - (100.0 * c.errors / c.text_size) : 100;
		const float wpm = (c.words_count * 60000.0 / (c.end_time - c.start_time)) - c.errors;

		// TODO add record notification
		auto stat_text = std::make_shared<tui::TextWidget>(
			"WPM: " + std::to_string(wpm) + " ACC: " + std::to_string(acc) + "%"
		);

		w.setContent({
			text("KeyboardChad") | centerX,
			stat_text | centerX | centerY, 
			text("[esc] exit [entr] restart") | buttom | centerX
		});

		return w;
	}

	tui::Window profileWindow(Typing_Session_Context& c) {
		tui::Window w = tui::Window{std::make_shared<tui::size::FullScreen>()};	

		return w;

	}
};
