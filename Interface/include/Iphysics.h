#pragma once

#include"def/def_interface.h"

namespace Interface
{
	class Physics
	{
		DECLARE_INTERFACE(Physics)

	public:
		virtual bool Initialize() = 0;
		virtual void Release() = 0;
		virtual void OnFixupdata(unsigned int times) = 0;
	};
}