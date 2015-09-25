#ifndef __JINX_UTILS_LOGGING_H
#define __JINX_UTILS_LOGGING_H

#include <iostream>
#include "../../libs/easylogging++.h"

namespace jinx { namespace utils {

	class Logging
	{
	public:
		static void init();
		static void error(const char message[]);
		static void warning(const char message[]);
		static void debug(const char message[]);
		static void info(const char message[]);
	private:
		static std::string signature;
		static void crashHandler(int sig);
	};

} }

#endif