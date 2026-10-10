#pragma once
#include "Keys.hpp"
#include "WinSize.hpp"
#include <Pixel.hpp>
#include <Widget.hpp>
#include <functional>
#include <initializer_list>
#include <memory>
#include <vector>

namespace tui {

class Widget;

using WinSize = std::shared_ptr<size::WinSize>;
class Window {
private:
	Elements elements;
	WinSize sz;
	
	std::vector<Pixel> content;
	std::vector<Pixel> oldContent;

	std::unordered_map<Key, std::function<void()>> mappings;	

	int lastWidht  = 0;
	int lastHeight = 0;

    void prepareContent();
    void drawElements();
    void renderPixels();
    void cacheSize();
    void updateContent();
    Pixel& oldPixelAt(int x, int y);
public:
	Window(WinSize);

	int getWidth();
	int getHeight();
	
	bool needUpdate();
	Pixel& pixelAt(int x, int y);

	void setContent(std::initializer_list<Element> content);
	void setContent(Elements& content);
	
	void mapping(Key key,const std::function<void()>& callback);
	void press(Key k);
	void pressOrDefault(Key k, std::function<void()>);

	void render();
    void renderDiff();
	bool empty() const;
};
} // namespace tui
