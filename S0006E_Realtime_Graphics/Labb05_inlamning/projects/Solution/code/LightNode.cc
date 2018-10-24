#include "LightNode.h"

void LightNode::SetPos(float x, float y, float z)
{
	pos.Set(x, y, z);
}

void LightNode::SetSpec(float x, float y, float z)
{
	spec.Set(x, y, z);
}

void LightNode::SetDiff(float x, float y, float z)
{
	diff.Set(x, y, z);
}

void LightNode::SetAmb(float x, float y, float z)
{
	amb.Set(x, y, z);
}

void LightNode::SetIntensity(float shiny)
{
	intensity = shiny;
}

Vector4D LightNode::GetPos()
{
	return pos;
}

Vector4D LightNode::GetSpec()
{
	return spec;
}

Vector4D LightNode::GetDiff()
{
	return diff;
}

Vector4D LightNode::GetAmb()
{
	return amb; 
}

float LightNode::GetIntensity()
{
	return intensity;
}