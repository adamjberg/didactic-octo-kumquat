#include "SDL_image.h"
#include "textures/Texture.h"

#include "cameras/Camera.h"

#include "components/FPSCamera.h"

#include "core/SDLEventController.h"
#include "core/Geometry.h"
#include "core/Window.h"

#include "input/Input.h"

#include "objects/Mesh.h"

#include "materials/Material.h"

#include "renderers/opengl/Program.h"
#include "renderers/opengl/GLRenderer.h"

#include "scenes/Scene.h"

void onQuit( bool *running )
{
	*running = false;
}

int main( int argc, char* args[] )
{
	SDL_Init( SDL_INIT_EVERYTHING );
	IMG_Init( IMG_INIT_JPG );

	bool running = true;

	Window window( "Tutorial", 200, 200 );

	Scene scene;

	Camera camera;
	camera.position.z = 5;

	GLRenderer glRenderer( window.sdlWindow, scene, camera );

	Program *program = new Program( "texture.vs", "texture.fs" );
	Texture suzanneTexture( "suzanne.jpg" );
	Texture boxTexture( "door.jpg" );

	Material suzanneMaterial( program, &suzanneTexture );
	Material boxMaterial( program, &boxTexture );

	Geometry suzanneGeo( "suzanne.obj" );
	Geometry boxGeo( "box.obj" );

	Mesh suzanneMesh( suzanneGeo, suzanneMaterial );
	suzanneMesh.position.x = -1.5;

	Mesh boxMesh( boxGeo, boxMaterial );
	boxMesh.position.x = 0.5;
	boxMesh.position.y = -0.5;

	scene.add( suzanneMesh );
	scene.add( boxMesh );

	SDLEventController sdlEventController;
	Input input( sdlEventController );

	sdlEventController.onQuit.add( std::bind( onQuit, &running ) );

	sdlEventController.onWindowResized.add( [ &glRenderer ]( int width, int height ) {
		glRenderer.onWindowResized( width, height );
	} );

	FPSCamera fpsCamera( input );
	camera.add( fpsCamera );

	while( running )
	{
		sdlEventController.update();

		camera.update();
		scene.update();
		
		glRenderer.render();
	}

	SDL_Quit();

	return 0;
}