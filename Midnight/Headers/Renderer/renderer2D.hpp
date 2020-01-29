#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP

//Std
#include <memory>
#include <vector>
//event
#include <eventMacro.hpp>
//math
#include <coreMath.hpp>
//render stuff
#include <renderCommand.hpp>
#include <shader.hpp>
#include <vertexArray.hpp>
#include <vertexBuffer.hpp>
#include <indexBuffer.hpp>
#include <texture.hpp>
#include <camera.hpp>
#include <transform.hpp>


namespace MN{


	//Maybe implement this latter if the renderer support others type of draws
	//Interface
	class RendererCommand {
		virtual float getData() = 0;
	};

	//Renderer is a static class that contains commands
	//Maybe this class can be a concrete singleton (see latter)
	class Renderer2D{
	public:
		//Aux classes
		class Render2DInfo {
		public:
			std::unique_ptr<Shader> shader;
			std::shared_ptr<VertexArray> vertexArray;
		};

		struct DrawQuadCommand {
			DrawQuadCommand(const Transform2D& transform, std::shared_ptr<Texture2D> texture,const vec4& color) :
				modelMatrix{ transform.modelMatrix() }, color{ color }{}
			mat4 modelMatrix;
			vec4 color;
			float textureNumber = 0;
			//std::shared_ptr<Texture2D> texture;
		};

		//Function
		static void start();
		static void end();

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
		static void createInstaceVertexArrayData();

		static Render2DInfo renderInfo;
		static std::shared_ptr<Camera> camera;
		static std::unique_ptr<RenderCommand> renderCommand;
		
		//Default textures
		static std::shared_ptr<Texture2D> whiteTexture;

		//Batch render
		static std::vector<DrawQuadCommand> drawCommandList;
		static std::shared_ptr<VertexBuffer> InstanceVBO;

		Renderer2D();

	};



}




#endif