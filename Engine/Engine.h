#pragma once

#ifdef ENGINE_EXPORTS
	#define ENGINE_API __declspec(dllexport)
#else 
	#define ENGINE_API __declspec(dllimport)
#endif

// export a function
extern "C" ENGINE_API void InitializeEngine();