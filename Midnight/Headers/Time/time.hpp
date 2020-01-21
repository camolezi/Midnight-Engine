#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>    


namespace MN{

	class Timer{
	public:
		//clock
		using Clock = std::chrono::high_resolution_clock;

		//Time point
		using TimePoint = std::chrono::high_resolution_clock::time_point;

		//Duration
		using Duration = std::chrono::duration<double>;


		void start(){ startTime = Clock::now();}
		void stop(){ endTime = Clock::now();}

		double getDuration(){ 
			return std::chrono::duration_cast<Duration>(endTime - startTime).count();}


		private:
			TimePoint startTime;
			TimePoint endTime;
	};
}



#endif