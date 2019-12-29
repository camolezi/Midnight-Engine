#ifndef TERMINALLOG
#define TERMINALLOG

#include <log.hpp>


namespace MN{
	namespace Debug{

		class TerminalLog : public BaseLog{

			public:

				void flush();
				TerminalLog(LogLevel level = LogLevel::LogDebugLow): BaseLog{level} {};

				~TerminalLog();

			private:

		};


	}
}


#endif