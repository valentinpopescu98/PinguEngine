#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <iostream>

class Texture
{
	public:
		void Create(const char* imagePath, GLuint id, GLenum unit);
		void Delete(GLuint id);
		void Bind(GLenum dimension, GLuint id);
		void Unbind();
		int GenerateMipmap(GLint interpType, GLint wrapType);
		void GenerateMipmap(GLint interpType, float borderColor[]);

		GLenum dimension;
		GLuint id;
	private:
		int widthImage, heightImage, numColCh; // Width, height and number of color channels
		unsigned char* bytes;
};