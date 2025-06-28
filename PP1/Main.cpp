#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

	//Vertex coordinates of the triangle
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	 // Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,// Upper left corner
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f, 1.0f,// Upper right corner
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f, 0.0f // Lower right corner
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 2, 1, // Upper triangle
		0, 3, 2 // Lower triangle
	};

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
	glViewport(0, 0, 800, 800);


	

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices,sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3 , GL_FLOAT, 8*sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Texture

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("mega-gengar.png", &widthImg, &heightImg, & numColCh,0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");

	shaderProgram.Activate();

	glUniform1i(tex0Uni, 0);

	//While loop so the window only closes when i choose to close it
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0.5f, 0.5f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture);
		//Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		//Draw the triangle using GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		//Take care of all GLFW events
		glfwPollEvents();
	}

	//Delete all the objects
	
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glDeleteTextures(1,&texture);

	//Delete window
	glfwDestroyWindow(window);

	//End glfw
	glfwTerminate();
	std::cout << "Application exited cleanly." << std::endl;
	return 0;
}