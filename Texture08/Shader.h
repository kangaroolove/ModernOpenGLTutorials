#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class Shader
{
public:
	GLuint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Use();
	void setInt(const std::string& name, int value) const;
	void setBool(const std::string& name, bool value) const;
	void setFloat(const std::string& name, float value) const;
};
