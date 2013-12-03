//////////////////////////////////////////////////////////////////////////////
//
// threshold.h 
//
// Created on 2011.4.19
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _THRESHOLD_
#define _THRESHOLD_

#include "../mvCore/mvtypes.h"
#include "../mvCore/array.h"
#include "mvImgProc.h"
#pragma comment(lib,"../mvCore/Debug/mvCore.lib")

extern "C"__declspec(dllexport) void ImBinarize (MvImage*  pSrcImageBufId, long Condition, double* thresholdValue = NULL);



#endif

