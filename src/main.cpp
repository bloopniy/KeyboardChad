
#include "Window.hpp"
#include "Util.hpp"
#include "WordList.hpp"
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

	WordList dict = WordList(utils::getHome()->string() +
	"/.local/share/kbchad/wordlist/english.txt");

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

void setCurrentTimeMs(long& time) {
    time = std::chrono::duration_cast<std::chrono::milliseconds>(
       std::chrono::system_clock::now().time_since_epoch() 
    ).count();
}

