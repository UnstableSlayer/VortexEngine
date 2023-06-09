#pragma once

//-----------------------------------------
//----for use in game application----------
//-----------------------------------------

//#include "Core/Allocator.h"
#include "Core/Core.h"
#include "Core/Logger.h"
#include "Core/Assert.h"

#include "Core/RefCounter.h"

#include "Core/App.h"
#include "Core/Layer.h"
#include "Core/Time.h"

#include "Input/Input.h"
#include "Input/InputManager.h"
#include "Events/KeyCodes.h"
#include "Events/MouseCodes.h"

#include "Core/RNG.h"

//----Scene--------------------------------
#include "../thirdParty/Entt/include/entt/entt.hpp"
#include "Environment/Object.h"
#include "Environment/Scene.h"
#include "Environment/Components.h"
#include "Environment/ComponentModifiers.h"

//----ImGui--------------------------------
#include "../thirdParty/imgui/imgui.h"
#include "ImGui/ImGuiLayer.h"

//----Rendering----------------------------
#include "Renderer/Renderer2D.h"
#include "Renderer/Renderer3D.h"
#include "Renderer/RenderCommand.h"

#include "Renderer/Buffers.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include "Renderer/Framebuffer.h"

//----Job System----------------------------

#include "Jobs/JobData.h"
#include "Jobs/JobScheduler.h"
