#ifndef Engine_Function_h__
#define Engine_Function_h__

namespace Engine
{
	template<typename T>
	unsigned int Safe_Release(T& pInstance)
	{
		unsigned int refCnt = { 0 };

		if (nullptr != pInstance)
		{
			refCnt = pInstance->Release();

			if (0 == refCnt)
				pInstance = nullptr;
		}

		return refCnt;
	}

	template<typename T>
	unsigned int Safe_AddRef(T& pInstance)
	{
		unsigned int refCnt = { 0 };

		if (nullptr != pInstance)
		{
			refCnt = pInstance->AddRef();
		}

		return refCnt;
	}

	template<typename T>
	void Safe_Delete(T& pPointer)
	{
		if (nullptr != pPointer)
		{
			delete pPointer;
			pPointer = nullptr;
		}
	}
}

#endif // !Engine_Function_h__
