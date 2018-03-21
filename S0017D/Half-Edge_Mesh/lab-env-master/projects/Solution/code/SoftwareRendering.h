#include "MeshResource.h"
#include <functional>


struct Color
{
	int r;
	int g;
	int b;
};


class SoftwareRendering
{
	public:
		SoftwareRendering();

        SoftwareRendering(int* iBuffer, Vertex* vBuffer);

		~SoftwareRendering();

		void SetBuffers(int* iBuffer, Vertex* vBuffer);

		void RasterTriangle(Vertex a, Vertex b, Vertex c);

		std::vector<int> Bresenham(Vertex A, Vertex B);

		int GetOctant(Vertex A, Vertex B);

		void SwitchToOctantZero(int octant,Vertex &B);

		void SwitchToOctant(int octant,Vertex &B);

		void Interpolate(Vertex A, Vertex B, Vertex C);

		float TriangleArea(Vertex A, Vertex B, Vertex C);

		void Draw();

	protected:

	private:
		Vertex* vertexBuffer;
		int* indBuffer;
		unsigned char* textureBuffer;
		unsigned char* imageBuffer;

		GLuint vAO, vBO, eBO;
		Matrix4D modelMatrix, viewMatrix, projectionMatrix;

//		/* Lambda function*/
//		std::function<Color(Vector4D uv, Vector4D norm, unsigned char* texture)> pixelColor =
//		([](Vector4D uv, Vector4D norm, unsigned char* texture)
//		{
//			Color test;
//			return test;
//		});
		
};