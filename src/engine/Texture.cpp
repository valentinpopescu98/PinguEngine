#include "Texture.h"

void Texture::Create(const char* imagePath, GLuint id, GLenum unit)
{
	this->id = id;

	stbi_set_flip_vertically_on_load(true); // Flip the texture, so that [0, 0] is in the bottom left, not top left
	bytes = stbi_load(imagePath, &widthImage, &heightImage, &numColCh, 0); // Read data from the texture and store it in image's variables

	glGenTextures(1, &id); // Create a texture
	glActiveTexture(unit); // Activate texture of given unit
}

void Texture::Delete(GLuint id)
{
	glDeleteTextures(1, &id); // Delete texture by id
}

void Texture::Bind(GLenum dimension, GLuint id)
{
	this->dimension = dimension;
	glBindTexture(dimension, id); // Bind the texture as 2D texture
}

void Texture::Unbind()
{
	stbi_image_free(bytes); // Delete image data
	glBindTexture(dimension, 0); // Unbind texture
}

// Base overload function
int Texture::GenerateMipmap(GLint interpType, GLint wrapType)
{
	if (wrapType == GL_CLAMP_TO_BORDER)
	{
		std::cout << "Please specify the color using the other overload of this method." << std::endl;
		return -1;
	}

	glTexParameteri(dimension, GL_TEXTURE_MIN_FILTER, interpType); // Interpolate texture pixels with chosen type when minifying
	glTexParameteri(dimension, GL_TEXTURE_MAG_FILTER, interpType); // Interpolate texture pixels with chosen type when magnifying

	glTexParameteri(dimension, GL_TEXTURE_WRAP_S, wrapType); // Cover empty horizontal space with the chosen wrapping style
	glTexParameteri(dimension, GL_TEXTURE_WRAP_T, wrapType); // Cover empty vertical space with the chosen wrapping style

	glTexImage2D(dimension, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes); // Process texture
	glGenerateMipmap(dimension); // Create mip-map
}

// Overload for wrapping with GL_CLAMP_TO_BORDER
void Texture::GenerateMipmap(GLint interpType, float borderColor[])
{
	glTexParameteri(dimension, GL_TEXTURE_MIN_FILTER, interpType); // Interpolate texture pixels with chosen type when minifying
	glTexParameteri(dimension, GL_TEXTURE_MAG_FILTER, interpType); // Interpolate texture pixels with chosen type when magnifying

	glTexParameteri(dimension, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); // Cover empty horizontal space with the given color
	glTexParameteri(dimension, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); // Cover empty vertical space with the given color

	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexImage2D(dimension, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes); // Process texture
	glGenerateMipmap(dimension); // Create mip-map
}