#pragma once

#include"def/def_delete_copy_move.h"

#include"Iphysics.h"

namespace Physics
{
	class PitayaPhysics : public Interface::Physics
	{
		DELETE_COPY_AND_MOVE(PitayaPhysics)

	public:
		PitayaPhysics() = default;
		~PitayaPhysics() = default;
	};
}