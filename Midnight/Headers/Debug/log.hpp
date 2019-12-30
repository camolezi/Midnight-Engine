#ifndef LOG
#define LOG

#include <iostream>   //cerr
#include <sstream>      // std::ostringstream
#include <string>


namespace MN{
	namespace Debug{

		enum class LogLevel{
			Error,
			Warning,
			Debug
		};

		//Interface for log class
		class ILog{
			public:
				virtual ~ILog(){}

				virtual std::ostringstream& write(LogLevel writeLevel) = 0;
				virtual LogLevel getLevel() = 0;
				virtual void setLevel(LogLevel level) = 0;

				virtual void flush() = 0;

		};

		//Class for debug Logs and error messages
		class BaseLog : public ILog{
			public:

				virtual ~BaseLog(){}
				virtual LogLevel getLevel(){return _level;}
				virtual void setLevel(LogLevel level){ _level = level;}

				virtual std::ostringstream& write(LogLevel writeLevel = LogLevel::Debug);

			protected:

				BaseLog(LogLevel level = LogLevel::Debug): _level{level} {};
				std::ostringstream stream;

			private:
				LogLevel _level;
				
		};

		//Implement later?
		class FileLog: public BaseLog{
			public:

			private:
		};

		//Implement later?
		class GraphicalLog: public BaseLog{
			public:

			private:
		};



	}
}


using Log  = MN::Debug::LogLevel;

#endif