#pragma once

#include "Input.hpp"
#include "Window.hpp"
#include "WinSize.hpp"
#include "user_context.hpp"

namespace kbchad {
	using namespace tui;

	class Typing_Window : public Window {
		private:
			std::shared_ptr<Input> input_;
			Typing_Session_Context context_;
		public:
			~Typing_Window() = default;
			Typing_Window (std::shared_ptr<size::WinSize> size, Typing_Session_Context context, Input input):
				Window(size), input_(std::make_shared<Input>(input)), context_(context) {}
			
			void reset_input(std::string& sentence);
			std::shared_ptr<Input> input();
			Typing_Session_Context context();
			void press_key(Key key);
	};
	
	Typing_Window type_window();
	tui::Window statistic_window(Typing_Window& tw);
	tui::Window profile_window(Typing_Session_Context context);
};
