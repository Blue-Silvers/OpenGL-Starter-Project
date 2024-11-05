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

			 0.1f,  0.0f, 0.0f,  0.1f, 0.6f, 0.3f,
			 0.1f,  0.1f, 0.0f,  0.1f, 0.6f, 0.3f,
			 0.0f,  0.1f, 0.0f,  0.1f, 0.6f, 0.3f,
			 -0.1f,  0.0f, 0.0f,  0.1f, 0.6f, 0.3f,
			 -0.1f,  -0.1f, 0.0f,  0.1f, 0.6f, 0.3f,
			 0.0f,  -0.1f, 0.0f,  0.1f, 0.6f, 0.3f,
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


	string vertexFragmentRGB = LoadShader("BlinkFragment.shader");
	const char* fragmentRgbShaderSource = vertexFragmentRGB.c_str();

	unsigned int fragmentRgbShaderId;
	fragmentRgbShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentRgbShaderId, 1, &fragmentRgbShaderSource, NULL);
	glCompileShader(fragmentRgbShaderId);

	unsigned int shaderProgramRGB;
	shaderProgramRGB = glCreateProgram();
	glAttachShader(shaderProgramRGB, vertexShaderId); //Attach vertex
	glAttachShader(shaderProgramRGB, fragmentRgbShaderId); //Attach fragment
	glLinkProgram(shaderProgramRGB); //Link shader to program


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
	//float moovingX = 0;
	//float moovingY = 0;
	float moovingX[100] = { 0, 0, 0, 0, 0, 0, 0 };
	float moovingY[100] = { 0, 0, 0, 0, 0, 0, 0 };
	int length = 50;
	float speed = 0.2f;

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
				if (event.key.keysym.sym == SDLK_UP && upDown == 0)
				{
					upDown = 0.1;
					rightLeft = 0;
				}
				else if (event.key.keysym.sym == SDLK_DOWN && upDown == 0)
				{
					upDown = -0.1;
					rightLeft = 0;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT && rightLeft == 0)
				{
					upDown = 0;
					rightLeft = 0.1;
				}
				else if (event.key.keysym.sym == SDLK_LEFT && rightLeft == 0)
				{
					upDown = 0;
					rightLeft = -0.1;
				}
				else if (event.key.keysym.sym == SDLK_SPACE)
				{
					if (length + 5 <= 100) 
					{
						length += 5;
					}
					speed += 0.03;
				}
				break;

			default:
				break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		//drawing zone

		//Classic draw
		float timeValue = (float)SDL_GetTicks() / 1000;
		//float mooving = (sin(timeValue * speed));
		float Scaling = 0.2;

		int vertexTriangleLocation = glGetUniformLocation(shaderProgram, "ourMovement");
		int vertexTriangleScale = glGetUniformLocation(shaderProgram, "ourScale");
		glUseProgram(shaderProgram);


		//border
		if (moovingX[0] <= -1.5 || moovingX[0] >= 1.5)
		{
			rightLeft = 0;
		}
		if (moovingY[0] <= -1.5 || moovingY[0] >= 1.5)
		{
			upDown = 0;
		}


		//apple
		glUniform2f(vertexTriangleLocation, 0, 0);
		glUniform1f(vertexTriangleScale, Scaling);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 9);
		glDrawArrays(GL_TRIANGLE_FAN, 9, 6);
		glDrawArrays(GL_TRIANGLE_FAN, 15, 4);


		float redColor = (sin(timeValue * speed) / 2.0f) + 0.5f;
		float greenColor = (sin(timeValue * speed + 2) / 2.0f) + 0.5f;
		float blueColor = (sin(timeValue * speed + 4) / 2.0f) + 0.5f;


		//movement
		moovingX[0] += rightLeft * speed;
		moovingY[0] += upDown * speed;

		//check body collision

		//RGB draw
		vertexTriangleLocation = glGetUniformLocation(shaderProgramRGB, "ourMovement");
		vertexTriangleScale = glGetUniformLocation(shaderProgramRGB, "ourScale");
		int vertexColorLocation = glGetUniformLocation(shaderProgramRGB, "ourShift");
		glUseProgram(shaderProgramRGB);
		glUniform4f(vertexColorLocation, redColor, greenColor, blueColor, 1.0f);
		Scaling = 0.6;

		//Snake head
		glUniform2f(vertexTriangleLocation, moovingX[0], moovingY[0]);
		glUniform1f(vertexTriangleScale, Scaling);

		glDrawArrays(GL_TRIANGLE_FAN, 19, 6);

		//Snake body
		for (int i = length - 1; i > 0; i--)
		{
			moovingX[i] = moovingX[i - 1];
			moovingY[i] = moovingY[i - 1];
			glUniform2f(vertexTriangleLocation, moovingX[i], moovingY[i]);
			glUniform1f(vertexTriangleScale, Scaling);

			glDrawArrays(GL_TRIANGLE_FAN, 19, 6);
		}


		// When eat apple
		/*
		length += 5;
		speed += 0.02;
		*/

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