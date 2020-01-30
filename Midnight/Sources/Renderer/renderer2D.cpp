#include <renderer2D.hpp>
#include <debug.hpp>
#include <algorithm>

//Shader as static for now, need to make a asset system.
static std::string TextureVertexShaderSource = R"(
	#version 410 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec2 textureCoordData;

	layout (location = 2) in vec4 ModelMatrix1;
	layout (location = 3) in vec4 ModelMatrix2;
	layout (location = 4) in vec4 ModelMatrix3;
	layout (location = 5) in vec4 ModelMatrix4;
	
	layout (location = 6) in vec4 Color;
	layout (location = 7) in int inTextureNumber;

	out vec2 textureCoord;
	out vec4 FragmentColor;
	flat out int textureNumber;

	uniform mat4 viewProj = mat4(1);

	void main(){
		textureCoord = textureCoordData;
		FragmentColor = Color;
		textureNumber = inTextureNumber;

		gl_Position = viewProj * transpose(mat4(ModelMatrix1,ModelMatrix2,ModelMatrix3,ModelMatrix4)) 
							   * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
)";

static std::string TextureFragmentShaderSource = R"(
	#version 410 core
	
	in vec2 textureCoord;
	in vec4 FragmentColor; 
	flat in int textureNumber;
	
	out vec4 finalColor;
	
	//Will be removed soon
	uniform sampler2D uniformTextures[16];

	void main(){
		finalColor = texture(uniformTextures[textureNumber],textureCoord) * FragmentColor;
	}
)";


namespace MN{

	//Static varible init
	std::unique_ptr<RenderCommand> Renderer2D::renderCommand;
	Renderer2D::Render2DInfo Renderer2D::renderInfo;
	std::shared_ptr<Camera> Renderer2D::camera;
	std::shared_ptr<Texture2D> Renderer2D::whiteTexture;
	std::vector<Renderer2D::DrawQuadCommand> Renderer2D::drawCommandList;


	std::shared_ptr<VertexBuffer> Renderer2D::InstanceVBO;
	std::vector<std::shared_ptr<Texture2D>> Renderer2D::BatchTextures;

	//Shoud only be called once at the start of the engine
 	void Renderer2D::start(){
 		renderCommand = RenderCommand::create();

 		//Configs
 		renderCommand->enableDepthTest();
		renderCommand->enableBlending();

		renderInfo.shader = Shader::create(TextureVertexShaderSource,TextureFragmentShaderSource);
	    float vertices[] = {
	    	//Position  - UV
	         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
	         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
	        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
	        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left 
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
	    	{ShaderDataType::FLOAT3, "Position"},
			{ShaderDataType::FLOAT2, "textureCoord"}
	    };

	    VBO->setLayout(layout);

		renderInfo.vertexArray = VertexArray::create();
	    renderInfo.vertexArray->setVertexBuffer(VBO);
	    renderInfo.vertexArray->setIndexBuffer(EBO);

		
		//Start with 1000 quads allocated (just a random value)
		InstanceVBO = VertexBuffer::create(84 * 1000,NULL,VertexBuffer::type::DynamicDraw);
		InstanceVBO->bind();
		BufferLayout layoutInstanced{
		   {ShaderDataType::FLOAT4, "ModelMatrix1"},
		   {ShaderDataType::FLOAT4, "ModelMatrix2"},
		   {ShaderDataType::FLOAT4, "ModelMatrix3"},
		   {ShaderDataType::FLOAT4, "ModelMatrix4"},
		   {ShaderDataType::FLOAT4, "Color"},
		   {ShaderDataType::INT,    "TextureNumber"}
		};
		InstanceVBO->setLayout(layoutInstanced);
		renderInfo.vertexArray->setVertexBuffer(InstanceVBO);
		

		//Textures
		unsigned char whiteTextureData[] = { 255,255,255,255 };
		whiteTexture = Texture2D::create(1, 1, whiteTextureData);

	    //Events subscription
	    EventSubscribe(WindowResizedEvent,Renderer2D::windowResizeUpdate);

 	}


	void Renderer2D::clear(){
		renderCommand->clear();
	}

	void Renderer2D::setClearColor(const vec3& color){
		renderCommand->setClearColor(color);
	}


	void  Renderer2D::beginScene(std::shared_ptr<Camera> cam){
		camera = cam;
		drawCommandList.clear();
	}

	void Renderer2D::drawQuad(const Transform2D& tr,const vec4& color){
		drawQuad(tr, whiteTexture, color);
	}


	void Renderer2D::drawQuad(const Transform2D& transform, std::shared_ptr<Texture2D> texture, const vec4& color){	

		auto it = std::find(BatchTextures.begin(), BatchTextures.end(), texture);
		if (it != BatchTextures.end()) {
			//in the list
			drawCommandList.push_back(DrawQuadCommand{ transform, color,static_cast<int>(it - BatchTextures.begin()) });
		}
		else {
			BatchTextures.push_back(texture);
			drawCommandList.push_back(DrawQuadCommand{ transform, color,static_cast<int>(BatchTextures.size() - 1) });
		}
	
	}


	void Renderer2D::drawSceneBatchRenderer() {

		//Update instance buffer with new data from the current frame 
		InstanceVBO->updateData(drawCommandList.size() * sizeof(DrawQuadCommand), drawCommandList.data());
		
		renderInfo.shader->bind();
		renderInfo.shader->uniformMat4("viewProj", camera->viewProjMatrix());
		renderInfo.vertexArray->bind();
		

		//Remove this array of samplers (Use a texture atlas or a texture array)
		int* textureNumberData = new int[BatchTextures.size()];
		for (int aux = 0; aux < BatchTextures.size(); aux++) {
			textureNumberData[aux] = aux;
			BatchTextures[aux]->bind(aux);
		}
		renderInfo.shader->uniformIntArray("uniformTextures", textureNumberData, BatchTextures.size());

		renderCommand->drawIndexedInstanced(renderInfo.vertexArray, drawCommandList.size());
		delete[] textureNumberData;
	}
	
	void Renderer2D::endScene(){
		drawSceneBatchRenderer();
	}

	void Renderer2D::windowResizeUpdate(MidnightEvent event){
		auto resizedEvent = downcast_event_ptr<WindowResizedEvent>(event);
		//Fow now (only one view port)
		renderCommand->setViewPort(0,0,resizedEvent->getWidth(),resizedEvent->getHeight());
	}


	
	void Renderer2D::end() {
		renderCommand.release();
	}

}
