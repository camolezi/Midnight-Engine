#ifndef MIDNIGHTAPPLICATION
#define MIDNIGHTAPPLICATION

#include <layer.hpp>

namespace MN{

	//Clien aplication is just another layer (maybe later let the client create more layers?)
	class MidnightApp : public Layer{

		public:
			virtual void run(double deltaTime) = 0;
			virtual void startApp() = 0;
			virtual ~MidnightApp(){};

			//Layer stuff
			void update(double deltaTime) { run(deltaTime); }
			void start() override { startApp(); }
			void onAttach() override {} ;
			void onDettach() override {} ;

			std::string getName() override { return "Client Application";}


			//Define in client
			static MidnightApp * createApp();
	};

}



#endif