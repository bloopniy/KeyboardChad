#include "Keys.hpp"
#include "Input.hpp"
#include "Window.hpp"

namespace tui {

	void renderCursor(Window& w, int x, int y) {
		w.pixelAt(x, y).isInvert = true; 
	}

	void applyStyles(
		int index,
		Pixel& pixel,
		const std::string& hint,
		const std::string& input
	) 
	{		
		if (input.size() <= index) return;
		if (hint[index] == input[index]) pixel.isBold = true;
		else pixel.isStrike = true;
	}

	void Input::render(Window& w, int& x, int& y) {
		for (int i = 0; i < hint.size(); i++) {
			if (i == cursorPosition) {
				renderCursor(w, x, y);
			}

			w.pixelAt(x, y).pixelContent = hint[i];
			applyStyles(i, w.pixelAt(x, y), hint, input);
			x++;
			if (x > w.getWidth()) {
				x = 1;
                y += 1;
			}
		}
    }
	
	void Input::press(char key) {
		if (isEnd()) return;
		
		switch (key) {
			case Key::BACKSPACE:
				if (!input.empty() && cursorPosition > 0) {
					input.pop_back();
					cursorPosition--;
				}
				break;

			case Key::CTRL_BACKSPACE: {
				int newPos = input.find_last_of(' ') + 1;
				if (newPos == std::string::npos) newPos = 0;

				if (newPos != std::string::npos) {
					input = input.substr(0, newPos);
					cursorPosition=newPos;
				}
				break;
			}

			default:
				if (cursorPosition < hint.size()) {
					input+=key;
					cursorPosition++;
					

					if (input[cursorPosition-1] 
							!= hint[cursorPosition-1])
						misses++;

					if (cursorPosition == hint.size()) 
						end = true;
				}
				break;
		}	
	}
	void Input::updateSentence(const std::string& newHint) {
		hint = newHint;
		cursorPosition = 0;
		misses = 0;
		input = "";
		end = false;
	}
	bool Input::isEnd() { return end; }
	int Input::getHeight() { return hint.size(); };
	int Input::getWidth() { return hint.size(); };
}
