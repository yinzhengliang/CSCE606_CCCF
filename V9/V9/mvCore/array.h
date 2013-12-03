//////////////////////////////////////////////////////////////////////////////
//
// array.h -- 数据类型相关的内存分配释放等基本操作；
//
// Created on 2011.3.14
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _MV_ARRAY_
#define _MV_ARRAY_
#include "mvtypes.h"
#include "iostream"
MVAPI MvImage* CreateImageHeader(int width,int height,int depth, int channels);	//创建图像头
MVAPI void CreateImageData( MvImage* arr );										//分配图像数据
MVAPI MvImage* CreateImage(int width,int height,int depth, int channels);			//创建图像

MVAPI void mvZero(MvImage* src);                                                                //图像清零
MVAPI MvImage* CloneImage(MvImage* src);											//拷贝图像，包括图像头，数据和ROI
MVAPI void Copy(MvImage* srcImage,MvImage* dstImage);                             //对srcImage中设定的ROI区域复制到dstImage图像中

MVAPI MvROI* CreateROI(int coi, int xOffset, int yOffset, int width, int height);	//创建ROI
MVAPI void SetImageROI(MvImage* img,MvRect rect);									//设置图像的ROI
MVAPI void ReSetImageROI(MvImage* img);											//消除ROI，并释放ROI结构

MVAPI void ReleaseImageHeader(MvImage* img);										//释放图像头
MVAPI void ReleaseImageData(MvImage* img);										//释放图像数据
MVAPI void ReleaseImage(MvImage* img);											//释放图像

MVAPI MvMat* CreateMat(int rows,int cols,int type);								//创建矩阵
MVAPI MvMat* CreateMatHeader(int rows,int cols,int type);							//创建矩阵头
MVAPI void CreateMatData(MvMat* arr);											//分配矩阵数据内存

MVAPI MvMat* CloneMat(const MvMat* src);											//拷贝矩阵，包括头和数据

MVAPI void  ReleaseMatHeader(MvMat* mat);											//释放矩阵头
MVAPI void  ReleaseMatData(MvMat* mat);											//释放矩阵数据
MVAPI void  ReleaseMat(MvMat* mat);												//释放矩阵

MVAPI void MatTranspose(const MvMat* src,MvMat* dst);//矩阵转置

MVAPI void MatMultiply(const MvMat* src1,const MvMat* src2,MvMat* dst);//矩阵乘法

static inline int pivot(double** m,const int &n,const int &row);//矩阵求逆用到的
MVAPI bool MatInvert(const MvMat*src,MvMat* dst);//矩阵求逆

#endif