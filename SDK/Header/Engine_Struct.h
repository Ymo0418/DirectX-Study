#pragma once

namespace Engine 
{
	struct WND_DESC
	{
		HWND hWnd;
		HINSTANCE hInst;
		uint iWinSizeX, iWinSizeY;
		bool isWindow;
	};

	struct MY_DLL VtxPosCol
	{
		XMFLOAT3 vPos;
		XMFLOAT3 vColor;

		static const uint iNumElemet = 2;
		static const D3D11_INPUT_ELEMENT_DESC Elements[2];
	};
}