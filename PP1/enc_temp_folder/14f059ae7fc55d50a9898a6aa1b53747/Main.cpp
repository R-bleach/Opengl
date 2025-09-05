#include"Model.h"



const unsigned int width = 800;
const unsigned int height = 800;

int main() {
	//Initiate glfw
	glfwInit();


	//Tell glfw the version of openGL that is being used (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tell the GLFW profile that is being used (Core)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Create a window object that is 800 by 600 and is named PersonalPortfolio1 and is not fullscreen
	GLFWwindow* window = glfwCreateWindow(width, height, "PersonalPortfolio1", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Add window to current context
	glfwMakeContextCurrent(window);

	//Load glad so it can configure OpenGl
	gladLoadGL();

	//Specify the viewport of OpenGl. 
	//Here the start position is 0,0 and end position is 800,600
	glViewport(0, 0, width, height);


	Shader shaderProgram("default.vert", "default.frag");


	Shader lightShader("light.vert", "light.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);


	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	//Texture




	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	std::string modelPath = ("models/ground/scene.gltf");

	Model model((modelPath).c_str(),glm::vec3(0, -5, 0),10);
	Model tree("models/trees/scene.gltf",glm::vec3(0,-5,0),10);


	//While loop so the window only closes when i choose to close it
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0.5f, 0.5f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Tell OpenGL which Shader Program we want to use
		camera.Inputs(window);
		camera.updateMatrix(45.f, 0.1f, 500.f);

		model.Draw(shaderProgram, camera);
		tree.Draw(shaderProgram, camera);

		//Draw the triangle using GL_TRIANGLES primitive
		glfwSwapBuffers(window);

		//Take care of all GLFW events
		glfwPollEvents();
	}

	//Delete all the objects

	shaderProgram.Delete();
	lightShader.Delete();

	//Delete window
	glfwDestroyWindow(window);

	//End glfw
	glfwTerminate();
	std::cout << "Application exited cleanly." << std::endl;
	return 0;
}