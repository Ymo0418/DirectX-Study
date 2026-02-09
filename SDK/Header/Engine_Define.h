#pragma once

#pragma warning (disable : 4251)

#include <d3d11.h>
#include <d3dcompiler.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <DirectXCollision.h>

#include "DirectXTK/DDSTextureLoader.h"
#include "DirectXTK/WICTextureLoader.h"
#include "DirectXTK/VertexTypes.h"
#include "DirectXTK/PrimitiveBatch.h"
#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "DirectXTK/Effects.h"
#include "DirectXTK/ScreenGrab.h"
#include "Effects11/d3dx11effect.h"

#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <DirectXMath.h>

using namespace DirectX;
using namespace std;

#include "Engine_Typedef.h"
#include "Engine_Function.h"
#include "Engine_Macro.h"
#include "Engine_Struct.h"

namespace Engine
{

}

using namespace Engine;

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#endif

#ifdef _DEBUG
#define DEB_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif