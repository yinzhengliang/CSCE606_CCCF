/************************************************************************/
/* claim of histogram related operations                                                                   */
/************************************************************************/
#ifndef _MV_IMGPROC_XX
#define _MV_IMGPROC_XX

#include "../mvCore/mvtypes.h"
#include "../mvCore/array.h"
#include "../mvCore/core.h"
#pragma comment(lib,"../mvCore/Debug/mvCore.lib")
#include "math.h"
#include "complex"
#ifndef PI
#define PI 3.1415926535898
#endif

static void FFT(complex<double> * TD, complex<double> * FD, int r);
MvImage* ImFourier(MvImage* ImageBufId);
bool ImTranslate(MvImage* ImageBufId,double XDisplacement,double YDisplacement);
bool ImRotate(MvImage* ImageBufId,double Angle,double CenX,double CenY);
#endif//_MV_IMGPROC_XX