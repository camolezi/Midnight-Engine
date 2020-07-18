#include <log.hpp>


using namespace MN::Debug;


static std::string enum_to_string(LogLevel writeLevel){
	switch(writeLevel){
		default:
		case (LogLevel::Debug):
			return "Debug"; 
		case (LogLevel::Error):
			return "Error";
		case(LogLevel::Warning):
			return "Warning";
	};
}	



std::ostringstream& BaseLog::write(LogLevel writeLevel){
	stream<< std::endl;
	stream << enum_to_string(writeLevel) << ": ";
	return stream;
}



