/************************************************************************/
/* coreģ����û��ӿ�                                                                     */
/************************************************************************/

#ifndef	MV_CORE_X
#define	MV_CORE_X

#ifndef MV_ID
#define MV_ID void*
#endif//����MV_ID

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

extern "C"__declspec(dllexport) MV_ID mvCreateImage(int width,int height,int depth, int channels);//����ͼ��
extern "C"__declspec(dllexport) MV_ID mvCreateMat(int rows,int cols,int type);//��������
extern "C"__declspec(dllexport) void mvReleaseImage(MV_ID img);//�ͷ�ͼ��
extern "C"__declspec(dllexport) void mvReleaseMat(MV_ID mat);//�ͷž���
extern "C"__declspec(dllexport) void mvSetImageROI(MV_ID img,int x,int y, int width, int height);//����ͼ���ROI����
extern "C"__declspec(dllexport) void mvReSetImageROI(MV_ID img);//�ͷ�ͼ���ROI
extern "C"__declspec(dllexport) MV_ID mvCloneImage(MV_ID src);//����ͼ��
extern "C"__declspec(dllexport) MV_ID mvCloneMat(MV_ID src);//���ƾ���
extern "C"__declspec(dllexport) void  mvCopyImage(MV_ID src,MV_ID dst);//��srcͼ���roi����������ͼ��
extern "C"__declspec(dllexport) bool  mvMatInvert(MV_ID src, MV_ID dst);//�����ת��
extern "C"__declspec(dllexport) void mvMatMultiply(MV_ID src1, MV_ID src2, MV_ID dst);//�������˷�
extern "C"__declspec(dllexport) void mvMatTranspose(MV_ID src,MV_ID dst);//��������ת��
extern "C"__declspec(dllexport) void mvImageZero(MV_ID src);//ͼ������
extern "C"__declspec(dllexport) long mvImageInquire(MV_ID ImageBufId, long InquireType);

#endif