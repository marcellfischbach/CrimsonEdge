
#pragma once

#ifdef CS_WIN32

#pragma warning( disable : 4530)
#pragma warning( disable : 4577)




#ifdef CS_CORE_EXPORT
#define CS_CORE_API __declspec(dllexport)
#else
#define CS_CORE_API __declspec(dllimport)
#endif

#pragma warning( disable : 4251 )

#else

#define CS_CORE_API

#endif
