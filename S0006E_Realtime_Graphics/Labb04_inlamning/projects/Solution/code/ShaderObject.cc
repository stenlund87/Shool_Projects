#pragma once
#include "ShaderObject.h"
#include <iostream>
#include <fstream>
#include <vector>


ShaderObject::ShaderObject()
{

}

ShaderObject::~ShaderObject()
{
}


std::string ShaderObject::ReadFromFile(const char* filename)
{
	std::string content;
	std::ifstream fileStream(filename, std::ios::in);

	if (!fileStream.is_open()) 
	{
		std::cerr << "Could not read file " << filename << ". File does not exist." << std::endl;
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
 		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

void ShaderObject::LoadShader(const char *vertex_path, const char *fragment_path)
{
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Read shaders
	std::string vShaderStr = ReadFromFile(vertex_path);
	std::string fShaderStr = ReadFromFile(fragment_path);
	const char *vShaderSrc = vShaderStr.c_str();
	const char *fShaderSrc = fShaderStr.c_str();

	GLint result = GL_FALSE;
	int logLength;

	// Compile vertex shader
	glShaderSource(vShader, 1, &vShaderSrc, NULL);
	glCompileShader(vShader);

	// Check vertex shader
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &logLength);


	// Compile fragment shader
	glShaderSource(fShader, 1, &fShaderSrc, NULL);
	glCompileShader(fShader);

	// Check fragment shader
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &logLength);


	this->program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> programError((logLength > 1) ? logLength : 1);
	glGetProgramInfoLog(program, logLength, NULL, &programError[0]);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void ShaderObject::Apply()
{
	glUseProgram(this->program);
}

void ShaderObject::ModifyMatrix(char* matName, float* pos)
{
	if (location.find(matName) == location.end())
	{
		location[matName] = glGetUniformLocation(this->program, matName);
	}
	glUniformMatrix4fv(location.find(matName)->second, 1, GL_TRUE, pos);
}

void ShaderObject::ModifyVector(char* vecName, float* pos)
{
	if (location.find(vecName) == location.end())
	{
		location[vecName] = glGetUniformLocation(this->program, vecName);
	}
	glUniform4fv(location.find(vecName)->second, 1, pos);
}