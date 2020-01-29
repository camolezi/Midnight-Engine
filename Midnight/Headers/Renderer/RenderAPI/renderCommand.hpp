#ifndef RENDERCOMMAND_H
#define RENDERCOMMAND_H	

#include <coreMath.hpp>
#include <renderAPI.hpp>
#include <memory>
#include <vertexArray.hpp>
	
namespace MN{


	class RenderCommand{
	public:

		//Commands
		virtual void setClearColor(const vec3& color) = 0;
		virtual void clear() = 0;
		virtual void drawIndexed(std::shared_ptr<VertexArray> VAO) =0;
		virtual void drawIndexedInstanced(std::shared_ptr<VertexArray> VAO, uint32_t number) = 0;
		virtual void enableDepthTest() = 0;
		virtual void enableBlending() = 0;
		virtual void setViewPort( unsigned int x,  unsigned int y, unsigned int width,  unsigned int height) = 0;
		

		//utility
		virtual RenderApi getApi() const = 0;
		virtual ~RenderCommand(){}
		static std::unique_ptr<RenderCommand> create();
	};




	class RenderCommandOpenGL : public RenderCommand{
	public:
		void setClearColor(const vec3& color) override;
		void clear() override;
		RenderApi getApi() const override{return RenderApi::OpenGL;}
		void drawIndexed(std::shared_ptr<VertexArray> VAO) override;
		void drawIndexedInstanced(std::shared_ptr<VertexArray> VAO, uint32_t number) override;
		void enableDepthTest() override;
		void setViewPort( unsigned int x,  unsigned int y,  unsigned int width,  unsigned int height) override;
		void enableBlending() override;

		~RenderCommandOpenGL(){}

		RenderCommandOpenGL(){}
	private:
	};

}


#endif
