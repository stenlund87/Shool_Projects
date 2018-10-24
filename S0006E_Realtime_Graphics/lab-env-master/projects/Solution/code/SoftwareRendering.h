#include "MeshResource.h"
#include <functional>
#include "TextureResource.h"
#include "LightNode.h"
#include "ShaderObject.h"

struct Color
{
	int r = 0;
	int g = 0;
	int b = 0;
};


class SoftwareRendering
{
	public:
		/**
		*Default constructor
		*/
		SoftwareRendering() {};

		SoftwareRendering(Matrix4D viewProj, TextureResource* t);

		/**
		*Destructor
		*/
		~SoftwareRendering();

		void SetMesh(MeshResource* m) { this->mesh = m; };
		void SetTexture(TextureResource* t) { this->tr = t; };
		void SetLight(LightNode l)
		{ 
			lightPos = l.GetPos();
			lightAmb = l.GetAmb();
			lightSpec = l.GetSpec();
			lightIntensity = l.GetIntensity();
		
		};
		void SetModelMatrix(Matrix4D model) { modelMatrix = model; };
		void RasterTriangle(Vertex a, Vertex b, Vertex c);
		void Fill(Vertex a, Vertex b, Vertex c, std::vector<std::pair<int, int>> leftEdge, std::vector<std::pair<int, int>> rightEdge, int minY, int maxY, int defaultX);
		std::vector<std::pair<int, int>> Bresenham(Vertex A, Vertex B);
		void Interpolate(Vertex A, Vertex B, Vertex C, int x, int y);
		float TriangleArea(Vertex A, Vertex B, Vertex C);
		float AreaProcent(Vertex A, Vertex B, int x, int y);
		void Draw();

	protected:

	private:
		//Object pointers
		MeshResource* mesh;
		TextureResource* tr;
	
		//Matrix for calculations
		Matrix4D modelMatrix;
		Matrix4D viewProjection;

		//Vectors for light and camera
		Vector4D cameraPos;
		Vector4D lightPos;
		Vector4D lightAmb;
		Vector4D lightSpec;

		//Some other relevant data to save
		int height, width;
		int textureHeight;
		int textureWidth;
		float diffDiv; //<< Used in the lambda function, no need to re-caluclate it every frame
		float lightIntensity;

		//Lambda function
		std::function<Color(Vector4D pos, Vector4D uv, Vector4D norm, Matrix4D rotation)> PixelColor;
		std::vector<float>zBuffer;
};