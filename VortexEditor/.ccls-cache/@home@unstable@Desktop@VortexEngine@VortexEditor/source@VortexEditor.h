#pragma once
#include "EditorLayer.h"

namespace Vortex
{
	class VortexEditor : public ApplicationClass
	{
	public:
		VortexEditor();

		~VortexEditor();

		virtual void OnStart() override;
		virtual void OnUpdate() override;
	};
}