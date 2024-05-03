#ifndef SHADER_H
#define SHADER_H

#include "glew.h"

#include "string"
#include "fstream"
#include "iostream"
#include "sstream"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"

class Shader
{
public:
	unsigned int id;

	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader() { glDeleteProgram(this->id); }

	void use();
	void unUse();

	std::string getShaderSrc(const char* filePath);

	unsigned int compileShader(const char* src, unsigned int type);
	void linkProgram(unsigned int& vertexShader, unsigned int& fragmentShader);

	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);

	void setMat4fv(const char* name, glm::mat4 value)
	{
		use();
		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(value));
		unUse();
	}
};

#endif
