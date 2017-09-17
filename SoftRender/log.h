#ifndef __LOG_H__
#define __LOG_H__

#include <string>

namespace SoftRenderer {

	class Log
	{
	public:
		Log() {}
		~Log() {}

		static void log(const char *content) { m_log.append(content); m_log.append("\n"); }

	private:
		static std::string m_log;
	};

#define SLOG Log::log;

}

#endif
