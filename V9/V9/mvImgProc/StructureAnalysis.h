/************************************************************************/
/* claim of structure analysis related operations                                                                */
/************************************************************************/
#ifndef	_MV_STRUCTURE_ANALYSIS_XX
#define	_MV_STRUCTURE_ANALYSIS_XX
#include "../mvCore/mvtypes.h"
#include "iostream"

#ifndef _MV_MATH_H
#define _MV_MATH_H
#include "math.h"
#endif //_MV_MATH_H

#ifndef PI
#define PI 3.1415926535898
#endif

extern "C"__declspec(dllexport) bool Normalize(MvImage* dstImage,MvImage* tmpImage,int offX,int offY,int width,int height,int filter,double* ccorr);


#endif//_MV_STRUCTURE_ANALYSIS_XX