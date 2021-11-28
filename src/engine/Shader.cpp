#include "Shader.h"

void Shader::Create(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	std::string vertexCode = GetFileContents(vertexShaderPath); // Store VS source code in a string
	std::string fragmentCode = GetFileContents(fragmentShaderPath); // Store FS source code in a string

	const char* vertexSource = vertexCode.c_str(); // Convert the VS code into a recognizable format by GLAD (char array)
	const char* fragmentSource = fragmentCode.c_str(); // Convert the FS code into a recognizable format by GLAD (char array)

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create VS object
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // Attach VS source code to VS object
	glCompileShader(vertexShader); // Compile VS into machine code
	CheckErrors(vertexShader, "VERTEX"); // Check for errors for VS

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create FS object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // Attach FS source code to VS object
	glCompileShader(fragmentShader); // Compile FS into machine code
	CheckErrors(fragmentShader, "FRAGMENT"); // Check for errors for FS

	ID = glCreateProgram(); // Create final object shader
	glAttachShader(ID, vertexShader); // Attach VS to the new shader
	glAttachShader(ID, fragmentShader); // Attach FS to the new shader
	glLinkProgram(ID); // Link final shader into the shading program
	CheckErrors(ID, "PROGRAM"); // Check for error for the main shader

	glDeleteShader(vertexShader); // Delete VS object
	glDeleteShader(fragmentShader); // Delete FS object
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::Use()
{
	glUseProgram(ID); // Use shader
}

void Shader::CheckErrors(GLuint shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
		}
	}
}