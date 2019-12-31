#include "..\Public\GL4Device.h"
#include "..\..\..\Frame\Public\RenderTarget.h"
#include "..\..\..\Platforms\Windows\Public\EngineWindows.h"
#include "..\..\..\Platforms\Windows\Public\RenderWindowWindows.h"
#include "..\..\..\Platforms\Windows\Public\WindowsUtility.h"
#include <SDL.h>

GL4Device::GL4Device()
{

}

GL4Device::~GL4Device()
{

}

int GL4Device::Init()
{
	const int OPENGL_MAJOR_VERSION = 2;
	const int OPENGL_MINOR_VERSION = 1;
	SDL_GLprofile OPENGL_PROFILE = SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_CORE;

	RenderWindow *Window = dynamic_cast<RenderWindow*>(EngineWindows::GetInstance()->GetRenderTarget());

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OPENGL_PROFILE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);

	SDL_GLContext context = SDL_GL_CreateContext(Window->GetWindow());
	SDL_GL_MakeCurrent(Window->GetWindow(), context);

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	gluPerspective(60.0, 1.0, 1.0, 100.0);

	GLfloat ratio;

	ratio = 1.0;

	glViewport(0, 0, 1024, 1024);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLdouble fovY = 45.0f;
	GLdouble aspect = 1.0f;
	GLdouble zNear = 0.1f;
	GLdouble zFar = 100.0f;
	GLdouble fW, fH;

	fH = tan(fovY / 360 * M_PI) * zNear;
	fW = fH * aspect;

	glFrustum(-fW, fW, -fH, fH, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	return 0;
}

int GL4Device::UnInit()
{
	return 0;

}

int GL4Device::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor4f(1, 1, 0, 1.0);

	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f); 
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd(); 

	glTranslatef(3.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS); 
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd(); 

	RenderWindow *Window = dynamic_cast<RenderWindow*>(EngineWindows::GetInstance()->GetRenderTarget());

	SDL_GL_SwapWindow(Window->GetWindow());

	return 0;
}
