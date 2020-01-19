#include <renderer2D.hpp>

#include <debug.hpp>
#include <coreMath.hpp>


//Shader as static for now, need to make a asset system.
static std::string vertexShaderSource = R"(
	#version 330 core
	layout (location = 0) in vec3 aPos;

	uniform mat4 model = mat4(1);
	uniform mat4 viewProj = mat4(1);

	void main(){
		gl_Position = viewProj * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
)";

static std::string fragmentShaderSource = R"(
	#version 330 core

	out vec4 finalColor;

	uniform vec4 uniformColor;
	void main(){
		finalColor = uniformColor;
	}
)";



namespace MN{

	//Static varible init
	std::unique_ptr<RenderCommand> Renderer2D::renderCommand;
	Render2DInfo Renderer2D::renderInfo;
	std::shared_ptr<Camera> Renderer2D::camera;

	//Shoud only be called once at the start of the engine
 	void Renderer2D::start(){
 		renderCommand = RenderCommand::create();

		renderInfo.shader = Shader::create(vertexShaderSource,fragmentShaderSource);
	    float vertices[] = {
	    	//Position  
	         0.5f,  0.5f, 0.0f,   // top right
	         0.5f, -0.5f, 0.0f,  // bottom right
	        -0.5f, -0.5f, 0.0f,  // bottom left
	        -0.5f,  0.5f, 0.0f // top left 
	    };
	    unsigned int indices[] = {  // note that we start from 0!
	        0, 1, 3,  // first Triangle
	        1, 2, 3   // second Triangle
	    };


	    std::shared_ptr<VertexBuffer> VBO = VertexBuffer::create(sizeof(vertices), vertices);
	    VBO->bind();

	    std::shared_ptr<IndexBuffer> EBO = IndexBuffer::create(sizeof(indices), indices);
	    EBO->bind();

	    BufferLayout layout{
	    	{ShaderDataType::FLOAT3, "Position"}
	    };

	    VBO->setLayout(layout);

	    renderInfo.vertexArray = VertexArray::create();
	    renderInfo.vertexArray->setVertexBuffer(VBO);
	    renderInfo.vertexArray->setIndexBuffer(EBO);
 	}


	void Renderer2D::clear(){
		renderCommand->clear();
	}

	void Renderer2D::setClearColor(const vec3& color){
		renderCommand->setClearColor(color);
	}


	void  Renderer2D::beginScene(std::shared_ptr<Camera> cam){
		camera = cam;
	}

	void Renderer2D::drawQuad(const Transform2D& tr,const vec4& color){
		//This bind may be unnecessary

		renderInfo.shader->bind();
  		renderInfo.shader->uniformVec4("uniformColor",color);
  		renderInfo.shader->uniformMat4("viewProj",camera->viewProjMatrix());
  		renderInfo.shader->uniformMat4("model",tr.modelMatrix());

		renderInfo.vertexArray->bind();
		renderCommand->drawIndexed(renderInfo.vertexArray);
	}
	

	void Renderer2D::endScene(){

	}



}
