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
	meshRes = std::make_shared<MeshResource>(*MeshResource::Load("yavin.obj"));
	//meshRes = std::make_shared<MeshResource>(*MeshResource::Load("sword.obj"));

	texture = std::make_shared<TextureResource>();
	shaderObj = std::make_shared<ShaderObject>();

	texture->LoadFromFile("Yavin.jpg");
	shaderObj->LoadShader("verticeShader.txt", "ps.txt");
}

void GraphicsNode::SetTransform(Matrix4D trans, Matrix4D norm)
{
	this->transform = trans;
	this->normal = norm;
}

void GraphicsNode::Draw()
{
	texture->Apply();
	shaderObj->Apply();
	shaderObj->ModifyMatrix("matrix", (float*)this->transform.matrix);
	shaderObj->ModifyMatrix("normalMat", (float*)this->normal.matrix);

	shaderObj->ModifyVector("lightPos", shaderObj->light.GetPos().GetVector());
	shaderObj->ModifyVector("ambientColor", shaderObj->light.GetAmb().GetVector());
	shaderObj->ModifyVector("diffuseColor", shaderObj->light.GetDiff().GetVector());

	shaderObj->ModifyVector("specColor", shaderObj->light.GetSpec().GetVector());
	shaderObj->ModifyFloat("shininess", shaderObj->light.GetIntensity());

	meshRes->Draw();
}

void GraphicsNode::InitSkeleton()
{
	shaderObj = std::make_shared<ShaderObject>();
	shaderObj->LoadShader("verticeShader.txt", "ps.txt");

	skel = std::make_shared<Skeleton>();
	skel->ReadFromFile("Unit_Footman.constants");
	skel->CalculateOriginal();

	anim = std::make_shared<Animation>();
	anim->SetupNax3("Unit_Footman.nax3");

	skin = std::make_shared<Skinning>();
	skin->ReadHeadData("Unit_Footman.nvx2");
	skin->ReadPrimitive();
	skin->SetupVertex();
	skin->SetupVertexBuffer();
	skin->SetupIndiceBuffer();
}

void GraphicsNode::DrawSkeleton(int currentAnimation, float dt)
{
	shaderObj->Apply();
	shaderObj->ModifyMatrix("matrix", (float*)this->transform.matrix);
	shaderObj->ModifyMatrix("normalMat", (float*)this->normal.matrix);

	anim->SetupAnimation(currentAnimation,skel.get(),dt);
	skin->BindToSkeleton(skel.get());
//	skin->DrawSkin();
}