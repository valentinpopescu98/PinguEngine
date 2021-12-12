#include "Culler.h"

glm::vec3 Culler::X, Culler::Y, Culler::Z;
float Culler::sphereFactorX, Culler::sphereFactorY;
float Culler::tang;

void Culler::FrontFaceCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
}

void Culler::BackFaceCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

bool Culler::MeshInFrustum(Camera& camera, Mesh& mesh)
{
	float longestSide = mesh.scale.x;
	longestSide = mesh.scale.y > mesh.scale.x ? mesh.scale.y : mesh.scale.x;
	longestSide = mesh.scale.z > longestSide ? mesh.scale.z : longestSide;

	int status = SphereInFrustum(camera, mesh.position, longestSide);
	if (status == OUTSIDE)
	{
		return false;
	}
	return true;
}

bool Culler::ModelInFrustum(Camera& camera, Model& model)
{
	float longestSide = model.scale.x;
	longestSide = model.scale.y > model.scale.x ? model.scale.y : model.scale.x;
	longestSide = model.scale.z > longestSide ? model.scale.z : longestSide;

	int status = SphereInFrustum(camera, model.position, longestSide);
	if (status == OUTSIDE)
	{
		return false;
	}
	return true;
}

void Culler::ComputeSphereData(Camera& camera)
{
	float angleY = glm::radians(camera.fovY / 2.0f); // Compute half of the the vertical FOV in radians
	tang = tan(angleY); // Tangent needed to calculate the height of the frustum
	sphereFactorY = 1.0f / cos(angleY); // How small the the sphere is vertically relative to its size near the camera

	float angleX = glm::atan(tang * Engine::aspectRatio); // Compute half of the the horizontal FOV in radians
	sphereFactorX = 1.0f / cos(angleX); // How small the the sphere is horizontally relative to its size near the camera

	Z = glm::normalize(camera.forward - camera.position); // Forward vector from camera
	X = glm::normalize(glm::cross(Z, camera.vecUp)); // Right vector from camera
	Y = glm::cross(X, Z); // Up vector from camera
}

int Culler::SphereInFrustum(Camera& camera, glm::vec3 spherePos, float radius)
{
	ComputeSphereData(camera);

	float d; // The sphere radius length without taking perspective in consideration
	float ax, ay, az; // Sphere center coordinates relative to camera's X, Y, Z
	int result = INSIDE; // Sphere actual state

	glm::vec3 v = spherePos - camera.position; // Vector from camera to sphere center

	az = glm::dot(v, Z);
	// Check if sphere inner radius is outside the frustum on OZ axis
	if (az > camera.farPlane + radius or az < camera.nearPlane - radius)
		return(OUTSIDE);
	// Check if sphere inner radius is intersecting the frustum on OZ axis
	if (az > camera.farPlane - radius or az < camera.nearPlane + radius)
		result = INTERSECT;

	ay = glm::dot(v, Y);
	az *= tang; // This is now the height of the frustum
	d = sphereFactorY * radius;
	// Check if sphere inner radius is outside the frustum on OY axis
	if (ay > az + d or ay < -az - d)
		return(OUTSIDE);
	// Check if sphere inner radius is intersecting the frustum on OY axis
	if (ay > az - d or ay < -az + d)
		result = INTERSECT;

	ax = glm::dot(v, X);
	az *= Engine::aspectRatio; // This is now the width of the frustum
	d = sphereFactorX * radius;
	// Check if sphere inner radius is outside the frustum on OX axis
	if (ax > az + d or ax < -az - d)
		return(OUTSIDE);
	// Check if sphere inner radius is intersecting the frustum on OX axis
	if (ax > az - d or ax < -az + d)
		result = INTERSECT;

	return(result);
}