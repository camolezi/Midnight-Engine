#ifndef MIDNIGHTAPPLICATION
#define MIDNIGHTAPPLICATION



namespace MN{


	class MidNightApp{

		public:
			virtual void run() = 0;
			virtual ~MidNightApp(){};

			//Define in client
			static MidNightApp * createApp();
	};

}







#endif