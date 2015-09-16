#pragma once

#include <SDL.h>

#include "GL.h"

#include "cameras/Camera.h"

#include "core/Window.h"

#include "materials/Material.h"

#include "objects/Mesh.h"

#include "renderers/opengl/GLUniform.h"

#include "scenes/Scene.h"

class GLRenderer
{
public:
	GLRenderer( SDL_Window *window, Scene &scene, Camera &camera );
	~GLRenderer();

	void setSize( int width, int height );
	void onWindowResized( int width, int height );
	void onCameraUpdated();

	void render();

	void setProgram( Program *program );
	void setVAO( GLuint vao );

	void updateModelMatrix( Mesh *mesh );
	void updateViewMatrix();
	void updateModelViewMatrix();
	void updateProjectionMatrix( bool cascade = true );
	void updateModelViewProjectionMatrix();
	void updateCameraPosition();

	void loadUniforms( Material *material );

	SDL_Window* window;
	SDL_GLContext context;

	Scene *scene;
	Camera *camera;

	Program *currentProgram;
	GLuint currentVAO;

	glm::mat4 currentModelMatrix;
	glm::mat4 currentViewMatrix;
	glm::mat4 currentModelViewMatrix;
	glm::mat4 currentModelViewProjectionMatrix;
	glm::mat4 currentProjectionMatrix;
};