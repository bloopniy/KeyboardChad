#pragma once

namespace kbchad {	
	struct Typing_Session_Context {
		long start_time;
		long end_time;
		int errors;
		int text_size;
		int words_count;
	};

	// TODO
	struct User_Context {
		int tests_completed;
	};
};
