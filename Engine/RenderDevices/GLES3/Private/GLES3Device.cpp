#include "..\Public\GLES3Device.h"
#include "..\..\..\Frame\Public\RenderTarget.h"
#include "..\..\..\Platforms\Windows\Public\EngineWindows.h"
#include "..\..\..\Platforms\Windows\Public\RenderWindowWindows.h"
#include "..\..\..\Platforms\Windows\Public\WindowsUtility.h"

#include <SDL.h>

#if RENDER_DEVICE_USE == RENDER_DEVICE_GLES3
#include <GLES3/gl3.h>
#pragma comment(lib, "libGLESv2.lib")
#endif


//#include <SDL2/SDL_opengl_glext.h>

GLES3Device::GLES3Device()
{

}

GLES3Device::~GLES3Device()
{

}

int GLES3Device::Init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetSwapInterval(0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	RenderWindow *Window = dynamic_cast<RenderWindow*>(EngineWindows::GetInstance()->GetRenderTarget());
	auto glc = SDL_GL_CreateContext(Window->GetWindow());

	auto rdr = SDL_CreateRenderer(
		Window->GetWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	//GLuint vao;
	////glGenVertexArraysOES(1, &vao);
	////glBindVertexArrayOES(vao);

	//GLuint vbo;
	//glGenBuffers(1, &vbo);

	//GLfloat vertices[] = { 0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f };

	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//const GLchar* vertexSource =
	//	"attribute vec4 position;    \n"
	//	"void main()                  \n"
	//	"{                            \n"
	//	"   gl_Position = vec4(position.xyz, 1.0);  \n"
	//	"}                            \n";
	//const GLchar* fragmentSource =
	//	"precision mediump float;\n"
	//	"void main()                                  \n"
	//	"{                                            \n"
	//	"  gl_FragColor = vec4 (1.0, 1.0, 1.0, 1.0 );\n"
	//	"}                                            \n";

	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//glCompileShader(vertexShader);

	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//glCompileShader(fragmentShader);

	//GLuint shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);

	//glLinkProgram(shaderProgram);
	//glUseProgram(shaderProgram);

	//GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	//glEnableVertexAttribArray(posAttrib);
	//glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	return 0;
}

int GLES3Device::UnInit()
{
	return 0;

}

int GLES3Device::Draw()
{
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	//glDrawArrays(GL_TRIANGLES, 0, 3);

	RenderWindow *Window = dynamic_cast<RenderWindow*>(EngineWindows::GetInstance()->GetRenderTarget());
	SDL_GL_SwapWindow(Window->GetWindow());

	return 0;
}

