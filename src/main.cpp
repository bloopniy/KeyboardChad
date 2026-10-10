#include "WordList.hpp"
#include "Util.hpp"
#include "FileUtil.hpp"
#include "window_factory.hpp"

using namespace tui;
using namespace utils;

void initSettings() {
	const std::string p = getHome()->string() + "/.local/share/kbchad/wordlist";
	std::filesystem::path settingPath(p);

    mkdir(settingPath);
    if (!fileExists("static/english.txt"))
        return;
	copy(std::filesystem::path("static/english.txt"), 
		std::filesystem::path(p + "/"));
}

int main() {
   	if (!fileExists(getHome()->string() + "/.local/share/kbchad/wordlist"))
        initSettings();

	WordList list = WordList{utils::getHome()->string() + "/.local/share/kbchad/wordlist/english.txt"};

	kbchad::Typing_Window tw = kbchad::type_window(list);

	util::enableAlterScr();
	util::hideCursor();

	while (true) {
		if (!tw.input()->isEnd()) {
			tw.renderDiff();
			char ch = util::getch();
			if (ch == Key::ESC) break;
			tw.press_key((Key)ch);
		} else {
			Window statistic = kbchad::statistic_window(tw);
			util::clearScr();
			statistic.renderDiff();	
			char ch = util::getch();
			if (ch == Key::ESC) break;
			statistic.press((Key)ch);
		}
	}

	util::disablAlterScr();
	util::showCursor();
    return 0;
}
