#include "SoftwareRendering.h"
#include "config.h"
#include "stb_image.h"
#define BresenhamFill
//#define Barycentric




SoftwareRendering::SoftwareRendering(Matrix4D viewProj, TextureResource* t)
{
	mesh = new MeshResource();
	mesh = mesh->SetupQuad(0.4f);
	cameraPos = Vector4D(0, 0, -2.0f);
	height = 500;
	width = 500;
	int bitsPerPixel;
	int textureHeight;
	int textureWidth;
	viewProjection = viewProj;
	tr = t;
	tr->imageBuffer = std::vector<unsigned char>(height * width * 3);
	unsigned char* temp = stbi_load("d:\\images.jpg", &textureWidth, &textureHeight, &bitsPerPixel, 3); // 3 means force rgb, ignore alpha
	
	diffDiv = 1.0f / 255.0f;

	for (int i = 0; i < (textureWidth * textureHeight * 3); i++)
	{
		tr->texture.push_back(temp[i]);
	}
	tr->width = textureWidth;
	tr->height = textureHeight;

	PixelColor = [this](Vector4D pos, Vector4D uv, Vector4D norm, Matrix4D rotation)->Color
	{
#ifdef BresenhamFill
		uv.Get(0) >= 1 ? uv.SetX(0.999f) : uv[0];
		uv.Get(1) >= 1 ? uv.SetY(0.9999f) : uv[1];
		uv.Get(0) <= 0 ? uv.SetX(0.0f) : uv[0];
		uv.Get(1) <= 0 ? uv.SetY(0.0f) : uv[1];

#endif // BresenhamFill
		norm = (rotation * norm);
		norm.Normalize();
		//Sample texture for diffuse color
		int n = ((int)(uv[1] * tr->height) *tr->width + (int)(uv[0] * tr->width)) * 3;
		//if (n+2 > tr->texture.size())
		//{
		//	Color c;
		//	return c;
		//}
		Vector4D diffuseColor = Vector4D((int)tr->texture[n], (int)tr->texture[n + 1], (int)tr->texture[n + 2]) * diffDiv;
		lightPos.Normalize();
		pos.Normalize();
		Vector4D lightDir = lightPos - pos;
		float lambertian = std::max((lightDir*norm), 0.0f);
		float specular = 0.0;
		if (lambertian > 0.0)
		{
			Vector4D viewDir = cameraPos - pos;
			viewDir.Normalize();
			Vector4D halfDir = lightDir + viewDir;
			halfDir.Normalize();
			float specAngle = std::max(halfDir * norm, 0.0f);
			specular = std::pow(specAngle, lightIntensity);
		}
		//AMBIENT					//DIFFUSE						//SPECULAR
		Vector4D colorLinear = (lightAmb + diffuseColor * lambertian + lightSpec * specular);

		Color color;	
		float gammaCorrection = 2.2f;
		color.r = std::min((int)(std::pow(colorLinear[0], gammaCorrection) * 255), 255);
		color.g = std::min((int)(std::pow(colorLinear[1], gammaCorrection) * 255), 255);
		color.b = std::min((int)(std::pow(colorLinear[2], gammaCorrection) * 255), 255);

		return  color;
	};
}

SoftwareRendering::~SoftwareRendering()
{
	
}

void SoftwareRendering::RasterTriangle(Vertex A, Vertex B, Vertex C)
{
#ifdef Barycentric
	int maxX = std::max(A.pos[0], std::max(B.pos[0], C.pos[0]));
	int maxY = std::max(A.pos[1], std::max(B.pos[1], C.pos[1]));

	int minX = std::min(A.pos[0], std::min(B.pos[0], C.pos[0]));
	int minY = std::min(A.pos[1], std::min(B.pos[1], C.pos[1]));

	Vector4D AB = B.pos - A.pos;
	Vector4D BC = C.pos - B.pos;
	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			Vector4D delta = Vector4D((float)x - A.pos[0], (float)y - A.pos[1],0);
			float s = (delta[0] * BC[1] - delta[1] * BC[0]) / (AB[0] * BC[1] - AB[1] * BC[0]);
			float t = (AB[0] * delta[1] - AB[1] * delta[0]) / (AB[0] * BC[1] - AB[1] * BC[0]);

			//Is the pixel inside the triangle
			if ((s >= 0) && (t >= 0) && (s + t <= 1))
			{
				Interpolate(A, B, C, x, y);
			}
		}
	}
#endif
#ifdef BresenhamFill 
	if (A.pos[0] > B.pos[0])
		std::swap(A, B);
	if (A.pos[0] > C.pos[0])
		std::swap(A, C);
	if (B.pos[0] > C.pos[0])
		std::swap(B, C);

	std::vector<std::pair<int, int>> AB = Bresenham(A, B);
	std::vector<std::pair<int, int>> BC = Bresenham(B, C);
	std::vector<std::pair<int, int>> CA = Bresenham(C, A);


	if (AB.size() > 0 && BC.size() > 0 && CA.size() > 0)  //Is the triangle big enough to be visible?
	{
		int ay = AB[0].second;
		int by = BC[0].second;
		int cy = CA[0].second;
		if (ay > cy)
		{
			if (by > ay)		//CASE 1
			{
				//Bottom
				Fill(A, B, C, CA, BC, BC[BC.size() - 1].second, CA[CA.size() - 1].second, BC[BC.size() - 1].first);
				//Top
				Fill(A, B, C, AB, BC, AB[0].second, BC[0].second, BC[0].first);
			}
			else if (by < cy)	//CASE 3
			{
				//Bottom
				Fill(A, B, C, AB, BC, AB[AB.size() - 1].second, BC[BC.size() - 1].second, AB[AB.size() - 1].first);
				//Top
				Fill(A, B, C, AB, CA, CA[0].second, AB[0].second, AB[0].first);

			}
			else				//CASE 2, has mirror
			{
				//Bottom
				Fill(A, B, C, CA, BC, CA[0].second, BC[0].second, CA[0].first);
				//Top
				Fill(A, B, C, CA, AB, AB[AB.size() - 1].second, CA[CA.size() - 1].second, CA[CA.size() - 1].first);
			}
}
		else
		{
			if (by >= cy)		//CASE 4
			{
				//Bottom
				Fill(A, B, C, AB, CA, AB[0].second, CA[0].second, AB[0].first);
				//Top
				Fill(A, B, C, AB, BC, BC[BC.size() - 1].second, AB[AB.size() - 1].second, AB[AB.size() - 1].first);
			}
			else if (by <= ay)	//CASE 6
			{
				//Bottom
				Fill(A, B, C, AB, BC, BC[0].second, AB[0].second, BC[0].first);
				//Top
				Fill(A, B, C, CA, BC, CA[CA.size() - 1].second, BC[BC.size() - 1].second, BC[BC.size() - 1].first);
			}
			else				//CASE 5, has mirror
			{
				//Bottom
				Fill(A, B, C, AB, CA, CA[CA.size() - 1].second, AB[AB.size() - 1].second, CA[CA.size() - 1].first);
				//Top
				Fill(A, B, C, BC, CA, BC[0].second, CA[0].second, CA[0].first);
			}
		}
	}


#endif
}

void SoftwareRendering::Fill(Vertex a, Vertex b, Vertex c, std::vector<std::pair<int, int>> leftEdge, std::vector<std::pair<int, int>> rightEdge, int minY, int maxY, int defaultX)
{
	int leftX = defaultX;
	int rightX = defaultX;
	int le = leftEdge[0].second;
	int le2 = leftEdge[0].second;
	for (int y = minY; y <= maxY; y++)
	{
		//Find first on the left edge to have the y-value
		for (unsigned int i = 0; i < leftEdge.size(); i++)
		{
			if (leftEdge[i].second == y)
			{
				leftX = leftEdge[i].first;
				break;
			}
		}
		//Find first on the right edge to have the y-value
		for (unsigned int i = 0; i < rightEdge.size(); i++)
		{
			if (rightEdge[i].second == y)
			{
				rightX = rightEdge[i].first;
				break;
			}
		}
		for (int x = leftX; x <= rightX; x++)
		{
			Interpolate(a, b, c, x, y);

		}

		// Fill pixels in special mirror situation, can happen in case 2 and 5
		for (int x = rightX; x <= leftX; x++)
		{
			Interpolate(a, b, c, x, y);

		}
	}

}

std::vector<std::pair<int, int>> SoftwareRendering::Bresenham(Vertex A, Vertex B)
{
	std::vector<std::pair<int, int>> edge;

	int x = (int)A.pos[0];
	int y = (int)A.pos[1];
	int x4 = (int)B.pos[0];
	int y4 = (int)B.pos[1];


	int w = (int)B.pos[0] - (int)A.pos[0];
	int h = (int)B.pos[1] - (int)A.pos[1];

	int x1 = (int)A.pos[0];
	int y1 = (int)A.pos[1];
	int x2 = (int)B.pos[0];
	int y2 = (int)B.pos[1];

	int dx1 = 0;
	int dx2 = 0;
	int dy1 = 0;
	int dy2 = 0;

	if(w < 0)
	{
		dx1 = -1;
		dx2 = -1;
	}
	else if(w > 0)
	{
		dx1 = 1;
		dx2 = 1;
	}
	if(h < 0)
	{
		dy1 = -1;
	}
	else if(h > 0)
	{
		dy1 = 1;
	}

	int longest = abs(w);
	int shortest = abs(h);

	if(!(longest > shortest))
	{
		int temp = longest;
		longest = shortest;
		shortest = temp;

		if(h < 0)
		{
			dy2 = -1;
		}
		else
		{
			dy2 = 1;
		}
		dx2 = 0;
	}
	int numerator = longest >> 1;
	for(int i = 0; i<= longest; i++)
	{
		edge.push_back(std::pair<int, int>(x1, y1));
		numerator += shortest;
		if(!(numerator<longest))
		{
			numerator -= longest;
			x1 += dx1;
			y1 += dy1;
		}
		else
		{
			x1 += dx2;
			y2 += dy2;
		}
	}
	return edge;
}

void SoftwareRendering::Interpolate(Vertex A, Vertex B, Vertex C, int x, int y)
{
	if (x > 0 && y > 0 && x < width && y < height)
	{
		float triangleArea = TriangleArea(A, B, C); //<< Get the total area of the whole triangle

		if (triangleArea == 0)
		{
			return;
		}

		float multiplyArea = 1.0f / triangleArea;
		float ABP = AreaProcent(A, B, x, y) * multiplyArea;
		float ACP = AreaProcent(A, C, x, y) * multiplyArea;
		float BCP = AreaProcent(B, C, x, y) * multiplyArea;

		Vertex vertex((GLfloat)x,(GLfloat)y,(A.pos[2] * BCP) + (B.pos[2] * ACP) + (C.pos[2] * ABP));

		//Interpolating the UV
		vertex.uv[0] = A.uv[0] * BCP + B.uv[0] * ACP + C.uv[0] * ABP;
		vertex.uv[1] = A.uv[1] * BCP + B.uv[1] * ACP + C.uv[1] * ABP;

		//Interpolating the normals
		vertex.normal[0] = A.normal[0] * BCP + B.normal[0] * ACP + C.normal[0] * ABP;
		vertex.normal[1] = A.normal[1] * BCP + B.normal[1] * ACP + C.normal[1] * ABP;
		vertex.normal[2] = A.normal[2] * BCP + B.normal[2] * ACP + C.normal[2] * ABP;

		Color color = PixelColor(vertex.pos, vertex.uv, vertex.normal, modelMatrix);

		int index = (y * width * 3) + (x * 3);
		tr->imageBuffer[index] = color.r;
		tr->imageBuffer[index + 1] = color.g;
		tr->imageBuffer[index + 2] = color.b;
	}
}

float SoftwareRendering::TriangleArea(Vertex A, Vertex B, Vertex C)
{
	return abs((A.pos[0]*(B.pos[1] - C.pos[1])+B.pos[0]*(C.pos[1]-A.pos[1])+C.pos[0]*(A.pos[1] - B.pos[1]))*0.5);
}

float SoftwareRendering::AreaProcent(Vertex A, Vertex B, int x, int y)
{
	return std::abs((A.pos[0] * (B.pos[1] - y) + (B.pos[0] * (y - A.pos[1])) + (x * (A.pos[1] - B.pos[1])))*0.5f);
}

void SoftwareRendering::Draw()
{
	//Resetting the imageBuffer for next frame
	for (int i = 0; i < tr->imageBuffer.size(); i++)
	{
		tr->imageBuffer[i] = 128;
	}

	std::vector<Vertex> modified = std::vector<Vertex>(mesh->numVertices);
	Vertex temp;
	for (int i = 0; i < mesh->numVertices; i++)
	{
		temp = mesh->verticeBuffer[i];
		temp.pos = viewProjection * modelMatrix * mesh->verticeBuffer[i].pos;
		temp.pos[0] = temp.pos[0] * width;
		temp.pos[1] = temp.pos[1] * height;
		modified[i] = temp;
	}

	for (int i = 0; i < mesh->sizeOfBuffer; i+=3)
	{
 		RasterTriangle(modified[mesh->indiceBuffer[i]], modified[mesh->indiceBuffer[i+1]], modified[mesh->indiceBuffer[i+2]]);
	}
	tr->ApplyNewTexture();
}
