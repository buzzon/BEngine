#include "Shader.h"
#include "Tools.h"

Shader::Shader()
{
	index = 1;
}

Shader::Shader(GLenum shaderType, const char * path)
{
	const GLchar* ShaderSource = Tools::ReadFile(path);

	index = glCreateShader(shaderType);
	glShaderSource(index, 1, &ShaderSource, NULL);
	glCompileShader(index);

	glGetShaderiv(index, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(index, infoLogSize, NULL, infoLog);
		std::cout << "ERROR::"<< shaderType  << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
