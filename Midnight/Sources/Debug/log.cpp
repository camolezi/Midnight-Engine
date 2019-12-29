#include <log.hpp>


using namespace MN::Debug;

std::ostringstream& BaseLog::write(LogLevel writeLevel){
	stream<< std::endl;
	stream << (int) writeLevel << ": ";
	return stream;
}
