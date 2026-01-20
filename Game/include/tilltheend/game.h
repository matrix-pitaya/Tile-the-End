#pragma once

#include"def/def_delete_copy_move.h"

#include"Igame.h"

namespace Game
{
	class TilltheEnd : public Interface::Game
	{
		DELETE_COPY_AND_MOVE(TilltheEnd)
	public:
		TilltheEnd() = default;
		~TilltheEnd() = default;
	};
}
