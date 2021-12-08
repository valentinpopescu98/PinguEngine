#include "Culler.h"

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

void Culler::FrustumCulling()
{

}

//Frustum CreateFrustumFromCamera(const Camera& cam, float aspect, float fovY, float zNear, float zFar)
//{
//    Frustum frustum;
//    const float halfVSide = zFar * tanf(fovY * 0.5f);
//    const float halfHSide = halfVSide * aspect;
//    const glm::vec3 frontMultFar = zFar * cam.orientation;
//
//    frustum.topFace = { cam.position, glm::cross(cam.right, frontMultFar - cam.up * halfVSide) };
//    frustum.bottomFace = { cam.position, glm::cross(frontMultFar + cam.up * halfVSide, cam.right) };
//
//    frustum.leftFace = { cam.position, glm::cross(frontMultFar - cam.right * halfHSide, cam.up) };
//    frustum.rightFace = { cam.position, glm::cross(cam.up, frontMultFar + cam.right * halfHSide) };
//
//    frustum.nearFace = { cam.position + zNear * cam.orientation, cam.orientation };
//    frustum.farFace = { cam.position + frontMultFar, -cam.orientation };
//
//    return frustum;
//}