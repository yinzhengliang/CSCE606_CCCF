//////////////////////////////////////////////////////////////////////////////
//
// array.h -- ����������ص��ڴ�����ͷŵȻ���������
//
// Created on 2011.3.14
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _MV_ARRAY_
#define _MV_ARRAY_
#include "mvtypes.h"
#include "iostream"
MVAPI MvImage* CreateImageHeader(int width,int height,int depth, int channels);	//����ͼ��ͷ
MVAPI void CreateImageData( MvImage* arr );										//����ͼ������
MVAPI MvImage* CreateImage(int width,int height,int depth, int channels);			//����ͼ��

MVAPI void mvZero(MvImage* src);                                                                //ͼ������
MVAPI MvImage* CloneImage(MvImage* src);											//����ͼ�񣬰���ͼ��ͷ�����ݺ�ROI
MVAPI void Copy(MvImage* srcImage,MvImage* dstImage);                             //��srcImage���趨��ROI�����Ƶ�dstImageͼ����

MVAPI MvROI* CreateROI(int coi, int xOffset, int yOffset, int width, int height);	//����ROI
MVAPI void SetImageROI(MvImage* img,MvRect rect);									//����ͼ���ROI
MVAPI void ReSetImageROI(MvImage* img);											//����ROI�����ͷ�ROI�ṹ

MVAPI void ReleaseImageHeader(MvImage* img);										//�ͷ�ͼ��ͷ
MVAPI void ReleaseImageData(MvImage* img);										//�ͷ�ͼ������
MVAPI void ReleaseImage(MvImage* img);											//�ͷ�ͼ��

MVAPI MvMat* CreateMat(int rows,int cols,int type);								//��������
MVAPI MvMat* CreateMatHeader(int rows,int cols,int type);							//��������ͷ
MVAPI void CreateMatData(MvMat* arr);											//������������ڴ�

MVAPI MvMat* CloneMat(const MvMat* src);											//�������󣬰���ͷ������

MVAPI void  ReleaseMatHeader(MvMat* mat);											//�ͷž���ͷ
MVAPI void  ReleaseMatData(MvMat* mat);											//�ͷž�������
MVAPI void  ReleaseMat(MvMat* mat);												//�ͷž���

MVAPI void MatTranspose(const MvMat* src,MvMat* dst);//����ת��

MVAPI void MatMultiply(const MvMat* src1,const MvMat* src2,MvMat* dst);//����˷�

static inline int pivot(double** m,const int &n,const int &row);//���������õ���
MVAPI bool MatInvert(const MvMat*src,MvMat* dst);//��������

#endif