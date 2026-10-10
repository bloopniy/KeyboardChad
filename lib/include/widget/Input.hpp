#pragma once
#include <Widget.hpp>

namespace tui {

class Input: public Widget {
private:
	std::string hint; 

	int cursorPosition = 0;
	std::string input = "";
	bool end = false;
	int misses = 0;
public:
	Input(const std::string& hint) :
		 hint(hint) {};

	void render(Window& w, int& x, int& y) override;
	void press(char key);	
	bool isEnd();

	int getWidth() override;
	int getHeight() override;
	int getMisses() { return misses; }

	const std::string& getText() const { return input; };
	void updateSentence(const std::string& newHint);
	~Input() {}
};
}
