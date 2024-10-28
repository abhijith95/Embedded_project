#ifndef __DLL_EXPORT_H__
#define __DLL_EXPORT_H__

#ifdef EMU_TARGET
    #define DLLEXPORT __declspec(dllexport)
#else
    #define DLLEXPORT
#endif

#endif