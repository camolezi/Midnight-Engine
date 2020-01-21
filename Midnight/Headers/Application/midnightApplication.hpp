#ifndef MIDNIGHTAPPLICATION
#define MIDNIGHTAPPLICATION



namespace MN{


	class MidnightApp{

		public:
			virtual void run(double deltaTime) = 0;
			virtual void start() = 0;
			virtual ~MidnightApp(){};

			//Define in client
			static MidnightApp * createApp();
	};

}







#endif