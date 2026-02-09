#ifndef Engine_Macro_h__
#define Engine_Macro_h__

namespace Engine
{
#ifndef MSGBOX
#define	MSG_BOX(_message)	MessageBox(NULL, TEXT(_message), L"System Message", MB_OK)
#endif // !MSGBOX

#define		BEGIN(NAME)		namespace NAME {
#define		END				}

#ifdef DLL_EXPORTS
#define MY_DLL	_declspec(dllexport)
#else
#define MY_DLL	_declspec(dllimport)
#endif
}

#endif // Engine_Macro_h__
