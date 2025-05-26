#pragma once

#include <SDKDDKVer.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>


#ifdef DEBUG && !defined(DISTRIBUTION)
#define LOG_DEBUG_INFO_MSG(obj, msgFormat, ...) \
    obj->showMessage(xstring::Printf(msgFormat, __VA_ARGS__), wwgmtkMessageType_Info)
#else
#define LOG_DEBUG_MSG(obj, msgFormat, ...)
#endif

#ifdef DEBUG  && !defined(DISTRIBUTION)
#define LOG_DEBUG_ERROR_MSG(obj, msgFormat, ...) \
    obj->showMessage(xstring::Printf(msgFormat, __VA_ARGS__), wwgmtkMessageType_Error)
#else
#define LOG_DEBUG_ERROR_MSG(obj, msgFormat, ...)
#endif

#ifdef DEBUG  && !defined(DISTRIBUTION)
#define LOG_DEBUG_WARN_MSG(obj, msgFormat, ...) \
    obj->showMessage(xstring::Printf(msgFormat, __VA_ARGS__), wwgmtkMessageType_Warning)
#else
#define LOG_DEBUG_ERROR_MSG(obj, msgFormat, ...)
#endif