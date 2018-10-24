#include "SoftwareRendering.h"
#include "config.h"


SoftwareRendering::SoftwareRendering()
{

}

SoftwareRendering::SoftwareRendering(int* iBuffer, Vertex* vBuffer)
{
    this->indBuffer = iBuffer;
    this->vertexBuffer = vBuffer;
}

SoftwareRendering::~SoftwareRendering()
{
	
}



void SoftwareRendering::SetBuffers(int* iBuffer, Vertex* vBuffer)
{
	this->indBuffer = iBuffer;
	this->vertexBuffer = vBuffer;
}

void SoftwareRendering::RasterTriangle(Vertex left, Vertex top, Vertex right)
{
    std::vector<int> AB = Bresenham(left, top);
    std::vector<int> BC = Bresenham(top, right);
    std::vector<int> CA = Bresenham(right, left);

	if (left.pos[0] > top.pos[0] || left.pos[0] > right.pos[0])
	{

	}
	else if (left.pos[1] < top.pos[1] && left.pos[1] < right.pos[1])
	{

	}
	else if (left.pos[2] < top.pos[2] && left.pos[2] < right.pos[2])
	{

	}
}

std::vector<int> SoftwareRendering::Bresenham(Vertex A, Vertex B)
{
//	int width = (int)B[0] - (int)A[0];
//	int height = (int)B[1] - (int)A[1];
//	int dx1 = 0;
//	int dx2 = 0;
//	int dy1 = 0;
//	int dy2 = 0;
//
//	if(width < 0)
//	{
//		dx1 = -1;
//		dx2 = -1;
//	}
//	else if(width > 0)
//	{
//		dx1 = 1;
//		dx2 = 1;
//	}
//	if(height < 0)
//	{
//		dy1 = -1;
//	}
//	else if(height > 0)
//	{
//		dy1 = 1;
//	}
//	int longest = abs(width);
//	int shortest = abs(height);
//
//	if(!(longest > shortest))
//	{
//		int temp = longest;
//		longest = shortest;
//		shortest = temp;
//
//		if(height < 0)
//		{
//			dy2 = -1;
//		}
//		else
//		{
//			dy2 = 1;
//		}
//		dx2 = 0;
//	}
//	int numerator = longest >> 1;
//	for(int i = 0; i<= longest; i++)
//	{
//		//putpixel(A[0], A[1], Color);
//		numerator += shortest;
//		if(!(numerator<longest))
//		{
//			numerator -= longest;
//			A[0] += dx1;
//			A[1] += dy1;
//		}
//		else
//		{
//			A[0] += dx2;
//			A[1] += dy2;
//		}
//	}

    std::vector<int> edge;
	float dX = B[0] - A[0];
	float dY = B[1] - A[1];
	float d = 2*dY - dX;

	int octant = GetOctant(A, B);

	int y = (int)A[1];
    int x = (int)A.pos[0];

	SwitchToOctant(octant , A);
	SwitchToOctant(octant , B);

	for(; x <= (int)B[0]; x++)
	{
		//Plot(x,y)
		if(d > 0)
		{
			y++;
			d = d - 2*dX;
		}
		else
		{
			d = d + 2*dY;
		}
        Vertex C = Vertex(x,y,0);
		SwitchToOctantZero(octant, C);



        edge.push_back((int)C[0] + (int)A[0]);
        edge.push_back((int)C[1] + (int)A[1]);
        return edge;
	}
}

int SoftwareRendering::GetOctant(Vertex A, Vertex B)
{
	int octant = 0;

	float deltaX = B[0] - A[0];
	float deltaY = B[1] - A[1];
	float subX =  A[0] -B[0];
	float subY =  A[1] -B[1];

	if(B[0] > A[0])
	{
		if(B[1] > A[1])
		{
			if(deltaY < deltaX)
                octant = 0;
			else
                octant = 1;
		}
		else
		{
			if(subY < deltaX)
                octant = 7;
			else
                octant = 6;
		}
	}
	else
	{
		if(B[1] > A[1])
		{
			if(deltaY < subX)
                octant = 3;
			else
                octant = 2;
		}
		else
		{
            if(subY < subX)
                octant = 4;
            else
                octant = 5;
		}
	}
    return octant;
}

void SoftwareRendering::SwitchToOctantZero(int octant ,Vertex &B)
{
	float temp;
	switch (octant)
	{
		case 0:
			break;
		case 1:
			temp = B[0];
			B[0] = B[1];
			B[1] = temp;
			break;
		case 2:
			temp = -B[0];
			B[0] = B[1];
			B[1] = temp;
			break;
		case 3:
			B[0] = -B[0];
			break;
		case 4:
			B[0] = -B[0];
			B[1] = -B[1];
			break;
		case 5:
			temp = -B[0];
			B[0] = -B[1];
			B[1] = temp;
			break;
		case 6:
			temp = B[0];
			B[0] = -B[1];
			B[1] = temp;
			break;
		case 7:
			B[1] = -B[1];
			break;
	}

}

void SoftwareRendering::SwitchToOctant(int octant, Vertex &B)
{
    float temp;
    switch (octant)
    {
        case 0:
            break;
        case 1:
            temp = B[0];
            B[0] = B[1];
            B[1] = temp;
            break;
        case 2:
            temp = B[0];
            B[0] = -B[1];
            B[1] = temp;
            break;
        case 3:
            B[0] = -B[0];
            break;
        case 4:
            B[0] = -B[0];
            B[1] = -B[1];
            break;
        case 5:
            temp = -B[0];
            B[0] = -B[1];
            B[1] = temp;
            break;
        case 6:
            temp = -B[0];
            B[0] = B[1];
            B[1] = temp;
            break;
        case 7:
            B[1] = -B[1];
            break;
    }
}

void SoftwareRendering::Interpolate(Vertex A, Vertex B, Vertex C)
{
	float area[3];
	float triangleArea = TriangleArea(A, B,C); //<< Get the total area of the whole triangle


}

float SoftwareRendering::TriangleArea(Vertex A, Vertex B, Vertex C)
{
	return abs((A[0]*(B[1] - C[1])+B[0]*(C[1]-A[1])+C[0]*(A[1] - B[1]))*0.5);
}

void SoftwareRendering::Draw()
{

	//pixelColor = [texture, texturewidth, textureheight](vertex point)->color
	//{
	//	Color c;

	//	c.r = 0;
	//	c.g = 0;
	//	c.b = 0;

	//	int n = (int)(point.uv.get_Y() * th) * tw * 3 + (int)(point.uv.get_X() * tw) * 3;

	//	if (n < 0)
	//		return c;

	//	c.r = (int)tex[n];
	//	c.g = (int)tex[n + 1];
	//	c.b = (int)tex[n + 2];

	//	return c;
	//};
	Vertex left;
	Vertex top;
	Vertex right;
	this->RasterTriangle(left, top, right);
}
