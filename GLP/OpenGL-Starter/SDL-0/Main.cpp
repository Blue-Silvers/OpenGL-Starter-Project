#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>
#include <glew.h>
using namespace std;
//#define GLEW_STATIC

string LoadShader(string fileName);

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!\n";
	}
	///////////SETTING UP SDL/////////////
	//Create a simple window
	int width = 800;
	int height = 800;
	unsigned int center = SDL_WINDOWPOS_CENTERED;
	SDL_Window* Window = SDL_CreateWindow("Snake", center, center, width, height, SDL_WINDOW_OPENGL);
	//SDL_WINDOW_OPENGL is a u32 flag !


	//Create an OpenGL compatible context to let glew draw on it
	SDL_GLContext Context = SDL_GL_CreateContext(Window);

	/////////SETTING UP OPENGL WITH GLEW///
	//Initialize glew
	glewExperimental = GL_TRUE;
	if (glewInit() == GLEW_OK) {
		cout << "Glew initialized successfully\n";
	}

	//Set the viewing frame through which we will see the objects
	glViewport(0, 0, width, height);

	//Put the color you want here for the background
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

	/*float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, //A
		0.5f, -0.5f, 0.0f,  //B
		0.0f,  0.5f, 0.0f   //C
	};*/
	float vertices[] = {
		// positions             // colors
			 0.1f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
			 0.1f,  0.2f, 0.0f,  1.0f, 0.0f, 0.0f,
			 -0.1f,  0.2f, 0.0f,  1.0f, 0.0f, 0.0f,
			 -0.3f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
			 -0.3f,  -0.2f, 0.0f,  1.0f, 0.0f, 0.0f,
			 -0.1f,  -0.4f, 0.0f,  1.0f, 0.0f, 0.0f,
			 0.1f,  -0.4f, 0.0f,  1.0f, 0.0f, 0.0f,
			 0.3f,  -0.2f, 0.0f,  1.0f, 0.0f, 0.0f,
			 0.3f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

			 0.18f,  0.38f, 0.0f,  0.1f, 0.6f, 0.3f,
			 0.18f,  0.46f, 0.0f,  0.1f, 0.6f, 0.3f,
			 0.1f,  0.46f, 0.0f,  0.1f, 0.6f, 0.3f,
			 0.02f,  0.38f, 0.0f,  0.1f, 0.6f, 0.3f,
			 0.02f,  0.3f, 0.0f,  0.1f, 0.6f, 0.3f,
			 0.1f,  0.3f, 0.0f,  0.1f, 0.6f, 0.3f,

			 -0.02f,  0.4f, 0.0f,  0.4f, 0.3f, 0.3f,
			 0.02f,  0.4f, 0.0f,  0.4f, 0.3f, 0.3f,
			 0.02f,  0.2f, 0.0f,  0.4f, 0.3f, 0.3f,
			 -0.02f,  0.2f, 0.0f,  0.4f, 0.3f, 0.3f,
	};


	//VBO
	unsigned int vbo;
	glGenBuffers(1, &vbo);

	//SHADER
	string vertexShader = LoadShader("SimpleShader.shader");
	const char* vertexShaderSource = vertexShader.c_str();

	//string vertexFragment = LoadShader("BlinkFragment.shader");
	string vertexFragment = LoadShader("SimpleFragment.shader");
	const char* fragmentShaderSource = vertexFragment.c_str();

	unsigned int vertexShaderId;
	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShaderId);

	unsigned int fragmentShaderId;
	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderId);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderId); //Attach vertex
	glAttachShader(shaderProgram, fragmentShaderId); //Attach fragment
	glLinkProgram(shaderProgram); //Link shader to program
	glUseProgram(shaderProgram);  //Use shader to program

	//VAO
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	//MAIN SGAME LOOP
	bool isRunning = true;
	float rightLeft = 0;
	float upDown = -0.1;
	float moovingX = 0;
	float moovingY = 0;

	while (isRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) 
				{
					isRunning = false;
				}
				if (event.key.keysym.sym == SDLK_UP)
				{
					upDown = 0.1;
					rightLeft = 0;
				}
				else if (event.key.keysym.sym == SDLK_DOWN) 
				{
					upDown = -0.1;
					rightLeft = 0;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					upDown = 0;
					rightLeft = 0.1;
				}
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					upDown = 0;
					rightLeft = -0.1;
				}
				break;

			default:
				break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		//drawing zone

		/*float speed = 5;
		float timeValue = (float)SDL_GetTicks() / 1000;
		float redColor = (sin(timeValue *speed) / 2.0f) + 0.5f;
		float greenColor = (sin(timeValue* speed +2) / 2.0f) + 0.5f;
		float blueColor = (sin(timeValue* speed +4) / 2.0f) + 0.5f;

		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourShift");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, redColor, greenColor, blueColor, 1.0f);*/

		float speed = 0.2f;
		float timeValue = (float)SDL_GetTicks() / 1000;
		//float mooving = (sin(timeValue * speed));
		//float Scaling = (sin(timeValue * speed) / 2.0f)+0.5f;
		float Scaling = 0.4;
		moovingX += rightLeft * speed;
		moovingY += upDown * speed;


		int vertexTriangleLocation = glGetUniformLocation(shaderProgram, "ourMovement");
		int vertexTriangleScale = glGetUniformLocation(shaderProgram, "ourScale");
		glUseProgram(shaderProgram);
		glUniform2f(vertexTriangleLocation, moovingX, moovingY);
		glUniform1f(vertexTriangleScale, Scaling);



		glDrawArrays(GL_TRIANGLE_FAN, 0, 9);
		glDrawArrays(GL_TRIANGLE_FAN, 9, 6);
		glDrawArrays(GL_TRIANGLE_FAN, 15, 4);

		SDL_GL_SwapWindow(Window); // Swapbuffer
	}

	if (isRunning) 
	{
		cin.get();
	}
	
	return 0;


}

string LoadShader(string fileName) {
		ifstream myFile;
		myFile.open(fileName);
		if (myFile.fail()) {
			cerr << "Error - failed to open " << fileName << endl;
		}
		string fileText = "";
		string line = "";
		while (getline(myFile, line)) {
			fileText += line + '\n';
		}

		myFile.close();
		return fileText;
	}