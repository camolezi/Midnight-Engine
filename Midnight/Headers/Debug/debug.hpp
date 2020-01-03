#ifndef DEBUGHPP
#define DEBUGHPP


//Logs
#include <terminalLog.hpp>

	
//Assertions
#include <assert.h>

#ifdef deploy
	#define ASSERT(condition)
#else
	#define ASSERT(condition) assert(condition)
#endif



#endif