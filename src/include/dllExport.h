#ifndef __DLL_EXPORT_H__
#define __DLL_EXPORT_H__

#ifdef EMU_TARGET
    #define DLLEXPORT __declspec(dllexport)
#elif MCU_TARGET
    #define DLLEXPORT
#else
    #define DLLEXPORT __declspec(dllimport)
#endif

#endif