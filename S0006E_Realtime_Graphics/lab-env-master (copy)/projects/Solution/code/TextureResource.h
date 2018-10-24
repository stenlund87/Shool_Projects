#pragma once
#include "GL/glew.h"
#include <vector>

class TextureResource
{
	public:
		TextureResource();
		~TextureResource();

		/**
		*Method to load texture from file
		*/
		void LoadFromFile(const char* filename);

		/**
		*Method to activate texture
		*/
		void Apply();

		void ApplyNewTexture();
	
		unsigned char* data;
		std::vector<unsigned char> texture; // Texture that will be put on object
		std::vector<unsigned char> imageBuffer; // Only used for the rasterizer


		int height, width, comp;

	protected:
		GLuint TBO;
		

};