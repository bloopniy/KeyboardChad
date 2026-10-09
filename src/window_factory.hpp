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
	};
	
	Typing_Window typeWindow();
	tui::Window statisticWindow(Typing_Session_Context& context);
	tui::Window profileWindow(Typing_Session_Context& context);
};
