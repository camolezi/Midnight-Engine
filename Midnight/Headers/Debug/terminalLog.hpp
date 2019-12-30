#ifndef TERMINALLOG
#define TERMINALLOG

#include <log.hpp>

//Macros: for using the log and removing logs from deploy version
#ifdef deploy
	#define TERMINAL_LOG(level,text)
	#define TERMINAL_DEBUG(text)
	#define TERMINAL_LOG_LEVEL(level)
#else
	//Using terminal log with a level
	#define TERMINAL_LOG(level,text) \
		if( (int) MN::Debug::TerminalLog::instance().getLevel() < (int)level ) ;\
		else \
			MN::Debug::TerminalLog::instance().write(level) << text

	//Just a quick debug log
	#define TERMINAL_DEBUG(text) \
		if( (int) MN::Debug::TerminalLog::instance().getLevel() < (int)MN::Debug::LogLevel::Debug ) ;\
		else \
			MN::Debug::TerminalLog::instance().write() << text

	//Set log level. Any logs bellow  setted level, wont be printed
	#define TERMINAL_LOG_LEVEL(level) \
		MN::Debug::TerminalLog::instance().setLevel(level)

#endif




namespace MN{
	namespace Debug{

		//Singleton class for terminal logging
		class TerminalLog : public BaseLog{

			public:

				void flush();
				static TerminalLog& instance();

				~TerminalLog();

			private:
				TerminalLog(LogLevel level = LogLevel::Debug): BaseLog{level} {};
		};



	}
}


#endif