//1.add all audio libraries into the properties
//2.attch some audio files in resource
//3.attach headerfiles related to audio at the top of program
//4.create a variable for sound engine 
//5.call this sound engine variable with resouce audio wherever you want to call



//Reflection and refraction of skybox texture on 3d objects
//for reflection and refraction only need to change from the frag shader of the object
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
#include"Model.h"
#include<irrKlang.h>
using namespace irrklang;
using namespace std;


ISoundEngine *soundEngine = createIrrKlangDevice();

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

GLint wid = 2000; //*window variable
GLint height1 = 1500; //*window variable
GLFWwindow* window; //pointer var as window that will hold address only 

int screen_width, screen_height;

GLfloat transx3 = 0; //  step 2: for translation in x axis
GLfloat transy3 = 0; //  step2: for translation in y axis


//camera
Camera camera(glm::vec3(0, 0, 3.0f));
bool keys[1024];
GLfloat lastX = 400;
GLfloat lastY = 300;
bool firstMouse = true;

//timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


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
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)
	{
		cout << "fail to open glew\n";

	}
	else
		cout << "glew works success\n";

	glViewport(0, 0, screen_width, screen_height);
	glEnable(GL_DEPTH_TEST);  // ***************for objects
	Shader shaders("skybox.vs", "skybox.frag");

	Shader shader("res/model/modelLoading.vs", "res/model/modelLoading.frag");

	Shader shader1("res/model/modelLoading1.vs", "res/model/modelLoading1.frag");

	Shader shader2("modelLoading2.vs", "modelLoading2.frag");

	Shader shaders1("cube.vs", "cube.frag");
	Shader shaders2("Cube1.vs", "Cube1.frag");

	char tmp[] = "res/models2/Lamborghini_Aventador.obj";
	Model ourModel(tmp);

	char tmp1[] = "res/models1/nanosuit.obj";
	Model ourModel1(tmp1);

	//light and cube**********
	Shader shadercube("cube2.vs", "cube2.frag");
	Shader shaderlight("Light.vs", "Light.frag");

	//audio call
	soundEngine->play2D("res/audio/breakout.mp3", GL_TRUE);

	//UPPER LIGHT
	GLfloat vertices1[] =
	{
		// step-1 change vertices as cube and add color too
		-0.1f, -0.1f, -0.1f,     1.0, 1.0, 1.0,
		 0.1f, -0.1f, -0.1f,     1.0, 1.0, 1.0,
		 0.1f,  0.1f, -0.1f,     1.0, 1.0, 1.0,
		 0.1f,  0.1f, -0.1f,     1.0, 1.0, 1.0,
		-0.1f,  0.1f, -0.1f,     1.0, 1.0, 1.0,
		-0.1f, -0.1f, -0.1f,     1.0, 1.0, 1.0,

		-0.1f, -0.1f, 0.1f,      1.0, 1.0, 1.0,
		 0.1f, -0.1f, 0.1f,      1.0, 1.0, 1.0,
		 0.1f, 0.1f, 0.1f,       1.0, 1.0, 1.0,
		 0.1f, 0.1f, 0.1f,       1.0, 1.0, 1.0,
		-0.1f, 0.1f, 0.1f,       1.0, 1.0, 1.0,
		-0.1f, -0.1f, 0.1f,      1.0, 1.0, 1.0,

		-0.1f, 0.1f, 0.1f,       1.0, 1.0, 1.0,
		-0.1f, 0.1f, -0.1f,      1.0, 1.0, 1.0,
		-0.1f, -0.1f, -0.1f,     1.0, 1.0, 1.0,
		-0.1f, -0.1f, -0.1f,	 1.0, 1.0, 1.0,
		-0.1f, -0.1f, 0.1f,		 1.0, 1.0, 1.0,
		-0.1f, 0.1f, 0.1f,		 1.0, 1.0, 1.0,

		0.1f, 0.1f, 0.1f,		 1.0, 1.0, 1.0,
		0.1f, 0.1f, -0.1f,		 1.0, 1.0, 1.0,
		0.1f, -0.1f, -0.1f,		 1.0, 1.0, 1.0,
		0.1f, -0.1f, -0.1f,		 1.0, 1.0, 1.0,
		0.1f, -0.1f, 0.1f,		 1.0, 1.0, 1.0,
		0.1f, 0.1f, 0.1f,		 1.0, 1.0, 1.0,

		-0.1f, -0.1f, -0.1f,	1.0, 1.0, 1.0,
		0.1f, -0.1f, -0.1f,		1.0, 1.0, 1.0,
		0.1f, -0.1f, 0.1f,		1.0, 1.0, 1.0,
		0.1f, -0.1f, 0.1f,		1.0, 1.0, 1.0,
		-0.1f, -0.1f, 0.1f,		1.0, 1.0, 1.0,
		-0.1f, -0.1f, -0.1f,	1.0, 1.0, 1.0,

		-0.1f, 0.1f, -0.1f,		1.0, 1.0, 1.0,
		0.1f, 0.1f, -0.1f,		1.0, 1.0, 1.0,
		0.1f, 0.1f, 0.1f,		1.0, 1.0, 1.0,
		0.1f, 0.1f, 0.1f,		1.0, 1.0, 1.0,
		-0.1f, 0.1f, 0.1f,		1.0, 1.0, 1.0,
		-0.1f, 0.1f, -0.5f,		1.0, 1.0, 1.0,
		//end

	};

	//OBJECT
	GLfloat vertices3[] =
	{

		// step-1 change vertices as cube and add color too

		//top				
		//coordinates			color				normal
		-0.1f, 0.1f, -0.1f,		1.0, 1.0, 0.0,		0.0f, 1.0f, 0.0f,
		 0.1f, 0.1f, -0.1f,		1.0, 1.0, 0.0,		0.0f, 1.0f, 0.0f,
		 0.1f, 0.1f,  0.1f,		1.0, 1.0, 0.0,		0.0f, 1.0f, 0.0f,
		 0.1f, 0.1f,  0.1f,		1.0, 1.0, 0.0,		0.0f, 1.0f, 0.0f,
		-0.1f, 0.1f,  0.1f,		1.0, 1.0, 0.0,		0.0f, 1.0f, 0.0f,
		-0.1f, 0.1f, -0.1f,		1.0, 1.0, 0.0,		0.0f, 1.0f, 0.0f,

		//back
		-0.1f, -0.1f, -0.1f,	1.0, 0.0, 0.0,		0.0f, 0.0f, -1.0f,
		 0.1f, -0.1f, -0.1f,	1.0, 0.0, 0.0,		0.0f, 0.0f, -1.0f,
		 0.1f,  0.1f, -0.1f,	1.0, 0.0, 0.0,		0.0f, 0.0f, -1.0f,
		 0.1f,  0.1f, -0.1f,	1.0, 0.0, 0.0,		0.0f, 0.0f, -1.0f,
		-0.1f,  0.1f, -0.1f,	1.0, 0.0, 0.0,		0.0f, 0.0f, -1.0f,
		-0.1f, -0.1f, -0.1f,	1.0, 0.0, 0.0,		0.0f, 0.0f, -1.0f,

		//front
		-0.1f, -0.1f, 0.1f,		0.0, 1.0, 0.0,		0.0f, 0.0f, 1.0f,
		 0.1f, -0.1f, 0.1f,		0.0, 1.0, 0.0,		0.0f, 0.0f, 1.0f,
		 0.1f,  0.1f, 0.1f,		0.0, 1.0, 0.0,		0.0f, 0.0f, 1.0f,
		 0.1f,  0.1f, 0.1f,		0.0, 1.0, 0.0,		0.0f, 0.0f, 1.0f,
		-0.1f,  0.1f, 0.1f,		0.0, 1.0, 0.0,		0.0f, 0.0f, 1.0f,
		-0.1f, -0.1f, 0.1f,		0.0, 1.0, 0.0,		0.0f, 0.0f, 1.0f,

		//left
		-0.1f,  0.1f,  0.1f,	0.0, 0.0, 1.0,		-1.0f, 0.0f, 0.0f,
		-0.1f,  0.1f, -0.1f,	0.0, 0.0, 1.0,		-1.0f, 0.0f, 0.0f,
		-0.1f, -0.1f, -0.1f,	0.0, 0.0, 1.0,		-1.0f, 0.0f, 0.0f,
		-0.1f, -0.1f, -0.1f,	0.0, 0.0, 1.0,		-1.0f, 0.0f, 0.0f,
		-0.1f, -0.1f,  0.1f,	0.0, 0.0, 1.0,		-1.0f, 0.0f, 0.0f,
		-0.1f,  0.1f,  0.1f,	0.0, 0.0, 1.0,		-1.0f, 0.0f, 0.0f,

		//right
		0.1f,  0.1f,  0.1f,		0.0, 1.0, 1.0,		1.0f, 0.0f, 0.0f,
		0.1f,  0.1f, -0.1f,		0.0, 1.0, 1.0,		1.0f, 0.0f, 0.0f,
		0.1f, -0.1f, -0.1f,		0.0, 1.0, 1.0,		1.0f, 0.0f, 0.0f,
		0.1f, -0.1f, -0.1f,		0.0, 1.0, 1.0,		1.0f, 0.0f, 0.0f,
		0.1f, -0.1f,  0.1f,		0.0, 1.0, 1.0,		1.0f, 0.0f, 0.0f,
		0.1f,  0.1f,  0.1f,		0.0, 1.0, 1.0,		1.0f, 0.0f, 0.0f,

		//bottom
		-0.1f, -0.1f, -0.1f,	1.0, 0.0, 1.0,		0.0f, -1.0f, 0.0f,
		 0.1f, -0.1f, -0.1f,	1.0, 0.0, 1.0,		0.0f, -1.0f, 0.0f,
		 0.1f, -0.1f,  0.1f,	1.0, 0.0, 1.0,		0.0f, -1.0f, 0.0f,
		 0.1f, -0.1f,  0.1f,	1.0, 0.0, 1.0,		0.0f, -1.0f, 0.0f,
		-0.1f, -0.1f,  0.1f,	1.0, 0.0, 1.0,		0.0f, -1.0f, 0.0f,
		-0.1f, -0.1f, -0.1f,	1.0, 0.0, 1.0,		0.0f, -1.0f, 0.0f

		//end

	};

	GLfloat cube[] =
	{
		 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f

	};

	GLfloat skybox[] =
	{
		 //Positions
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


	GLuint VBO[4], VAO[4];//vertex buffer obj//vert array obj
	glGenVertexArrays(4, VAO);
	glGenBuffers(4, VBO);


	//-----------------------------------LIGHT

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//vertices1
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	////texture
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(2);


	////-----------------------------------OBJECT

	glBindVertexArray(VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	//vertices3
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//cube1
	GLuint cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	//vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//cube2
	GLuint cubeVAO2, cubeVBO2;
	glGenVertexArrays(1, &cubeVAO2);
	glGenBuffers(1, &cubeVBO2);
	glBindVertexArray(cubeVAO2);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO2);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	//vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//skybox
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
	//Cubemap (Skybox)
	vector<const GLchar*> faces;
	faces.push_back("res/Skybox/skybox-txtrs/dark_rt.png");   
	faces.push_back("res/Skybox/skybox-txtrs/dark_lf.png");
	faces.push_back("res/Skybox/skybox-txtrs/dark_up.png");
	faces.push_back("res/Skybox/skybox-txtrs/dark_dn.png");
	faces.push_back("res/Skybox/skybox-txtrs/dark_bk.png");
	faces.push_back("res/Skybox/skybox-txtrs/dark_ft.png");
	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);


	glm::mat4 projection = glm::perspective(camera.GetZoom(),
		(float)screen_width / (float)screen_height, 0.1f, 1000.0f);


	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		DoMovement();

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//cube1
		shaders1.Use();
		glm::mat4 view2 = camera.GetViewMatrix();
		glm::mat4 model2;
		GLint modellocation = glGetUniformLocation(shaders1.Program, "model");
		GLint viewlocation = glGetUniformLocation(shaders1.Program, "view");
		GLint projectionlocation = glGetUniformLocation(shaders1.Program, "projection");
		glUniformMatrix4fv(viewlocation, 1, GL_FALSE, glm::value_ptr(view2));
		glUniformMatrix4fv(projectionlocation, 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(cubeVAO);
		glUniformMatrix4fv(modellocation, 1, GL_FALSE, glm::value_ptr(model2));
		glBindVertexArray(cubeVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		

		//cube2
		glm::mat4 view3 = camera.GetViewMatrix();
		glm::mat4 model3;
		shaders2.Use();
		GLint modellocation1 = glGetUniformLocation(shaders2.Program, "model");
		GLint viewlocation1 = glGetUniformLocation(shaders2.Program, "view");
		GLint projectionlocation1 = glGetUniformLocation(shaders2.Program, "projection");
		glUniformMatrix4fv(viewlocation1, 1, GL_FALSE, glm::value_ptr(view3));
		glUniformMatrix4fv(projectionlocation1, 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(cubeVAO2);
		glUniformMatrix4fv(modellocation1, 1, GL_FALSE, glm::value_ptr(model3));
		glBindVertexArray(cubeVAO2);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//**cube3
		//MIDDLE OBJECT
		//linking the shader / calling the shader
		shadercube.Use();

		//for color flunctation
		glm::vec3 lightcolorfl;
		lightcolorfl.r = sin(glfwGetTime() * 0.6f);
		lightcolorfl.g = sin(glfwGetTime() * 0.2f);
		lightcolorfl.b = sin(glfwGetTime() * 3.0f);

		glm::vec3 diffusecolor = lightcolorfl * glm::vec3(0.5);
		glm::vec3 ambientcolor = diffusecolor * glm::vec3(0.2);

		//for the light properties
		glUniform3f(glGetUniformLocation((shadercube.Program), "lgt.ambient"), ambientcolor.r, ambientcolor.g, ambientcolor.b);
		glUniform3f(glGetUniformLocation((shadercube.Program), "lgt.diffuse"), diffusecolor.r, diffusecolor.g, diffusecolor.b);
		glUniform3f(glGetUniformLocation((shadercube.Program), "lgt.specular"), 0.5f, 0.5f, 0.5f);

		//for the material properties
		glUniform3f(glGetUniformLocation((shadercube.Program), "mat.ambient"), 1.0, 0.0, 0.3);
		glUniform3f(glGetUniformLocation((shadercube.Program), "mat.diffuse"), 1.0, 0.0, 0.3);
		glUniform3f(glGetUniformLocation((shadercube.Program), "mat.specular"), 1.0, 1.0, 1.0);

		//for the shininess properties
		glUniform1f(glGetUniformLocation((shadercube.Program), "mat.shininess"), 16.0f);

		

		//translation
		glm::mat4 view9 = glm::mat4(1.0f);
		view9 = glm::rotate(view9, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, -1.0f));


		//step 3 get the uniform data from the vs shader file
		//translation data fetch from shaders
		unsigned int rotateacces3 = glGetUniformLocation(shadercube.Program, "view3");
		glUniformMatrix4fv(rotateacces3, 1, GL_FALSE, glm::value_ptr(view9));

		//translation
		glm::mat4 model9 = glm::mat4(1.0f);
		model9 = glm::translate(model9, glm::vec3(0.0 + transx3, -0.2 + transy3, 0.0));
		unsigned int translationacces3 = glGetUniformLocation(shadercube.Program, "model3");
		glUniformMatrix4fv(translationacces3, 1, GL_FALSE, glm::value_ptr(model9));
		//6 must pass parameter vao to see visibility of drawing 
		glBindVertexArray(VAO[3]);
		glDrawArrays(GL_TRIANGLES, 0, 36);		//drawing

		//another light cube****
		//translation
		glm::mat4 model10 = glm::mat4(1.0f);
		model10 = glm::translate(model10, glm::vec3(0.0 + transx3, 0.5 + transy3, 0.0));
		unsigned int translationacces4 = glGetUniformLocation(shadercube.Program, "model3");
		glUniformMatrix4fv(translationacces4, 1, GL_FALSE, glm::value_ptr(model10));
		//6 must pass parameter vao to see visibility of drawing 
		glBindVertexArray(VAO[3]);
		glDrawArrays(GL_TRIANGLES, 0, 36);		//drawing
		

		//skybox
		glDepthFunc(GL_LEQUAL);//*****must remember after multiple objcets has drawn make sure depth fun should be lequal of our skybox that means we wantely set opengl make our skybox greater than all or all other drawing must be less than or equal
		glm::mat4 view1 = camera.GetViewMatrix();
		shaders.Use();
		view1 = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(shaders.Program, "view"), 1, GL_FALSE, glm::value_ptr(view1));
		glUniformMatrix4fv(glGetUniformLocation(shaders.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);
		
		//model1
		shader.Use();
		glBindVertexArray(0);
		// make sure use new view as view1 ***********************
		glm::mat4 view4 = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view4));
		// make sure use new model as model1 ***********************
		//6.4 Draw the loaded model and done
		glm::mat4 model4;
		//lambo value trans and scale
		model4 = glm::translate(model4, glm::vec3(-2.0f, -2.0f, -50.0f)); // Translate it down a bit so it's at the center of the scene
		model4 = glm::scale(model4, glm::vec3(0.02f, 0.02f, 0.02f));	// It's a bit too big for our scene, so scale it down
		glBindVertexArray(0);
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model4));
		ourModel.Draw(shader);
		glBindVertexArray(0);

		//model2
		shader1.Use();
		glBindVertexArray(0);
		// make sure use new view as view1 ***********************
		glm::mat4 view5 = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader1.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader1.Program, "view"), 1, GL_FALSE, glm::value_ptr(view5));
		// make sure use new model as model1 ***********************
		//6.4 Draw the loaded model and done
		glm::mat4 model5;
		//lambo value trans and scale
		model5 = glm::translate(model5, glm::vec3(-6.0f, -3.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model5 = glm::scale(model5, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
		glBindVertexArray(0);
		glUniformMatrix4fv(glGetUniformLocation(shader1.Program, "model"), 1, GL_FALSE, glm::value_ptr(model5));
		ourModel1.Draw(shader1);
		glBindVertexArray(0);

		//model5*****
		glm::mat4 model8;
		//lambo value trans and scale
		model8 = glm::translate(model8, glm::vec3(-8.0f, -3.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model8 = glm::scale(model8, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
		glBindVertexArray(0);
		glUniformMatrix4fv(glGetUniformLocation(shader1.Program, "model"), 1, GL_FALSE, glm::value_ptr(model8));
		ourModel1.Draw(shader1);
		glBindVertexArray(0);

		//model3
		shader2.Use();
		glBindVertexArray(0);
		// make sure use new view as view1 ***********************
		glm::mat4 view6 = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader2.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader2.Program, "view"), 1, GL_FALSE, glm::value_ptr(view6));
		// make sure use new model as model1 ***********************
		//6.4 Draw the loaded model and done
		glm::mat4 model6;
		//lambo value trans and scale
		model6 = glm::translate(model6, glm::vec3(6.0f, -3.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model6 = glm::scale(model6, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
		glBindVertexArray(0);
		glUniformMatrix4fv(glGetUniformLocation(shader2.Program, "model"), 1, GL_FALSE, glm::value_ptr(model6));
		ourModel1.Draw(shader2);
		glBindVertexArray(0);

		//model4*******
		glm::mat4 model7;
		//lambo value trans and scale
		model7 = glm::translate(model7, glm::vec3(8.0f, -3.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model7 = glm::scale(model7, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
		glBindVertexArray(0);
		glUniformMatrix4fv(glGetUniformLocation(shader2.Program, "model"), 1, GL_FALSE, glm::value_ptr(model7));
		ourModel1.Draw(shader2);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		cout << "w key pressed\n";
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		cout << "s key pressed\n";
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		cout << "a key pressed\n";
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		cout << "d key pressed\n";
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
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


