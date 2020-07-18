#ifndef DEBUGHPP
#define DEBUGHPP


//Logs
#include <terminalLog.hpp>

	
//Assertions
#include <assert.h>

#ifdef deploy
	#define ASSERT( condition , text)
#else
	#define ASSERT( condition , text) \
	if(! (condition) ){ \
		TERMINAL_LOG(Log::Error, text); \
		Debug::TerminalLog::instance().flush(); \
		assert(condition); \
	}
	

#endif



#endif