#pragma once
#include "GraphicsNode.h"

GraphicsNode::GraphicsNode()
{

}

GraphicsNode::~GraphicsNode()
{
	
}

std::shared_ptr<MeshResource> GraphicsNode::GetMesh()
{
	return meshRes;
}

void GraphicsNode::SetMesh(std::shared_ptr<MeshResource> mesh)
{
	meshRes = mesh;
}

std::shared_ptr<TextureResource> GraphicsNode::GetTexture()
{
	return texture;
}

void GraphicsNode::SetTexture(std::shared_ptr<TextureResource> tex)
{
	texture = tex;
}

std::shared_ptr<ShaderObject> GraphicsNode::GetShader()
{
	return shaderObj;
}

void GraphicsNode::SetShader(std::shared_ptr<ShaderObject> shader)
{
	shaderObj = shader;
}

void GraphicsNode::InitNode()
{
	meshRes = std::make_shared<MeshResource>(*MeshResource::MakeCube());
	texture = std::make_shared<TextureResource>();
	shaderObj = std::make_shared<ShaderObject>();

	texture->LoadFromFile("D:\\Zelda3.jpg");
	texture->SetupTexture();
	shaderObj->LoadShader("D:\\verticeShader.txt", "D:\\ps.txt");
}

void GraphicsNode::SetTransform(Matrix4D trans)
{
	shaderObj->ModifyMatrix("matrix", *trans.matrix);
}

void GraphicsNode::Draw(float* pos)
{
	shaderObj->Apply();
	shaderObj->ModifyMatrix("matrix", pos);
	meshRes->Draw();
}