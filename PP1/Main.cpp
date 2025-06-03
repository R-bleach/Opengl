#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {
	//Initiate glfw
	glfwInit();


	//Tell glfw the version of openGL that is being used (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tell the GLFW profile that is being used (Core)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Vertex coordinates of the triangle
	GLfloat vertices[] =
	{
		-0.4f,-0.4f,0.0f, //lower left corner
		0.6f, -0.4f, 0.0f, //lower right corner
		0.0f, 0.6f,0.0f //top corner
	};

		//Create a window object that is 800 by 600 and is named PersonalPortfolio1 and is not fullscreen
	GLFWwindow * window = glfwCreateWindow(800, 600, "PersonalPortfolio1", NULL, NULL);
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
	glViewport(0, 0, 800, 600);


	//Create Vertex Shader Object and get refrence
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	//Create Fragment Shader Object and get refrence
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Compile the Fragment Shader into machine code
	glCompileShader(fragmentShader);

	//Create Shader Program Object and get its refrence
	GLuint shaderProgram = glCreateProgram();

	//Attach the Vertex and Fragment shader to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Wrap up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);


	//Delete the Shader Objects because they have been added to the shader program 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Create refrence container for the Vertex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

	//Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	//Bind the VBO and specify that it is an Array Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	//Enable the Vertex Attributes so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VAO and VBO to 0 so wo don't modify it on accident
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Specify background color
	glClearColor(0, 0.5f, 0.5f, 1);
	//Clean the back buffer and assign the new color
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Swap the back buffer to the front buffer (the front buffer is what ends up on your screen)
	glfwSwapBuffers(window);

	//While loop so the window only closes when i choose to close it
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0.5f, 0.5f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		//Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		//Draw the triangle using GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES,0,3);
		glfwSwapBuffers(window);

		//Take care of all GLFW events
		glfwPollEvents();
	}

	//Delete all the objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//Delete window
	glfwDestroyWindow(window);

	//End glfw
	glfwTerminate();
	std::cout << "Application exited cleanly." << std::endl;
	return 0;
}