#include "CBase.h"

CBase::CBase()
{
}

//증가된 값이 반환
uint CBase::AddRef()
{
	return ++m_iRefCnt;
}

//감소 전 값이 반환
uint CBase::Release()
{
	if (m_iRefCnt != 0)
	{
		return m_iRefCnt--;
	}
	else
	{
		Free();
		delete this;
		return 0;
	}
}

void CBase::Free()
{

}