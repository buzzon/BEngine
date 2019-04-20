#include "FaceManager.h"

void FaceManager::ClippingFaces(Face face, Bypass bypass)
{
	glEnable(GL_CULL_FACE);
	glCullFace(face);
	glFrontFace(bypass);
}

void FaceManager::DisableClippingFaces()
{
	glDisable(GL_CULL_FACE);
}
