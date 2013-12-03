// #ifndef MV_FEAT_MATCH_XX
// #define MV_FEAT_MATCH_XX

#include "../mvCore/mvtypes.h"
#include "../mvCore/array.h"
#include "../mvCore/mvaux.h"
#include "../mvImgProc/filter.h"
#include "../mvGUI/imageWindow.h"
#include "featMatchtypes.h"


#include "../mvImgProc/StructureAnalysis.h"
#pragma comment(lib,"../mvCore/Debug/mvCore.lib")
#pragma comment(lib,"../mvGUI/Debug/mvGUI.lib")
#pragma comment(lib,"../mvImgProc/Debug/mvImgProc.lib")

#define MV_FEATMODEL void*
//Interface prototypes//
//allocate paremeter structure memory
extern "C"__declspec(dllexport) MvFeatParam* FeatAllocParam(int method);
//set the value of matching parameters 
extern "C"__declspec(dllexport) void SetFeatParam(int MvFeatType, double value, MvFeatParam* featparam);
//allocate module structure memory
extern "C"__declspec(dllexport) MV_FEATMODEL FeatAllocModel(MvImage* tmpImage, MvFeatParam* featparam);
//module image pretreatment and information extraction
extern "C"__declspec(dllexport) void FeatPreprocess(MV_FEATMODEL featmodel,MvFeatParam*);
//feature matching positioning
extern "C"__declspec(dllexport) bool FeatFind(MvImage* dstimage,MV_FEATMODEL featmodel,MvFeatParam* featparam,MvFeatResult* featresult);
//allocate result structure memory
extern "C"__declspec(dllexport) MvFeatResult* FeatAllocResult(MvFeatParam* featparam);
//extract information of result matching
extern "C"__declspec(dllexport) void FeatGetResult(MvFeatResult* FeatResultId,int ResultType,double *UserArrayPtr);
//release parameter structure memory
extern "C"__declspec(dllexport) void FeatParamFree(MvFeatParam* featparam);
//release module structure memory
extern "C"__declspec(dllexport) void FeatModelFree(MV_FEATMODEL featmodel,MvFeatParam *featparam);
//release result structure memory
extern "C"__declspec(dllexport) void FeatResultFree(MvFeatResult* featresult);
//storage feature matching module
extern "C"__declspec(dllexport) void FeatModelSave(const char* FileName,MvImage* mimage, MvFeatParam* featparam);
//write feature matching module
extern "C"__declspec(dllexport) void FeatWriteModel(FILE *FileHandle,MvImage* mimage, MvFeatParam* featparam);
//read feature matching module
extern "C"__declspec(dllexport) void FeatModelLoad(const char* FileName,MvImage** mimage,MvFeatParam** featparam);
//read feature mathicng module
extern "C"__declspec(dllexport) void FeatReadModel(FILE *FileHandle, MvImage** mimage, MvFeatParam** featparam);
//draw module
extern "C"__declspec(dllexport) void FeatDrawModel(MvImage* model, MvFeatParam* featparam,HDC hDCDst, RECT* pDstRect);


//GHTprototypes 
//Sobel edge extraction
bool GHTSobelEdge(MvImage * mimg,MvImage * simg,int threshold ,vector<edgepoint> *edgepoints,int mode);
//object image's edge extraction with Sobel in blurred and indistinct region
bool GHTSuImgEdgeExtract(MvImage *img, MvImage *emask, PreResult preresult, int threshold, vector<tedgepoint> *sedgepoints, 
						 int tilelength=1, int mode=0);
//image expansion and establish blurred region
bool GHTDilate(MvImage *simg,int n);
//单一分辨率层匹配
bool GHTLayerMatch(int row,int column, RTable *rtable_layer,vector<tedgepoint> *sepoints, PreResult& current_result,bool tile);
//module image pretreatment and extraction
bool SGHTPreProcessModel(GHTModel* ghtmodel,MvFeatParam* featparam);
//MFGHT matching
bool SGHTFindModel(MvImage* dstimage,GHTModel* featmodel,MvFeatParam* featparam,MvFeatResult* featresult);
//GHT matching
bool SSGHTFindModel(MvImage* m_image,GHTModel* featmodel,MvFeatParam* featparam,MvFeatResult* featresult);
//sub pixel simulation
bool SUBPIXMODIFIER3(int **pMatrix,int ai,int aj,int votex,int votey,double *x,double *y);
//***********//







