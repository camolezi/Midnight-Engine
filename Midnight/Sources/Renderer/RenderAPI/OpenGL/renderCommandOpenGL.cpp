#include <renderCommand.hpp>
#include <glad.h>
#include <memory>

namespace MN{

	//Only open GL for Now
	std::unique_ptr<RenderCommand> RenderCommand::create(){
		return std::make_unique<RenderCommandOpenGL>();
	}

	void RenderCommandOpenGL::enableDepthTest(){ glEnable(GL_DEPTH_TEST); }

	void RenderCommandOpenGL::setClearColor(const vec3& color) {
		glClearColor(color.at(0), color.at(1), color.at(2), 1.0f);
	}


	void RenderCommandOpenGL::clear(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommandOpenGL::drawIndexed(std::shared_ptr<VertexArray> VAO){
		glDrawElements(GL_TRIANGLES, VAO->getIndexNumber(), GL_UNSIGNED_INT, 0);
	}

	void RenderCommandOpenGL::setViewPort(
	 unsigned int x, 
	 unsigned int y, 
	 unsigned int width, 
	 unsigned int height)
	{
		glViewport(x,y,width,height);
	}


}