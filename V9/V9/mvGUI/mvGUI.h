/************************************************************************/
/* 显示及图像IO模块的用户文件                                                                     */
/************************************************************************/

#ifndef	MV_GUI_X
#define	MV_GUI_X

#ifndef MV_ID
#define MV_ID void*
#endif//定义MV_ID



extern "C"__declspec(dllexport) bool mvReadImageFile(MV_ID* image, const char * filename);
extern "C"__declspec(dllexport) bool mvWriteImageFile(MV_ID image, const char * filename);

extern "C"__declspec(dllexport) void mvCreateWindows( const char* name, int flags = 1 );
extern "C"__declspec(dllexport) void mvShowImage( const char* name, MV_ID image );
extern "C"__declspec(dllexport) void mvResizeWindow( const char* name, int width, int height );
extern "C"__declspec(dllexport) void mvMoveWindow( const char* name, int x, int y );
extern "C"__declspec(dllexport) void mvDestroyWindow( const char* name );
extern "C"__declspec(dllexport) void mvDestroyAllWindows(void);
extern "C"__declspec(dllexport) void mvDispSelectWindow( MV_ID image, HDC hDCDst, RECT* pDstRect, bool flag = false);
extern "C"__declspec(dllexport) int mvWaitKey( int delay =0 );


#endif
