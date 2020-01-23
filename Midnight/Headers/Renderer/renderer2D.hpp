#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP

#include <memory>

#include <eventMacro.hpp>

#include <coreMath.hpp>

#include <renderCommand.hpp>
#include <shader.hpp>
#include <vertexArray.hpp>
#include <vertexBuffer.hpp>
#include <indexBuffer.hpp>
#include <texture.hpp>
#include <camera.hpp>
#include <transform.hpp>

namespace MN{


	class Render2DInfo{
	public:
		std::unique_ptr<Shader> shader;
		std::shared_ptr<VertexArray> vertexArray;
	};


	//Renderer is a static class that contains commands
	class Renderer2D{

	public:

		static void start();
		//static void end();

		static void clear();
		static void setClearColor(const vec3& color);
		static void beginScene(std::shared_ptr<Camera> camera);
		static void endScene();
		static void drawQuad(const Transform2D& transform, const vec4& color = {1.0f,1.0f,1.0f,1.0f});
		static void drawQuad(const Transform2D& transform,
							std::shared_ptr<Texture2D> texture, 
							const vec4& color = { 1.0f,1.0f,1.0f,1.0f });
	private:

		static void windowResizeUpdate(MidnightEvent event);

		static Render2DInfo renderInfo;

		static std::shared_ptr<Camera> camera;
		static std::unique_ptr<RenderCommand> renderCommand;
		
		//Default textures
		static std::shared_ptr<Texture2D> whiteTexture;

		Renderer2D();

	};



}




#endif