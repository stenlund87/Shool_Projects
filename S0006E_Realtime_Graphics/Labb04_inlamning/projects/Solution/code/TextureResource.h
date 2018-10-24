#pragma once
#include "GL\glew.h"


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
		void SetupTexture();

	protected:
		GLuint TBO;

};