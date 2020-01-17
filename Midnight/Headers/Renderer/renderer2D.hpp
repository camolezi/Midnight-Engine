#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP

#include <coreMath.hpp>
#include <renderCommand.hpp>
#include <memory>

namespace MN{


	//Renderer is a static class that contenteins commands
	class Renderer2D{

	public:

		static void start();
		//static void end();

		static void clear();
		static void setClearColor(vec3 color);

		static void beginScene();
		static void endScene();

		static void drawQuad(std::shared_ptr<VertexArray> VAO);


	private:

		static std::unique_ptr<RenderCommand> renderCommand;
		Renderer2D();

	};



}




#endif