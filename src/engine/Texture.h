#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <iostream>

class Texture
{
	public:
		void Create(const char* imagePath, GLenum unit);
		void Delete();
		void Bind(GLenum textureType);
		void Unbind();
		int GenerateMipmap(GLint interpType, GLint wrapType);
		void GenerateMipmap(GLint interpType, float borderColor[]);

		GLuint ID;
		GLenum dimension;

	private:
		int widthImage, heightImage, numColCh; // Width, height and number of color channels
		unsigned char* bytes;
};