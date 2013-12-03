//////////////////////////////////////////////////////////////////////////////
//
// mvtypes.h -- 图像，矩阵，点等所有数据类型定义等
//
// Created on 2011.3.14
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _MV_TYPES_
#define _MV_TYPES_

#include <malloc.h>

#ifdef MVCORE_EXPORTS
#define MV_DLL_EXP __declspec(dllexport)
#else
#define MV_DLL_EXP
#endif	//MVCORE_EXPORTS

#ifdef __cplusplus
#define MVAPI extern "C" MV_DLL_EXP
#else
#define MVAPI MV_DLL_EXP
#endif	//__cplusplus

#ifndef MV_INLINE
#if defined __cplusplus
#define MV_INLINE inline
#elif (defined WIN32 || defined WIN64) && !defined __GNUC__
#define MV_INLINE __inline
#else
#define MV_INLINE static
#endif
#endif /* MV_INLINE */


#ifndef NULL
#define NULL 0
#endif

#define MV_ID void*

//Base types redefinition
typedef double REAL;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;
#ifndef __cplusplus
typedef enum {false, true} bool;
#endif



/************************************************************************/
/* MVstatus                                                                     */
/************************************************************************/
typedef int CVStatus;

enum {    
		MV_StsOk=                       0,  /* everithing is ok                */
		// CV_StsBackTrace=               -1,  /* pseudo error for back trace     */
		MV_StsError=                   -2,  /* unknown /unspecified error      */
		MV_StsInternal=                -3,  /* internal error (bad state)      */
		MV_StsNoMem=                   -4,  /* insufficient memory             */
		MV_StsBadArg=                  -5,  /* function arg/param is bad       */
		MV_StsBadFunc=                 -6,  /* unsupported function            */
		MV_StsNoConv=                  -7,  /* iter. didn't converge           */
		MV_StsAutoTrace=               -8,  /* tracing                         */
		//  CV_HeaderIsNull=               -9,  /* image header is NULL            */
		//  CV_BadImageSize=              -10, /* image size is invalid           */
		//  CV_BadOffset=                 -11, /* offset is invalid               */
		//  CV_BadDataPtr=                -12, /**/
		//  CV_BadStep=                   -13, /**/
		//  CV_BadModelOrChSeq=           -14, /**/
		//  CV_BadNumChannels=            -15, /**/
		//  CV_BadNumChannel1U=           -16, /**/
		//  CV_BadDepth=                  -17, /**/
		//  CV_BadAlphaChannel=           -18, /**/
		//  CV_BadOrder=                  -19, /**/
		//  CV_BadOrigin=                 -20, /**/
		//  CV_BadAlign=                  -21, /**/
		//  CV_BadCallBack=               -22, /**/
		//  CV_BadTileSize=               -23, /**/
		//  CV_BadCOI=                    -24, /**/
		//  CV_BadROISize=                -25, /**/
		//  CV_MaskIsTiled=               -26, /**/
		//  CV_StsNullPtr=                -27, /* null pointer */
		//  CV_StsVecLengthErr=           -28, /* incorrect vector length */
		//  CV_StsFilterStructContentErr= -29, /* incorr. filter structure content */
		//  CV_StsKernelStructContentErr= -30, /* incorr. transform kernel content */
		//  CV_StsFilterOffsetErr=        -31, /* incorrect filter ofset value */
		// CV_StsBadSize=                -201, /* the input/output structure size is incorrect  */
		// CV_StsDivByZero=              -202, /* division by zero */
		// CV_StsInplaceNotSupported=    -203, /* in-place operation is not supported */
		// CV_StsObjectNotFound=         -204, /* request can't be completed */
		// CV_StsUnmatchedFormats=       -205, /* formats of input/output arrays differ */
		// CV_StsBadFlag=                -206, /* flag is wrong or not supported */  
		// CV_StsBadPoint=               -207, /* bad CvPoint */ 
		// CV_StsBadMask=                -208, /* bad format of mask (neither 8uC1 nor 8sC1)*/
		// CV_StsUnmatchedSizes=         -209, /* sizes of input/output structures do not match */
		// CV_StsUnsupportedFormat=      -210, /* the data format/type is not supported by the function*/
		// CV_StsOutOfRange=             -211, /* some of parameters are out of range */
		// CV_StsParseError=             -212, /* invalid syntax/structure of the parsed file */
		//CV_StsNotImplemented=         -213, /* the requested function/feature is not implemented */
		// CV_StsBadMemBlock=            -214, /* an allocated block has been corrupted */
		MV_StsAssert=                 -215, /* assertion failed */    
		// CV_GpuNotSupported=           -216,  
		// CV_GpuApiCallError=           -217, 
		// CV_GpuNppCallError=           -218  
};
/******************************* MVPoint and variants ***********************************/

typedef struct MvPoint
{
    int x;
    int y;
}MvPoint;


MV_INLINE  MvPoint  mvPoint( int x, int y )
{
    MvPoint p;

    p.x = x;
    p.y = y;

    return p;
}


typedef struct MvPoint2D32f
{
    float x;
    float y;
}
MvPoint2D32f;


MV_INLINE  MvPoint2D32f  mvPoint2D32f( double x, double y )
{
    MvPoint2D32f p;

    p.x = (float)x;
    p.y = (float)y;

    return p;
}


MV_INLINE  MvPoint2D32f  mvPointTo32f( MvPoint point )
{
    return mvPoint2D32f( (float)point.x, (float)point.y );
}


// MV_INLINE  MvPoint  mvPointFrom32f( MvPoint2D32f point )
// {
//     MvPoint ipt;
//     ipt.x = mvRound(point.x);
//     ipt.y = mvRound(point.y);
// 
//     return ipt;
// }


typedef struct MvPoint3D32f
{
    float x;
    float y;
    float z;
}
MvPoint3D32f;


MV_INLINE  MvPoint3D32f  mvPoint3D32f( double x, double y, double z )
{
    MvPoint3D32f p;

    p.x = (float)x;
    p.y = (float)y;
    p.z = (float)z;

    return p;
}


typedef struct MvPoint2D64f
{
    double x;
    double y;
}
MvPoint2D64f;


MV_INLINE  MvPoint2D64f  mvPoint2D64f( double x, double y )
{
    MvPoint2D64f p;

    p.x = x;
    p.y = y;

    return p;
}


typedef struct MvPoint3D64f
{
    double x;
    double y;
    double z;
}
MvPoint3D64f;


MV_INLINE  MvPoint3D64f  mvPoint3D64f( double x, double y, double z )
{
    MvPoint3D64f p;

    p.x = x;
    p.y = y;
    p.z = z;

    return p;
}

/************************************* MvComplex *****************************************/
typedef struct MvComplex  //20110322
{	
	double real;
	double imag;
}MvComplex;                             //复数类型




/*************************************** MvRect *****************************************/

typedef struct MvRect
{
    int x;
    int y;
    int width;
    int height;
}
MvRect;

MV_INLINE  MvRect  mvRect( int x, int y, int width, int height )
{
    MvRect r;
	
    r.x = x;
    r.y = y;
    r.width = width;
    r.height = height;
	
    return r;
}


// MV_INLINE  IplROI  MvRectToROI( MvRect rect, int coi )
// {
//     IplROI roi;
//     roi.xOffset = rect.x;
//     roi.yOffset = rect.y;
//     roi.width = rect.width;
//     roi.height = rect.height;
//     roi.coi = coi;
// 	
//     return roi;
// }
// 
// 
// MV_INLINE  MvRect  MvROIToRect( IplROI roi )
// {
//     return MvRect( roi.xOffset, roi.yOffset, roi.width, roi.height );
// }

/******************************** MvSize's & MvBox **************************************/

typedef struct
{
    int width;
    int height;
}
MvSize;

MV_INLINE  MvSize  mvSize( int width, int height )
{
    MvSize s;

    s.width = width;
    s.height = height;

    return s;
}

typedef struct MvSize2D32f
{
    float width;
    float height;
}
MvSize2D32f;


MV_INLINE  MvSize2D32f  mvSize2D32f( double width, double height )
{
    MvSize2D32f s;

    s.width = (float)width;
    s.height = (float)height;

    return s;
}

typedef struct MvBox2D
{
    MvPoint2D32f center;  /* center of the box */
    MvSize2D32f  size;    /* box width and length */
    float angle;          /* angle between the horizontal axis
                             and the first side (i.e. length) in degrees */
}
MvBox2D;

/************************************* MvScalar *****************************************/

typedef struct MvScalar
{
    double val[4];
}
MvScalar;

MV_INLINE  MvScalar  mvScalar( double val0, double val1=0,
							  double val2=0, double val3=0)
{
    MvScalar scalar;
    scalar.val[0] = val0; scalar.val[1] = val1;
    scalar.val[2] = val2; scalar.val[3] = val3;
    return scalar;
}


MV_INLINE  MvScalar  mvRealScalar( double val0 )
{
    MvScalar scalar;
    scalar.val[0] = val0;
    scalar.val[1] = scalar.val[2] = scalar.val[3] = 0;
    return scalar;
}

MV_INLINE  MvScalar  mvScalarAll( double val0123 )
{
    MvScalar scalar;
    scalar.val[0] = val0123;
    scalar.val[1] = val0123;
    scalar.val[2] = val0123;
    scalar.val[3] = val0123;
    return scalar;
}


/****************************************************************************************\
*                                  Image type (IplImage)                                 *
\****************************************************************************************/
#define MV_DEPTH_SIGN 0x80000000

typedef struct MvImage
{
    int	 nSize;			/* sizeof(MvImage) */
	int  nChannels;     /* 1,2,3 or 4 channels */
    int  depth;         /* pixel depth in bits*/
    int  width;         /* image width in pixels */
    int  height;        /* image height in pixels */
    int  widthStep;		/* size of aligned image row in bytes */
    struct MvROI *roi;/* image ROI. if NULL, the whole image is selected */
    uchar* imageData;  /* pointer to aligned image data */
}
MvImage;

typedef struct MvROI
{
    int  coi; /* 0 - no COI (all channels are selected), 1 - 0th channel is selected ...*/
    int  xOffset;
    int  yOffset;
    int  width;
    int  height;
}
MvROI;

#define MV_IS_IMAGE_HDR(img) \
((img) != NULL && ((const MvImage*)(img))->nSize == sizeof(MvImage))

#define MV_IS_IMAGE(img) \
    (MV_IS_IMAGE_HDR(img) && ((MvImage*)img)->imageData != NULL)

/* get reference to pixel at (col,row)*/ 
#define MV_IMAGE_ELEM( image, elemtype, row, col,channel )       \
    (((elemtype*)((image)->imageData + (image)->widthStep*(row)))[(col)*(channel)])

/****************************************************************************************\
*                                  Matrix type (MvMat)                                   *
\****************************************************************************************/
// #define MV_CN_SHIFT   3
// #define MV_CN_MAX     512
// #define MV_CN_SHIFT   3
// #define MV_DEPTH_MAX  (1 << MV_CN_SHIFT)


#define MV_8S   1
#define MV_16U  2
#define MV_16S  3
#define MV_32S  4
#define MV_32F  5

#ifndef MV_8U
#define MV_8U   0
#endif

#ifndef MV_64F
#define MV_64F  6
#endif
// #define MV_MAKETYPE(depth,cn) ((depth) + (((cn)-1) << MV_CN_SHIFT))    
// #define MV_MAKE_TYPE MV_MAKETYPE
// 
// #define MV_8UC1 MV_MAKETYPE(MV_8U,1)
// #define MV_8UC2 MV_MAKETYPE(MV_8U,2)
// #define MV_8UC3 MV_MAKETYPE(MV_8U,3)
// #define MV_8UC4 MV_MAKETYPE(MV_8U,4)
// #define MV_8UC(n) MV_MAKETYPE(MV_8U,(n))
// 
// #define MV_8SC1 MV_MAKETYPE(MV_8S,1)
// #define MV_8SC2 MV_MAKETYPE(MV_8S,2)
// #define MV_8SC3 MV_MAKETYPE(MV_8S,3)
// #define MV_8SC4 MV_MAKETYPE(MV_8S,4)
// #define MV_8SC(n) MV_MAKETYPE(MV_8S,(n))
// 
// #define MV_16UC1 MV_MAKETYPE(MV_16U,1)
// #define MV_16UC2 MV_MAKETYPE(MV_16U,2)
// #define MV_16UC3 MV_MAKETYPE(MV_16U,3)
// #define MV_16UC4 MV_MAKETYPE(MV_16U,4)
// #define MV_16UC(n) MV_MAKETYPE(MV_16U,(n))
// 
// #define MV_16SC1 MV_MAKETYPE(MV_16S,1)
// #define MV_16SC2 MV_MAKETYPE(MV_16S,2)
// #define MV_16SC3 MV_MAKETYPE(MV_16S,3)
// #define MV_16SC4 MV_MAKETYPE(MV_16S,4)
// #define MV_16SC(n) MV_MAKETYPE(MV_16S,(n))
// 
// #define MV_32SC1 MV_MAKETYPE(MV_32S,1)
// #define MV_32SC2 MV_MAKETYPE(MV_32S,2)
// #define MV_32SC3 MV_MAKETYPE(MV_32S,3)
// #define MV_32SC4 MV_MAKETYPE(MV_32S,4)
// #define MV_32SC(n) MV_MAKETYPE(MV_32S,(n))
// 
// #define MV_32FC1 MV_MAKETYPE(MV_32F,1)
// #define MV_32FC2 MV_MAKETYPE(MV_32F,2)
// #define MV_32FC3 MV_MAKETYPE(MV_32F,3)
// #define MV_32FC4 MV_MAKETYPE(MV_32F,4)
// #define MV_32FC(n) MV_MAKETYPE(MV_32F,(n))
// 
// #define MV_64FC1 MV_MAKETYPE(MV_64F,1)
// #define MV_64FC2 MV_MAKETYPE(MV_64F,2)
// #define MV_64FC3 MV_MAKETYPE(MV_64F,3)
// #define MV_64FC4 MV_MAKETYPE(MV_64F,4)
// #define MV_64FC(n) MV_MAKETYPE(MV_64F,(n))
// 
// 
// #define MV_MAGIC_MASK       0xFFFF0000
// #define MV_MAT_MAGIC_VAL    0x42420000

typedef struct MvMat
{
    int type;                //各种预定义类型MV_<bit_depth>(S|U|F)C<number_of_channerls>
    int step;				//字节表示的行数据长度	
	int rows;
    int cols;
    union
    {
        uchar* ptr;
        short* s;
        int* i;
        float* fl;
        double* db;
    } data;						//指向数据的指针	

}MvMat;

// #define MV_IS_MAT_HDR(mat) \
//     ((mat) != NULL && \
//     (((const MvMat*)(mat))->type & MV_MAGIC_MASK) == MV_MAT_MAGIC_VAL && \
//     ((const MvMat*)(mat))->cols > 0 && ((const MvMat*)(mat))->rows > 0)
#define MV_IS_MAT_HDR(mat) \
    ((mat) != NULL && \
    (((const MvMat*)(mat))->type <=6 && \
    ((const MvMat*)(mat))->cols > 0 && ((const MvMat*)(mat))->rows > 0)

#define MV_IS_MAT(mat) \
    (MV_IS_MAT_HDR(mat) && ((const MvMat*)(mat))->data.ptr != NULL)


#define MV_MAT_ELEM_PTR( mat, row, col, pix_size )  \
    ((mat).data.ptr + (size_t)(mat).step*(row) + (pix_size)*(col))

#define MV_MAT_ELEM( mat, elemtype, row, col )           \
    (*(elemtype*)MV_MAT_ELEM_PTR( mat, row, col, sizeof(elemtype)))



/************************************* MvMoment *****************************************/
typedef struct MvZnkMomentData //20110322
{
	int n;           				//阶数
	int m;						//重数
	int x;		    				//x坐标值
	int y;						//y坐标值
	double r;        				//半径
	double theta;					//角度
	double RadPoly;	//径向多项式的值
	double cosMThetaR;  			//cos(m*theta)*R
	double sinMThetaR;  			//sin(m*theta)*R
	bool mask;        			//是否在单位圆内的标记
}MvZnkMomentData;              //Zernike矩径向多项式的计算相关的信息结构体

#endif	//_MV_TYPES_