#pragma once
#include "TextureResource.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


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

	data = stbi_load(filename, &width, &height, &comp, 4);

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
	unsigned char* temp = stbi_load(filename, &width, &height, &comp, 3);

	for (int i = 0; i < (width*height * 3); i++)
	{
		texture.push_back(data[i]);
	}
	delete temp;
	delete data;
}


void TextureResource::Apply()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TBO);
}

void TextureResource::ApplyNewTexture()
{
	if (TBO == 0)
	{
		glGenTextures(1, &TBO);
	}
	glBindTexture(GL_TEXTURE_2D, TBO);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 500, 500, 0, GL_RGB, GL_UNSIGNED_BYTE, &imageBuffer[0]);

	if (TBO == 0)
	{
		glActiveTexture(GL_TEXTURE0);
	}
	glBindTexture(GL_TEXTURE_2D, TBO);

	glGenerateMipmap(GL_TEXTURE_2D);
	glGenerateTextureMipmap(TBO);
}


