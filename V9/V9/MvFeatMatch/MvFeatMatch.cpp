// MvFeatMatch.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include "FeatMatch.h"
#include "../demo/mv.h"
#include "MvFeatMatch.h"

/***************************************************************/
//function name£ºmvAllocFeatParam
//input: matching method
//output: external parameter structure pointers
//function: allocate external matching parameter, set default value 
//Created on 2013.10.16 by Yang Song
/***************************************************************/
MV_ID mvFeatAllocParam(int FeatMethod)
{
     return (MV_ID)FeatAllocParam(FeatMethod);
}

/***************************************************************/
//function name: mvSetFeatParam
//input: set the parameter type, value
//input: NULL
//function: choose different parameter based on different methods
//Created on 2013.10.15 by Yang Song
/***************************************************************/
void mvSetFeatParam(int MvFeatType, double Value, MV_ID FeatParam)
{
	 SetFeatParam(MvFeatType, Value, (MvFeatParam*)FeatParam);
}

/***************************************************************/
//function name: mvFeatAllocModel
//input: module image, external parameter pointers
//output: module structure pointers
//function: allocate module space based on different methods
//Created on 2013.10.22 by Xiang Chen
/***************************************************************/
MV_ID mvFeatAllocModel(MV_ID TmpImage, MV_ID FeatParam)
{
     return FeatAllocModel((MvImage*)TmpImage, (MvFeatParam*) FeatParam);
}

/***************************************************************/
//function name: mvFeatPreprocess
//input: module image, external parameter pointers
//output: module structure pointers
//function: pre-treat module based on different methods
//Created on 2013.10.22 by Xiang Chen
/***************************************************************/
void mvFeatPreprocess(MV_ID FeatModel,MV_ID FeatParam)
{
     FeatPreprocess(FeatModel,(MvFeatParam*) FeatParam);
}

/***************************************************************/
//function name: mvFeatFind
//input: object image, module structure pointers, external structure pointers, result structure pointers
//output: NULL
//function: do match based on different methods
//Created on 2013.10.22 by Xiang Chen
/***************************************************************/
bool mvFeatFind(MV_ID DstImage,MV_ID FeatModel,MV_ID FeatParam,MV_ID FeatResult)
{
	return FeatFind((MvImage *)DstImage,FeatModel,(MvFeatParam*) FeatParam, (MvFeatResult*) FeatResult); //
}

/***************************************************************/
//function name: MvFeatAllocResult
//input: external parameter structure pointers 
//output: matching result structure pointers
//function: allocate result structure based on different requirements
//Created on 2013.10.23 by Xiang Chen
/***************************************************************/
MV_ID mvFeatAllocResult(MV_ID FeatParam)
{
    return(MvFeatResult*) FeatAllocResult((MvFeatParam*) FeatParam);
}

/***************************************************************/
//function name: mvFeatGetResult
//input:  result structure, result type, single type result array
//output:  NULL
//function:  get all the result of single type matching
//Created on 2013.10.21 by Yang Song
/***************************************************************/
void mvFeatGetResult(MV_ID FeatResultId,int ResultType,double *UserArrayPtr)
{
    FeatGetResult((MvFeatResult*) FeatResultId,ResultType,UserArrayPtr);
}

/***************************************************************/
//function name: mvFeatParamFree
//input:  parameter structure pointers
//output:  NULL
//function:  release the memory of the parameter space
//Created on 2013.10.21 by Yang Song
/***************************************************************/
void mvFeatParamFree(MV_ID FeatParam)
{
    FeatParamFree((MvFeatParam*) FeatParam);
}

/***************************************************************/
//function name: mvFeatModelFree
//input:  module pointer
//output:  NULL
//function:  release memory of module 
//Created on 2013.10.22 by Yang Song
/***************************************************************/
void mvFeatModelFree(MV_ID FeatModel,MV_ID FeatParam)
{
    FeatModelFree(FeatModel,(MvFeatParam*)FeatParam);
}

/***************************************************************/
//function name: mvFeatResultFree
//input:  result structure pointers
//output:  NULL
//function:  release the memory of result
//Created on 2013.10.22 by Xiang Chen
/***************************************************************/
void mvFeatResultFree(MV_ID FeatResult)
{
    FeatResultFree((MvFeatResult*) FeatResult);
}

/***************************************************************/
//function name: mvFeatModelSave
//input:  
//output:  NULL
//function: storage of image information
/***************************************************************/
void mvFeatModelSave(const char* FileName,MV_ID mimage,MV_ID featparam)
{
    FeatModelSave(FileName, (MvImage*)mimage, (MvFeatParam*)featparam);
}

/***************************************************************/
//function name: mvFeatWriteModel
//input:  
//output:  NULL
//function: storage of image information
/***************************************************************/
void mvFeatModelLoad(const char* FileName,MV_ID mimage,MV_ID featparam)
{
    FeatModelLoad(FileName,(MvImage**)mimage,(MvFeatParam**)featparam);
}

/***************************************************************/
//function name: mvFeatDrawModel
//input:  
//output:  NULL
//function: storage of image information
/***************************************************************/
void mvFeatDrawModel(MV_ID model, MV_ID featparam,HDC hDCDst, RECT* pDstRect)
{
    FeatDrawModel((MvImage*)model, (MvFeatParam*)featparam, hDCDst,pDstRect);
}