#include "renderers/opengl/GLRenderer.h"

#include "objects/Mesh.h"
#include "renderers/opengl/GLUniform.h"
#include "textures/Texture.h"

GLRenderer::GLRenderer( SDL_Window *window, Scene &scene, Camera &camera ) : scene( &scene ), camera( &camera )
{
	this->window = window;
	context = SDL_GL_CreateContext( window );

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	assert( glewIsSupported( "GL_VERSION_4_0" ) );
	assert( glewError == GLEW_OK );

	SDL_GL_SetSwapInterval( 1 );

	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );
	glEnable( GL_CULL_FACE );

	camera.onUpdate.add( std::bind( &GLRenderer::onCameraUpdated, this ) );

	currentProgram = nullptr;
}

GLRenderer::~GLRenderer()
{
	SDL_GL_DeleteContext( context );
}

void GLRenderer::onWindowResized( int width, int height )
{
	camera->aspect = ( float ) width / height;
	camera->updateProjectionMatrix();

	updateProjectionMatrix();
	updateViewMatrix();

	glViewport( 0, 0, width, height );
}

void GLRenderer::onCameraUpdated()
{
	if( currentProgram != nullptr )
	{
		updateProjectionMatrix();
		updateViewMatrix();
	}
}

void GLRenderer::render()
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	for( Object3D *object : scene->children )
	{
		Mesh *mesh = dynamic_cast< Mesh* >( object );

		setVAO( mesh->getVAO() );
		setProgram( mesh->material->program );

		updateModelMatrix( mesh );

		loadUniforms( mesh->material );

		glDrawElements( GL_TRIANGLES, mesh->geometry->size, GL_UNSIGNED_INT, NULL );
	}

	SDL_GL_SwapWindow( window );
}

void GLRenderer::setProgram( Program *program )
{
	if( currentProgram == nullptr || program->id != currentProgram->id )
	{
		currentProgram = program;
		glUseProgram( currentProgram->id );

		updateProjectionMatrix( false );
		updateViewMatrix();
	}
}

void GLRenderer::setVAO( GLuint vao )
{
	if( vao != currentVAO )
	{
		currentVAO = vao;
		glBindVertexArray( currentVAO );
	}
}

void GLRenderer::updateModelMatrix( Mesh *mesh )
{
	currentModelMatrix = mesh->matrix;
	currentProgram->getUniform( "modelMatrix" )->value = glm::value_ptr( currentModelMatrix );
	updateModelViewMatrix();

}

void GLRenderer::updateViewMatrix()
{
	currentViewMatrix = camera->matrix;
	currentProgram->getUniform( "viewMatrix" )->value = glm::value_ptr( currentViewMatrix );
	updateModelViewMatrix();
}

void GLRenderer::updateModelViewMatrix()
{
	currentModelViewMatrix = currentViewMatrix * currentModelMatrix;
	currentProgram->getUniform( "modelViewMatrix" )->value = glm::value_ptr( currentModelViewMatrix );
	updateModelViewProjectionMatrix();
}

void GLRenderer::updateModelViewProjectionMatrix()
{
	currentModelViewProjectionMatrix = currentProjectionMatrix * currentViewMatrix * currentModelMatrix;
	currentProgram->getUniform( "modelViewProjectionMatrix" )->value = glm::value_ptr( currentModelViewProjectionMatrix );
}

void GLRenderer::updateProjectionMatrix( bool cascade )
{
	currentProjectionMatrix = camera->projectionMatrix;
	currentProgram->getUniform( "projectionMatrix" )->value = glm::value_ptr( currentProjectionMatrix );

	if( cascade )
	{
		updateModelViewProjectionMatrix();
	}
}

void GLRenderer::loadUniforms( Material *material )
{
	for( std::pair<std::string, GLUniform *> kv : material->uniforms )
	{
		GLUniform *uniform = kv.second;
		void * value = uniform->value;
		GLint location = uniform->location;

		if( value == NULL || location == -1 )
		{
			continue;
		}

		switch( uniform->type )
		{
		case MATRIX4x4:
		{
			glUniformMatrix4fv( location, 1, GL_FALSE, static_cast< GLfloat * >( value ) );
			break;
		}
		case VECTOR3:
		{
			glUniform3fv( location, 1, static_cast< GLfloat * >( value ) );
			break;
		}
		case TEXTURE:
		{
			Texture *texture = static_cast< Texture * >( value );

			// TODO: allow more than one texture
			GLint textureUnit = 0;

			glUniform1i( location, textureUnit );

			glActiveTexture( GL_TEXTURE0 );
			glBindTexture( GL_TEXTURE_2D, texture->id );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, texture->surface->w, texture->surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->surface->pixels );

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->magFilter );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->minFilter );

			break;
		}
		default:
		{
			assert( false );
			break;
		}
		}
	}
}