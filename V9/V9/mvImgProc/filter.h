/************************************************************************/
/* claim of functions concerning filtering                                                                     */
/************************************************************************/
#ifndef _MV_FILTER_XX_
#define _MV_FILTER_XX_

#include "../mvCore/mvtypes.h"
#include "../mvCore/array.h"
#include "../mvCore/core.h"
#include "mvImgProc.h"
#pragma comment(lib,"../mvCore/Debug/mvCore.lib")

//for sobel
#include "math.h"

extern "C"__declspec(dllexport) void PyrDown(MvImage* srcImage,MvImage*& dstImage);
extern "C"__declspec(dllexport) void BuildPyramid(MvImage* srcImage, MvImage** dstImage, int maxlevel);
extern "C"__declspec(dllexport) void SobelEdge(MvImage * img,int threshhold,int mode);
extern "C"__declspec(dllexport) bool Erosion(MvImage * img);
extern "C"__declspec(dllexport) bool Dilation(MvImage * img);
extern "C"__declspec(dllexport) bool Opening(MvImage * img);
extern "C"__declspec(dllexport) bool Closing(MvImage * img);
extern "C"__declspec(dllexport) bool AverageFilter(MvImage * img,int mode);
extern "C"__declspec(dllexport) void ArrayOrder(uchar* array,int num);
extern "C"__declspec(dllexport) bool MedianFilter(MvImage * img,int mode);
#endif//_MV_FILTER_XX_