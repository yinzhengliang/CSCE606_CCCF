/************************************************************************/
/* core模块的用户接口                                                                     */
/************************************************************************/

#ifndef	MV_CORE_X
#define	MV_CORE_X

#ifndef MV_ID
#define MV_ID void*
#endif//定义MV_ID

#if defined _MSC_VER || defined __BORLANDC__
typedef __int64 int64;
typedef unsigned __int64 uint64;
#else
typedef long long int64;
typedef unsigned long long uint64;
#endif	//_MSC_VER

#define MV_WIDTH		-1
#define MV_HEIGHT		-2
#define MV_DEPTH		-3
#define MV_CHANNELS	-4

extern "C"__declspec(dllexport) int64 mvGetTickCount();
extern "C"__declspec(dllexport) double mvGetTickFrequency();

extern "C"__declspec(dllexport) MV_ID mvCreateImage(int width,int height,int depth, int channels);//创建图像
extern "C"__declspec(dllexport) MV_ID mvCreateMat(int rows,int cols,int type);//创建矩阵
extern "C"__declspec(dllexport) void mvReleaseImage(MV_ID img);//释放图像
extern "C"__declspec(dllexport) void mvReleaseMat(MV_ID mat);//释放矩阵
extern "C"__declspec(dllexport) void mvSetImageROI(MV_ID img,int x,int y, int width, int height);//设置图像的ROI区域
extern "C"__declspec(dllexport) void mvReSetImageROI(MV_ID img);//释放图像的ROI
extern "C"__declspec(dllexport) MV_ID mvCloneImage(MV_ID src);//复制图像
extern "C"__declspec(dllexport) MV_ID mvCloneMat(MV_ID src);//复制矩阵
extern "C"__declspec(dllexport) void  mvCopyImage(MV_ID src,MV_ID dst);//将src图像的roi区域生成新图像
extern "C"__declspec(dllexport) bool  mvMatInvert(MV_ID src, MV_ID dst);//求矩阵转置
extern "C"__declspec(dllexport) void mvMatMultiply(MV_ID src1, MV_ID src2, MV_ID dst);//计算矩阵乘法
extern "C"__declspec(dllexport) void mvMatTranspose(MV_ID src,MV_ID dst);//计算矩阵的转置
extern "C"__declspec(dllexport) void mvImageZero(MV_ID src);//图像清零
extern "C"__declspec(dllexport) long mvImageInquire(MV_ID ImageBufId, long InquireType);

#endif