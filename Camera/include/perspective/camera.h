#pragma once

#include"def/def_delete_copy_move.h"

#include"Icamera.h"

namespace Camera
{
	class PerspectiveCamera : public Interface::Camera
	{
		DELETE_COPY_AND_MOVE(PerspectiveCamera)

	public:
		PerspectiveCamera() = default;
		~PerspectiveCamera() = default;
	};
}