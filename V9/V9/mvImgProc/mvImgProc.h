/************************************************************************/
/* The user interfaces of image processing module                                                                */
/************************************************************************/

#ifndef	MV_IMAGEPROC_XXX_X
#define	MV_IMAGEPROC_XXX_X

#ifndef MV_ID
#define MV_ID void*
#endif//define MV_ID
#define MV_THIN -1
#define MV_THICK -2
#define MV_3X3 1
#define MV_5X5 2
#define MV_MANUAL 1
#define MV_ITERATE 2
#define MV_OSTU 3

extern "C"__declspec(dllexport) void mvImBinarize (MV_ID srcImage, long Condition, double* thresholdValue = NULL);//Image binarization
extern "C"__declspec(dllexport) bool mvImErosion(MV_ID img);//image binary errosion
extern "C"__declspec(dllexport) bool mvImDilation(MV_ID img);//image binary expansion
extern "C"__declspec(dllexport) bool mvImOpening(MV_ID img);//image binary opening operation
extern "C"__declspec(dllexport) bool mvImClosing(MV_ID img);//image binary closing operation
extern "C"__declspec(dllexport) bool mvImAverageFilter(MV_ID img,int mode);//image mean filter
extern "C"__declspec(dllexport) bool mvImMedianFilter(MV_ID img,int mode);//image median filter
extern "C"__declspec(dllexport) void mvImSobelEdge(MV_ID img,int threshhold,int mode);//sobel operator filter

extern "C"__declspec(dllexport) MV_ID mvImFourier(MV_ID ImageBufId);
extern "C"__declspec(dllexport) bool mvImTranslate(MV_ID ImageBufId,double XDisplacement,double YDisplacement);
extern "C"__declspec(dllexport) bool mvImRotate(MV_ID ImageBufId,double Angle,double CenX,double CenY);

#endif