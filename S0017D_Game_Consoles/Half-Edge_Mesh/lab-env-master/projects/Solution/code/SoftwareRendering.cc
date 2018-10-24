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
    Interpolate(left,top, right);

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
//    std::vector<int> edge;
//	float dX = B[0] - A[0];
//	float dY = B[1] - A[1];
//	float d = 2*dY - dX;
//
//	int octant = GetOctant(A, B);
//
//
//	int y = (int)A.pos[1];
//    int x = (int)A.pos[0];
//
//	SwitchToOctant(octant , A);
//    SwitchToOctantZero(octant, B);
//
//	for(; x < (int)B[0]; x++)
//	{
//		//Plot(x,y)
//		if(d > 0)
//		{
//			y++;
//			d = d - 2*dX;
//		}
//
//        d = d + 2*dY;
//        //Vertex C = Vertex(x,y,0);
//        SwitchToOctant(octant, B);
//
//        edge.push_back((int)B[0] + (int)A[0]);
//        edge.push_back((int)B[1] + (int)A[1]);
//        return edge;
//	}
}

int SoftwareRendering::GetOctant(Vertex A, Vertex B)
{
	int octant = 0;

//	float deltaX = B[0] - A[0];
//	float deltaY = B[1] - A[1];
//	float subX =  A[0] -B[0];
//	float subY =  A[1] -B[1];
//
//	if(B[0] > A[0])
//	{
//		if(B[1] > A[1])
//		{
//			if(deltaY < deltaX)
//                octant = 0;
//			else
//                octant = 1;
//		}
//		else
//		{
//			if(subY < deltaX)
//                octant = 7;
//			else
//                octant = 6;
//		}
//	}
//	else
//	{
//		if(B[1] > A[1])
//		{
//			if(deltaY < subX)
//                octant = 3;
//			else
//                octant = 2;
//		}
//		else
//		{
//            if(subY < subX)
//                octant = 4;
//            else
//                octant = 5;
//		}
//	}
//    return octant;
}

void SoftwareRendering::SwitchToOctantZero(int octant ,Vertex &B)
{
//	float temp;
//    float x = B[0];
//    float y = B[1];
//	switch (octant)
//	{
//		case 0:
//			break;
//		case 1:
//			temp = x;
//			x = y;
//			y = temp;
//			break;
//		case 2:
//			temp = -x;
//			x = y;
//			y = temp;
//			break;
//		case 3:
//			x = -x;
//			break;
//		case 4:
//			x = -x;
//			y *= -y;
//			break;
//		case 5:
//			temp = -x;
//			x = -y;
//			y = temp;
//			break;
//		case 6:
//			temp = x;
//			x = -y;
//			y = temp;
//			break;
//		case 7:
//			y = -y;
//			break;
//	}
//    *B.pos[0] = x;
//    *B.pos[1] = y;
}

void SoftwareRendering::SwitchToOctant(int octant, Vertex &B)
{
//    float temp;
//    float x = B[0];
//    float y = B[1];
//    switch (octant)
//    {
//        case 0:
//            break;
//        case 1:
//            temp = x;
//            x = y;
//            y = temp;
//            break;
//        case 2:
//            temp = x;
//            x = -y;
//            y = temp;
//            break;
//        case 3:
//            x = -x;
//            break;
//        case 4:
//            x = -x;
//            y = -y;
//            break;
//        case 5:
//            temp = -x;
//            x = -y;
//            y = temp;
//            break;
//        case 6:
//            temp = -x;
//            x = y;
//            y = temp;
//            break;
//        case 7:
//            y = -y;
//            break;
//    }
//    *B.pos[0] = x;
//    *B.pos[1] = y;
}

void SoftwareRendering::Interpolate(Vertex A, Vertex B, Vertex C)
{
	float area[3];
	float triangleArea = TriangleArea(A, B,C); //<< Get the total area of the whole triangle

    area[0] = TriangleArea(A,B,C);
    area[1] = TriangleArea(B,C,A);
    area[2] = TriangleArea(C,A,B);

    float percent[3];
    percent[0] = area[0]/triangleArea; //<< Percent Red
    percent[1] = area[1]/triangleArea; //<< Percent Green
    percent[2] = area[3]/triangleArea; //<< Percent Blue

    //Arrays so that we can use them in the loop
    float textureCoord[] = {0,0};
    float normals[] = {0,0,0};
    float position[] = {0,0,0};

    Vector4D textureCoord4D[] ={A.uv, B.uv, C.uv};
    Vector4D normals4D[] = {A.normal, B.normal, C.normal};
    Vector4D position4D[] = {A.pos, B.pos, C.pos};

    // Adding interpolation to normals and texture coordinates
    for(int i = 0; i<3; i++)
    {
        textureCoord[0] += *textureCoord4D[i][0] * percent[i];
        textureCoord[1] += *textureCoord4D[i][1] * percent[i];

        normals[0] += *normals4D[i][0] * percent[i];
        normals[1] += *normals4D[i][1] * percent[i];
        normals[2] += *normals4D[i][2] * percent[i];

        position[0] += *position4D[i][0] * percent[i];
        position[1] += *position4D[i][1] * percent[i];
        position[2] += *position4D[i][2] * percent[i];
    }

    float depth = 0;
    depth += *A.pos[2] * percent[0];
    depth += *B.pos[2] * percent[1];
    depth += *C.pos[2] * percent[2];

    Vertex D;
    D.pos = Vector4D(position[0],position[1],position[2]);
    //D.screenSpace = Vector4D(0, 0, depth);
    D.uv = Vector4D(textureCoord[0],textureCoord[1],0);
    D.normal = Vector4D(normals[0], normals[1], normals[2]);
}

float SoftwareRendering::TriangleArea(Vertex A, Vertex B, Vertex C)
{
//	return abs((A[0]*(B[1] - C[1])+B[0]*(C[1]-A[1])+C[0]*(A[1] - B[1]))*0.5);
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
