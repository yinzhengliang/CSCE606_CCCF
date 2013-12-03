/************************************************************************/
/* feature matching user documents                                                                     */
/************************************************************************/
#ifndef	MV_FEAT_X
#define	MV_FEAT_X

#ifndef MV_ID
#define MV_ID void*
#endif//define MV_ID

//interface parameters//
//#ifndef MV_DISABLE
//#define MV_DISABLE       -109
//#endif
//#ifndef MV_ENABLE 
//#define MV_ENABLE        -110
//#endif
//#ifndef MV_DEFAULT 
//#define MV_DEFAULT       -111   //default value
//#endif
//#ifndef MV_ALL
//#define MV_ALL           -122
// #endif
/************************************************************************/
/* feature matching choose                                                    */
/************************************************************************/
#define MV_FEATMATCH_EDGE -101    //GHT
#define MV_FEATMATCH_XX  -102   

/************************************************************************/
/* feature matching external parameter                                                   */
/************************************************************************/
//GHT related// 
#define MV_GRAYFACTOR      -103   //edge extraction factor
#define MV_TOPLEVEL_LENGTH -104   


/************************************************************************/
/* index angle related                                                        */
/************************************************************************/
//#define MV_ANGLE_MODE             -1041
//#define MV_SEARCH_ANGLE           -105       
//#define MV_SEARCH_ANGLE_MAX_NEG   -106       
//#define MV_SEARCH_ANGLE_MAX_POS   -107      
// #define MV_SEARCH_ANGLE_STEP      -108       


/************************************************************************/
/* image smooth degree                                                         */
/************************************************************************/
#define MV_SMOOTHNESS             -113  

/************************************************************************/
/* set the detail working accuracy                                                     */
/************************************************************************/
//define the control value
//#define MV_DETAIL_LEVEL           -117
//#define MV_VERY_HIGH              -118
//#define MV_HIGH                   -119
/*#define MV_MEDIUM                 -120*/

/************************************************************************/
/* set the matching number                                                         */
/************************************************************************/
#define MV_FEAT_NUMBERMODE         -121      
#define MV_FEAT_NUMBER             -122

/************************************************************************/
/* reference point                                                           */
/************************************************************************/
//#define MV_MODEL_X              -123
//#define MV_MODEL_Y              -124
//#define MV_MODELROI_X           -1241
// #define MV_MODELROI_Y           -1242
/************************************************************************/
/* set the region of matching positioning                                                   */
/************************************************************************/
//#define MV_TARGET_X             -125            
//#define MV_TARGET_Y             -126       
//#define MV_TARGETROI_X          -127 
// #define MV_TARGETROI_Y          -128

/************************************************************************/
/* result gaining related                                                         */
/************************************************************************/
//#define MV_RESULT_X                -129
//#define MV_RESULT_Y                -130
//#define MV_RESULT_ANGLE            -131
// #define MV_RESULT_SCORE            -132

extern "C"__declspec(dllexport) MV_ID mvFeatAllocParam(int FeatMethod);
extern "C"__declspec(dllexport) void mvSetFeatParam(int MvFeatParamType, double Value, MV_ID FeatParam);
extern "C"__declspec(dllexport) MV_ID mvFeatAllocModel(MV_ID TmpImage, MV_ID FeatParam);
extern "C"__declspec(dllexport) MV_ID mvFeatAllocResult(MV_ID FeatParam);
extern "C"__declspec(dllexport) void mvFeatPreprocess(MV_ID FeatModel,MV_ID FeatParam);
extern "C"__declspec(dllexport) bool mvFeatFind(MV_ID DstImage,MV_ID FeatModel,MV_ID FeatParam,MV_ID FeatResult);
extern "C"__declspec(dllexport) void mvFeatGetResult(MV_ID FeatResultId,int ResultType,double *UserArrayPtr);
extern "C"__declspec(dllexport) void mvFeatParamFree(MV_ID FeatParam);
extern "C"__declspec(dllexport) void mvFeatModelFree(MV_ID FeatModel,MV_ID FeatParam);
extern "C"__declspec(dllexport) void mvFeatResultFree(MV_ID FeatResult);
extern "C"__declspec(dllexport) void mvFeatModelSave(const char* FileName,MV_ID mimage,MV_ID featparam);
extern "C"__declspec(dllexport) void mvFeatModelLoad(const char* FileName,MV_ID mimage,MV_ID featparam);
extern "C"__declspec(dllexport) void mvFeatDrawModel(MV_ID model, MV_ID featparam,HDC hDCDst, RECT* pDstRect);
 
#endif