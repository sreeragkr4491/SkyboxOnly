
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<GL\glew.h> 
#include"Shader.h"
#include"SOIL2/SOIL2.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Texture.h"
#include"Camera.h"

using namespace std;

void MouseCallback(GLFWwindow* window, double xPos, double yPos);

GLint wid = 2000; //*window variable
GLint height1 = 1500; //*window variable
GLFWwindow* window; //pointer var as window that will hold address only 

int screen_width, screen_height;

//camera
Camera camera(glm::vec3(0, 0, 3.0f));
//timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

GLfloat lastX = 400;
GLfloat lastY = 300;
//bool keys[1024];
bool firstMouse = true;

void main()
{

	glfwInit();

	if (!glfwInit())
	{
		cout << "glfw lib error" << endl;
	}
	else
		cout << "glfw success" << endl;
	window = glfwCreateWindow(wid, height1, "Window with background color", NULL, NULL);


	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)
	{
		cout << "fail to open glew\n";

	}
	else
		cout << "glew works success\n";

	glViewport(0, 0, screen_width, screen_height);
	glEnable(GL_DEPTH_TEST);
	Shader shaders("skybox.vs", "skybox.frag");



	GLfloat skybox[] =
	{
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f

	};

	GLuint skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVBO);
	glGenBuffers(1, &skyboxVAO);
	glBindVertexArray(skyboxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVAO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(skybox), skybox, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//skybox cube mapping
	// Cubemap (Skybox)
	vector<const GLchar*> faces;
	faces.push_back("res/images/right.png");
	faces.push_back("res/images/left.png");
	faces.push_back("res/images/top.png");
	faces.push_back("res/images/bottom.png");
	faces.push_back("res/images/back.png");
	faces.push_back("res/images/front.png");
	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);



	glm::mat4 projection = glm::perspective(camera.GetZoom(),
		(float)screen_width / (float)screen_height, 0.1f, 1000.0f);


	while (!glfwWindowShouldClose(window))
	{
		
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		glm::mat4 view1 = camera.GetViewMatrix();
		glm::mat4 model1;
		

		//skybox
		glm::mat4 view;
		//glDepthFunc(GL_EQUAL);
		shaders.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(shaders.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaders.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);
		glDepthFunc(GL_EQUAL);
		glfwSwapBuffers(window);
		
	}
	/*glDeleteVertexArrays(1, &cubeBuf2);
	glDeleteVertexArrays(1, &skyboxBuf2);
	glDeleteBuffers(1, &cubeBuf1);
	glDeleteBuffers(1, &skyboxBuf1);*/
	glfwTerminate();
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}


