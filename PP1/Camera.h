#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#define GLM_ENABLE_EXPERIMENTAL

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
	public:
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.f, 0.f, -1.f);
		glm::vec3 Up = glm::vec3(0.f, 1.f, 0.f);
		glm::mat4 CameraMatrix = glm::mat4(1.f);

		bool firstClick = true;

		int width;
		int height;	

		float speed = 0.5f;
		float sensitivity = 100.f;

		Camera(int width, int height, glm::vec3 position);

		void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void Matrix(Shader& shader, const char* uniform);

		void Inputs(GLFWwindow* window);
};


#endif
