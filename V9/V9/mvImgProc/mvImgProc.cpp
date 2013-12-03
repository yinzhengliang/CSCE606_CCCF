// mvImgProc.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#include "mvImgProc.h"
#include "filter.h"
#include "StructureAnalysis.h"
#include "threshold.h"
#include "imgProc.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

void mvBuildPyramid(MV_ID srcImage, MV_ID* dstImage, int maxlevel)
{
	BuildPyramid((MvImage*)srcImage,(MvImage**)dstImage,maxlevel);
}

void mvImBinarize(MV_ID srcImage, long Condition, double* thresholdValue)
{
	ImBinarize((MvImage*)srcImage, Condition,thresholdValue);
}

bool mvImErosion(MV_ID img)
{
	return Erosion((MvImage*) img);
}

bool mvImDilation(MV_ID img)
{
	return Dilation((MvImage*) img);
}

bool mvImOpening(MV_ID img)
{
	return Opening((MvImage*) img);
}

bool mvImClosing(MV_ID img)
{
	return Closing((MvImage*) img);
}

bool mvImAverageFilter(MV_ID img,int mode)
{
	return AverageFilter((MvImage*) img,mode);
}

bool mvImMedianFilter(MV_ID img,int mode)
{
	return MedianFilter((MvImage*) img,mode);
}


void mvImSobelEdge(MV_ID img,int threshhold,int mode)
{
	SobelEdge((MvImage*)img,threshhold,mode);
}

MV_ID mvImFourier(MV_ID ImageBufId)
{
	return ImFourier((MvImage*)ImageBufId);
}

bool mvImTranslate(MV_ID ImageBufId,double XDisplacement,double YDisplacement)
{
	return ImTranslate((MvImage*) ImageBufId,XDisplacement,YDisplacement);
}

bool mvImRotate(MV_ID  ImageBufId,double Angle,double CenX,double CenY)
{
	return ImRotate((MvImage*) ImageBufId,Angle,CenX,CenY);
}
