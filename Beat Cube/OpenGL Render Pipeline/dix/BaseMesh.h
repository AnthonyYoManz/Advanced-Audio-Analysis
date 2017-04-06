#pragma once
#include <GL/glew.h>
namespace dix
{
	class BaseMesh
	{
	private:
		bool m_loaded;
	protected:
		//Handle to VAO
		GLuint m_vao;
		/*Handles to VBOs
		  0: verts
		  1: normals
		  2: texCoords
		  3: colours
		*/
		GLuint m_vbo[4];
		//Number of vertexes in the mesh
		unsigned int m_vertexCount;
		//Number of triangles in the mesh
		unsigned int m_triangleCount;

		virtual void v_load() = 0;
	public:
		virtual ~BaseMesh() = default;

		//Loads the mesh
		void load();
		//(Hopefully) frees the mesh from memory
		void unload();

		GLuint getVAO();
		GLuint getVertexVBO();
		GLuint getNormalVBO();
		GLuint getTextureCoordVBO();
		GLuint getColourVBO();
		unsigned int getVertexCount();
		unsigned int getTriangleCount();
	};
}