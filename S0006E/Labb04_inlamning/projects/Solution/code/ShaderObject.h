#pragma once
#include "GL\glew.h"
#include <string>
#include <map>


class ShaderObject
{
	public:
		ShaderObject();
		~ShaderObject();
		std::string ReadFromFile(const char* filename);
		void LoadShader(const char *vertex_path, const char *fragment_path);
		void Apply();
		void ModifyMatrix(char* matName, float* pos);
		void ModifyVector(char* vecName, float* pos);


		GLuint program;
		std::map<char*,GLuint>location;
};