#include "Pixel.hpp"
#include <iostream>
#include <Window.hpp>
#include <Util.hpp>

namespace tui { 

	Window::Window(WinSize size) : 
		sz(size), 
		content(size->get_width() * size->get_height()), 
	    oldContent(size->get_width() * size->get_height()),
        elements({}) {
			lastWidht  = size->get_width();
			lastHeight = size->get_height();
		}



	int Window::getWidth() {
		return sz->get_width();
	}

	int Window::getHeight() {
		return sz->get_height();
	}

	bool Window::needUpdate() {
		return !(lastWidht  == sz->get_width()
			  && lastHeight == sz->get_height());
	}

	Pixel& Window::pixelAt(int x, int y) {
		int loc = (sz->get_width() * y) + x;
		return content.at(loc);
	}
	
	Pixel& Window::oldPixelAt(int x, int y) {	
	    int loc = (sz->get_width() * y) + x;
	    return oldContent.at(loc);
	}
	void renderPixelWithStyle(const Pixel& pixel) {

		if (pixel.isBold) std::cout << "\x1B[1m";
		if (pixel.isInvert) std::cout << "\x1B[7m";
		if (pixel.isUnderl) std::cout << "\x1B[4m";
		if (pixel.isItal) std::cout << "\x1B[3m";
		if (pixel.isStrike) std::cout << "\x1B[9m";

		std::cout << pixel.pixelContent;
		std::cout << "\x1B[0m";
	}

    void Window::prepareContent() {
        for (auto& pixel : content) {
			pixel.clearStyles();
			pixel.pixelContent = ' ';
		}
    }

    void Window::drawElements() {
		int x = 1; int y = 1;

		for (int i = 0; i < elements.size(); i++) {
			elements[i]->render(*this, x, y);
			if (y <= getHeight()) y += 1;
			x = 0;
		}
    }

    void Window::renderPixels() {
    	for (const Pixel& p : content) {
            renderPixelWithStyle(p); 
        }
		std::cout << std::endl;
    }

    void Window::cacheSize() {
		lastWidht = sz->get_width();
		lastHeight = sz->get_height();	
    }

    void Window::updateContent() {
        content.resize(sz->get_width()*sz->get_height(), Pixel{});
        oldContent.resize(sz->get_width()*sz->get_height(), Pixel{});
    }
    
	void Window::render() {	
		if (needUpdate())
            updateContent(); 

        prepareContent();
        drawElements();
        renderPixels();

        cacheSize();
	}

	void Window::renderDiff() {	 
        if (needUpdate())
            updateContent(); 

        prepareContent();
        drawElements();
        if (content.size() == oldContent.size() && !needUpdate()) {
            for (int x = 0; x < sz->get_width(); x++) {
                for (int y = 0; y < sz->get_height(); y++) {
                    if (pixelAt(x, y) == oldPixelAt(x, y))
                        continue;
                    
                    util::moveCursor(x, y);
                    renderPixelWithStyle(pixelAt(x, y));
                }
            }
            std::cout << std::endl;
            util::moveCursor(0,0);

            cacheSize();
        } else {
            renderPixels();
            cacheSize();
        } 
        std::swap(oldContent, content); 
	}
	
	bool Window::empty() const {
		return elements.empty();
	}

	void Window::mapping(Key k, const std::function<void()>& callback) {
		mappings[k] = callback;
	}

	void Window::press(Key k) {
		if (!mappings.contains(k)) return;
		mappings.at(k)();
	}

	void Window::pressOrDefault(Key k, std::function<void()> def) {
		if (!mappings.contains(k)) {
			def(); 
			return;
		}
		mappings.at(k)();
	}

    void Window::setContent(Elements& newElems) {
		elements = newElems;
	}

	void Window::setContent(std::initializer_list<Element> newElems) {
		elements = newElems;
	}

}
