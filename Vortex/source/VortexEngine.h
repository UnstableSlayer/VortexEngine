#pragma once
//for use in game application
#include "..\source\Core\Core.h"
#include "..\source\Core\Assert.h"
#include "..\source\Core\Logger.h"

#include "..\source\Core\ApplicationClass.h"
#include "..\source\Core\Layer.h"

#include "..\source\Core\Input.h"
#include "..\source\Core\Events\KeyCodes.h"
#include "..\source\Core\Events\MouseCodes.h"

#include "..\source\Core\RNG.h"

//---Scene---------------------------------
#include "..\thirdParty\Entt\include\entt\entt.hpp"
#include "..\source\Core\Envirovnemt\Object.h"
#include "..\source\Core\Envirovnemt\Scene.h"
#include "..\source\Core\Envirovnemt\Components.h"

//----Rendering----------------------------
#include "..\source\Core\Renderer\Renderer2D.h"
#include "..\source\Core\Renderer\RenderCommand.h"

#include "..\source\Core\Renderer\Buffers.h"
#include "..\source\Core\Renderer\Shader.h"
#include "..\source\Core\Renderer\Texture.h"
#include "..\source\Core\Renderer\SubTexture2D.h"
#include "..\source\Core\Renderer\Mesh.h"

#include "..\source\Core\Renderer\Framebuffer.h"

#include "..\source\Core\Renderer\Camera.h"

#include "..\source\Core\Time.h"
//----Job System----------------------------

#include "..\source\Core\Jobs\Coroutine.h"

//-------------------------------------------