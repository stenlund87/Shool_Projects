#pragma once

#include "TextureResource.h"


#include <stb_image.h>


TextureResource::TextureResource()
{

}

TextureResource::~TextureResource()
{
	glDeleteBuffers(1, &TBO);
	glDeleteTextures(1, &TBO);
}

void TextureResource::LoadFromFile(const char* filename)
{
	glGenTextures(1, &TBO);
	glBindTexture(GL_TEXTURE_2D, TBO);
	glBindBuffer(GL_ARRAY_BUFFER, TBO);

	int height, width, comp;
	unsigned char* data = stbi_load(filename, &width, &height, &comp, 4);

	if (data == nullptr)
	{
		throw "Image couldn't be loaded";
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glGenerateTextureMipmap(TBO);
	glBindTexture(GL_TEXTURE_2D, 0);

	delete data;
}


void TextureResource::Apply()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TBO);
}

