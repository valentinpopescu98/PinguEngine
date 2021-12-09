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
	SetCamInternals(camera);
	SetCamDef(camera);

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
	SetCamInternals(camera);
	SetCamDef(camera);

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

void Culler::SetCamInternals(Camera& camera)
{
	// compute width and height of the near section
	tang = tan(glm::radians(camera.FOVdeg / 2));
	sphereFactorY = 1.0 / cos(camera.FOVdeg / 2);

	// compute half of the the horizontal field of view and sphereFactorX
	float anglex = glm::atan(tang * Engine::aspectRatio);
	sphereFactorX = 1.0 / cos(anglex);
	//heigth = nearD * tang;
	//width = height * ratio;
}

void Culler::SetCamDef(Camera& camera)
{
	// compute the Z axis of the camera referential
	// this axis points in the same direction from
	// the looking direction
	Z = camera.orientation - camera.position;
	glm::normalize(Z);

	// X axis of camera is the cross product of Z axis and given "up" vector 
	X = Z * camera.up;
	glm::normalize(X);

	// the real "up" vector is the cross product of X and Z
	Y = X * Z;
}

int Culler::SphereInFrustum(Camera& camera, glm::vec3 spherePos, float radius)
{
	float d;
	float az, ax, ay;
	int result = INSIDE;

	glm::vec3 v = spherePos - camera.position;

	az = glm::dot(v, -Z);
	if (az > camera.farPlane + radius || az < camera.nearPlane - radius)
		return(OUTSIDE);

	if (az > camera.farPlane - radius || az < camera.nearPlane + radius)
		result = INTERSECT;

	ay = glm::dot(v, Y);
	d = sphereFactorY * radius;
	az *= tang;
	if (ay > az + d || ay < -az - d)
		return(OUTSIDE);

	if (ay > az - d || ay < -az + d)
		result = INTERSECT;

	ax = glm::dot(v, X);
	az *= Engine::aspectRatio;
	d = sphereFactorX * radius;
	if (ax > az + d || ax < -az - d)
		return(OUTSIDE);

	if (ax > az - d || ax < -az + d)
		result = INTERSECT;

	return(result);
}