#include "FaceManager.h"

void face_manager::clipping_faces(const face face, const bypass bypass)
{
	glEnable(GL_CULL_FACE);
	glCullFace(face);
	glFrontFace(bypass);
}

void face_manager::disable_clipping_faces()
{
	glDisable(GL_CULL_FACE);
}
