#include "SceneRenderer.h"
#include"VertexData.h"
#include"DeltaTime.h"

Scene::Scene() {
	//window = nullptr;

	//window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	InitGLFW();
	CreateWindow();
	InitGlad();
	SetWindowParameters();
	RegisterEvents();
	UseShaders();

	
	
	
}
//Scene::~Scene() {
//	//shaderProgram.Delete();
//	/*vao.Delete();
//	vbo.Delete(); //replace this
//	ebo.Delete();*/
//
//
//	//glfwTerminate();
//}

//void Scene::SetDeltaTime() {
//	float currentFrame = glfwGetTime();
//	deltaTime = currentFrame - lastFrame;
//	lastFrame = currentFrame;
//}









void Scene::InitGLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
void Scene::CreateWindow() {
	window = glfwCreateWindow(WIDTH, HEIGHT, "Scene", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	//return bool?
}
void Scene::InitGlad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
}

void Scene::SetWindowParameters() {

	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //enable alpha values;

	glEnable(GL_DEPTH_TEST); //to prevent rendering back vertices
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
}
void Scene::RegisterEvents() {
	glfwSetFramebufferSizeCallback(window, Scene::framebuffer_size_callback);
	glfwSetKeyCallback(window, Controller::SwitchState); //keyboard
	glfwSetCursorPosCallback(window, Controller::MouseCallback); //mouse 
}

void Scene::UseShaders() {
	shaderProgram = Shader("default.vert", "default.frag");
	shaderProgram.Activate();
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void Scene::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}





void Scene::DrawGrid() {
	shaderProgram.SetMatrix(Camera::GetProjectionMatrix() * Camera::GetViewMatrix());
	shaderProgram.SetAlpha(0.7f);

	shaderProgram.SetColor(glm::vec3(1, 0, 0));
	VertexData::GetXVAO().Bind();
	glDrawArrays(GL_LINES, 0, 2);

	shaderProgram.SetColor(glm::vec3(0, 1, 0));
	VertexData::GetZVAO().Bind();
	glDrawArrays(GL_LINES, 0, 2);

	shaderProgram.SetAlpha(0.9f);
	shaderProgram.SetColor(glm::vec3(0.2f, 0.2f, 0.2f));
	VertexData::GetGridVAO().Bind();
	glDrawArrays(GL_LINES, 0, VertexData::GetGridSize());

}

void Scene::Update() { // into main loop
	shouldClose = glfwWindowShouldClose(window);
	if (!shouldClose)
	{
		
		Controller::MoveCamera(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.SetColor(glm::vec3(0.2f, 0.4f, 0.8f));
		shaderProgram.SetAlpha(1.0f);

		glm::vec3 v = Controller::GetTransformVector();
		for (Shape* object : ObjectManager::GetSelectedObjects()) {
			if (Controller::GetTranslating())
				object->Move(v * DeltaTime::GetDeltaTime());
			if (Controller::GetScaling())
				object->Scale(v * DeltaTime::GetDeltaTime());
			if (Controller::GetRotating())
				object->Rotate(v * DeltaTime::GetDeltaTime());
		}
		for (Shape* object : ObjectManager::GetCreatedObjects()) {
			shaderProgram.SetMatrix(Camera::GetProjectionMatrix() * Camera::GetViewMatrix() * Shape::GetObjectMatrix(object)); // projection * view * local * vector; 
			object->Bind();
			glDrawElements(GL_TRIANGLES, object->GetVertexCount(), GL_UNSIGNED_INT, 0);
		}
		DrawGrid();

		glfwSwapBuffers(window);
		glfwPollEvents();
		return;
	}
	shaderProgram.Delete();
	VertexData::GetConeVAO().Delete();
	VertexData::GetCubeVAO().Delete();
	VertexData::GetCylinderVAO().Delete();
	VertexData::GetSphereVAO().Delete();
	VertexData::GetGridVAO().Delete();
	VertexData::GetXVAO().Delete();
	VertexData::GetZVAO().Delete();
	glfwTerminate();
}




GLFWwindow* Scene::GetWindow() {
	return window;
}
Shader Scene::GetShaderProgram() {
	return shaderProgram;
}
bool Scene::GetShouldClose() {
	return shouldClose;
}


