//
// COMP 371 Project Team 4
//
// Base code initially by Nicolas Bergeron and Gary Chang
// Updated By Rita Phommarath
// 
//

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

#include "Terrain.h"
#include "../Renderer.h"
#include "../TextureLoader.h"

using namespace glm;


Terrain::Terrain(vec3 size) : Model()
{
	//Load the texture 
	Texture = loadBMP("../Source/Textures/bricks0.bmp");

	//Allows collision detection
	CreateDefaultCollisionCube();

	// Create Vertex Buffer for all the vertices of the Cube
	vec3 halfSize = size * 0.5f;

	Vertex vertexBuffer[] = {  // position,                normal,                  color-white
		{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0) }, //left 
		{ vec3(-halfSize.x, -halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0) },

		{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0) },

		{ vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(1.0, 1.0, 1.0) }, // far
		{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(1.0, 1.0, 1.0) },

		{ vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(1.0, 1.0, 1.0) },

		{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(1.0, 1.0, 1.0) }, // bottom 
		{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(1.0, 1.0, 1.0) },

		{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(-halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(1.0, 1.0, 1.0) },

		{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(1.0, 1.0, 1.0) }, // near 
		{ vec3(-halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(1.0, 1.0, 1.0) },

		{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(1.0, 1.0, 1.0) },

		{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0) }, // right 
		{ vec3(halfSize.x, -halfSize.y, -halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0) },

		{ vec3(halfSize.x, -halfSize.y, -halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0) },

		{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0, 1.0, 1.0) }, // top 
		{ vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0, 1.0, 1.0) },

		{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0, 1.0, 1.0) },
		{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0, 1.0, 1.0) }
	};

	static const GLfloat g_uv_buffer_data[] =
	{
		0.0f, 0.0f, //left
		0.0f, 1.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 1.0f, //far
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,

		1.0f, 1.0f, // bottom
		0.0f, 0.0f,
		0.0f, 1.0f,

		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 0.0f, //near
		1.0f, 0.0f,
		1.0f, 1.0f,

		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,

		0.0f, 0.0f, //right
		1.0f, 1.0f,
		0.0f, 1.0f,

		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f, //top
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f


	};


	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);


	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	glDisable(GL_TEXTURE_2D);

}

Terrain::~Terrain()
{
	// Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void Terrain::Update(float dt)
{
	Model::Update(dt);
}

void Terrain::Draw()
{
	// Draw the Vertex Buffer
	glBindVertexArray(mVertexArrayID);

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(Renderer::GetShaderProgramID(), "mySamplerTexture");

	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);


	//enable texture
	glEnable(GL_TEXTURE_2D);

	// Bind our texture in Texture Unit 2?
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 2);

	// Set our "myTextureSampler" sampler to user Texture Unit 2
	glUniform1i(TextureID, 2);


	// 1st attribute buffer : vertex Positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(0,				// attribute. No particular reason for 0, but must match the layout in the shader.
		3,				// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		sizeof(Vertex), // stride
		(void*)0        // array buffer offset
		);

	// 2nd attribute buffer : vertex normal
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
		);


	// 3rd attribute buffer : vertex color
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(2,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(2 * sizeof(vec3)) // Color is Offseted by 2 vec3 (see class Vertex)
		);

	// 4th attribute buffer : UVs
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		3,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);


	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)

	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

bool Terrain::ParseLine(const std::vector<ci_string> &token){
	if (token.empty()){
		return true;
	}
	else {
		return Model::ParseLine(token);
	}
}

