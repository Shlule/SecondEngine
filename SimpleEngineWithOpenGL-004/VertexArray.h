#pragma once

constexpr float vertices[] = {
	-0.5f, 0.5f, 0.f, //0.f, 0.f //top left
	0.5f, 0.5f, 0.f, //1.0f, 0.f // topRight
	0.5f, -0.5f, 0.f, //1.f ,1.f //bottomRight
	-0.5f, -0.5f, 0.f, //0.f, 1.f //bottomLeft
};

constexpr unsigned int indices[] = {
	0,1,2,
	2,3,0
};
class VertexArray
{
public:
	VertexArray(const float* verticesP, unsigned int ndVerticesP, const unsigned int* indicesP, unsigned int nbIndicesP);
	~VertexArray();

	void setActive();

	unsigned int getNbVertices()const { return nbVertices; }
	unsigned int getnbIndices()const { return nbIndices; }

private:
	unsigned int nbVertices;
	unsigned int nbIndices;

	//openGl ID of the vertex array object
	unsigned int vertexArray;
	//OpenGL ID of the vertexBuffer
	unsigned int vertexBuffer;
	//OpenGl ID of the index buffer
	unsigned int indexBuffer;
};

