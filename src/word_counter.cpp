
#include "word_counter.hpp"
#include <sstream>
#include <iterator>


namespace kbchad {

	// Source - https://stackoverflow.com/a/3672259
	// Posted by Loki Astari, modified by community. See post 'Timeline' for change history
	// Retrieved 2026-10-09, License - CC BY-SA 2.5
	unsigned int word_count(std::string const& str) {
   		std::stringstream stream(str);
    	return std::distance(
			std::istream_iterator<std::string>(stream),
			std::istream_iterator<std::string>()
		);
	}

};
