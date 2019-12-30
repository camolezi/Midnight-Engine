#include <terminalLog.hpp>


using namespace MN::Debug;

void TerminalLog::flush(){
	std::cerr << stream.str();
	stream.str("");
	stream.str().clear();
}


TerminalLog::~TerminalLog(){
	flush();
}

TerminalLog& TerminalLog::instance(){
	static TerminalLog logInstance;
	return logInstance;
}



