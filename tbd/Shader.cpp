#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexString = getShaderSrc(vertexPath);
	std::string fragmentString = getShaderSrc(fragmentPath);

	const char* vertexSrc = vertexString.c_str();
	const char* fragmentSrc = fragmentString.c_str();

	unsigned int vertexShader = compileShader(vertexSrc, GL_VERTEX_SHADER);
	unsigned int fragmentShader = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);
	linkProgram(vertexShader, fragmentShader);
}

void Shader::linkProgram(unsigned int& vertexShader, unsigned int& fragmentShader)
{
	char infoLog[512];
	int success;
	this->id = glCreateProgram();
	glAttachShader(this->id, vertexShader);
	glAttachShader(this->id, fragmentShader);
	glLinkProgram(this->id);

	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(0);

}

unsigned int Shader::compileShader(const char* src, unsigned int type)
{
	char infoLog[512];
	int success;
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << src << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

std::string Shader::getShaderSrc(const char* filePath)
{
	std::string temp = "";
	std::string tempSrc = "";

	std::ifstream file;
	file.open(filePath);
	if (file.is_open())
		while (std::getline(file, temp))
			tempSrc += temp + "\n";
	
	file.close();
	
	return tempSrc;
}

void Shader::use()
{
	glUseProgram(this->id);
}
void Shader::unUse()
{
	glUseProgram(0);
}

void Shader::setBool(const std::string& name, bool value)
{
	use();
	glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
	unUse();
}
void Shader::setInt(const std::string& name, int value)
{
	use();
	glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
	unUse();
}
void Shader::setFloat(const std::string& name, float value) 
{
	use();
	glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
	unUse();
}