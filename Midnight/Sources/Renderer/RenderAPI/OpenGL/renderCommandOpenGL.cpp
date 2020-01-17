#include <renderCommand.hpp>
#include <glad.h>
#include <memory>

namespace MN{

	//Only open GL for Now
	std::unique_ptr<RenderCommand> RenderCommand::create(){
		return std::make_unique<RenderCommandOpenGL>();
	}

	void RenderCommandOpenGL::setClearColor(vec3 color) {
		glClearColor(color.x(), color.y(), color.z(), 1.0f);
	}


	void RenderCommandOpenGL::clear(){
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderCommandOpenGL::drawIndexed(std::shared_ptr<VertexArray> VAO){
		glDrawElements(GL_TRIANGLES, VAO->getIndexNumber(), GL_UNSIGNED_INT, 0);
	}


}