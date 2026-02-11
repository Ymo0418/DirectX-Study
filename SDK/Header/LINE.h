#pragma once
#include "Engine_Define.h"
#ifdef _DEBUG
#include "DebugDraw.h"
#endif // _DEBUG

struct MY_DLL LINE
{
	FPOINT left;
	FPOINT right;

	float a;
	float b;
	LINE* Neighbors[2] = { nullptr, nullptr };

	LINE(const FPOINT& l, const FPOINT& r) {
		left = l;
		right = r;
		a = (right.y - left.y) / (right.x - left.x);
		b = left.y - a * left.x;
	}

	float Get_Height(XMVECTOR vPos) {
		return a * XMVectorGetX(vPos) + b;
	}
	bool IsWithinLine(float x) {
		return (left.x <= x && right.x);
	}

#ifdef _DEBUG
	void Render(PrimitiveBatch<VertexPositionColor>* _pBatch, XMVECTOR vColor) {
		XMVECTOR vLeft = { left.x, left.y, 0, 1 };
		XMVECTOR vDir = { right.x - left.x, right.y - left.y, 0, 0 };
		DX::DrawRay(_pBatch, vLeft, vDir, false, vColor);
	}
#endif // _DEBUG

};

