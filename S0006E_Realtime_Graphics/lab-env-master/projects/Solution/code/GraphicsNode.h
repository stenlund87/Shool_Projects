#pragma once
#include "MeshResource.h"
#include "TextureResource.h"
#include "ShaderObject.h"
#include <memory>


class GraphicsNode
{
	public:
		GraphicsNode();
		~GraphicsNode();

		/* Methods for MeshResource */
		std::shared_ptr<MeshResource> GetMesh();
		void SetMesh(std::shared_ptr<MeshResource> mesh);
		MeshResource* GetMeshPointer() { return meshRes.get(); };


		/* Methods for TextureResource */
		std::shared_ptr<TextureResource> GetTexture();
		void SetTexture(std::shared_ptr<TextureResource> tex);
		TextureResource* GetTexturePointer() { return texture.get(); };

		/* Methods for ShaderObject */
		std::shared_ptr<ShaderObject> GetShader();
		void SetShader(std::shared_ptr<ShaderObject> shader);

		void InitNode();

		void InitRasterizer();

		/* Methods to change the object */
		void SetTransform(Matrix4D trans, Matrix4D norm);
		void Draw();

		std::shared_ptr<MeshResource> meshRes;
		std::shared_ptr<TextureResource> texture;
		std::shared_ptr<ShaderObject> shaderObj;

		Matrix4D transform;
		Matrix4D normal;

};