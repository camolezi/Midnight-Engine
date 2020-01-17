#include <renderer2D.hpp>
#include <debug.hpp>


namespace MN{

	std::unique_ptr<RenderCommand> Renderer2D::renderCommand;

	//API independent implementation 
 	void Renderer2D::start(){
 		renderCommand = RenderCommand::create();
 	}


	void Renderer2D::clear(){
		renderCommand->clear();
	}

	void Renderer2D::setClearColor(const vec3& color){
		renderCommand->setClearColor(color);
	}


	void  Renderer2D::beginScene(){

	}

	void Renderer2D::drawQuad(std::shared_ptr<VertexArray> VAO){
		renderCommand->drawIndexed(VAO);
	}


	void Renderer2D::endScene(){

	}



}
