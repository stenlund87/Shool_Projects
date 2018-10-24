//#ifndef  MESHRESOUCE_CPP
//#define MESHRESOURCE_CPP
//#include "MeshResouce.h"
//
//
//MeshResource::MeshResource()
//{
//
//}
//
//MeshResource::~MeshResource()
//{
//
//}
//
//void MeshResource::SetVBO()
//{
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeOfPositions, VB, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, floatsPerPosition, GL_FLOAT, GL_FALSE, 0, 0);
//}
//
//void MeshResource::SetEBO()
//{
//	glGenBuffers(1, &ebo);
//	 //Bind index buffer to corresponding target
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	 //ititialize index buffer, allocate memory, fill it with data
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, IB, GL_STATIC_DRAW);
//}
//
//
//void MeshResource::DrawQuad()
//{
//	Vertex topLeft(-0.5f, 0.5f, 0);
//	Vertex topRight(0.5f, 0.5f, 0);
//	Vertex bottomLeft(-0.5f, -0.5f, 0);
//	Vertex bottomRight(0.5f, -0.5f, 0);
//
//
//
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeOfIndices, NULL);
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeOfIndices, (GLvoid*)sizeOfPositions);
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//
//}
//
//void MeshResource::Draw()
//{
//	glBindVertexArray(vao);
//	glDrawArrays(GL_TRIANGLES, 0, numVertices);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);
//}
//#endif // ! MESHRESOUCE_CPP
