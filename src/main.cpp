
#include "Window.hpp"
#include "Util.hpp"
#include "FileUtil.hpp"
#include <string>
#include "window_factory.hpp"

void initSettings();

void setCurrentTimeMs(long& time);

using namespace tui;
using namespace utils;

int main() {
   	if (!fileExists(getHome()->string() +
	"/.local/share/kbchad/wordlist"))
        initSettings();

	kbchad::Typing_Window tw = kbchad::type_window();	

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

void initSettings() {
	const std::string p = utils::getHome()->string() +
		"/.local/share/kbchad/wordlist";
	std::filesystem::path settingPath(p);

    utils::mkdir(settingPath);
    if (!utils::fileExists("static/english.txt"))
        return;
	copy(std::filesystem::path("static/english.txt"), 
		std::filesystem::path(p + "/"));
}

