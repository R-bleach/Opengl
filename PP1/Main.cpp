#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {
	//Initiate glfw
	glfwInit();


	//Tell glfw the version of openGL that is being used (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tell the GLFW profile that is being used (Core)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a window object that is 800 by 600 and is named PersonalPortfolio1 and is not fullscreen
	GLFWwindow* window = glfwCreateWindow(800, 600, "PersonalPortfolio1", NULL, NULL);
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
	glViewport(0,0,800,600);

	//Specify background color
	glClearColor(4, 0, 0, 1);
	//Clean the back buffer and assign the new color
	glClear(GL_COLOR_BUFFER_BIT);
	//Swap the back buffer to the front buffer (the front buffer is what ends up on your screen)
	glfwSwapBuffers(window);

	//While loop so the window only closes when i choose to close it
	while (!glfwWindowShouldClose(window)) 
	{
		//Take care of all GLFW events
		glfwPollEvents();
	}
	
	//Delete window
	glfwDestroyWindow(window);

	//End glfw
	glfwTerminate();
	return 0;
}