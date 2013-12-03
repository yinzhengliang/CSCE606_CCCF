// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E9D3F307_4FF6_4F29_8A63_617B77EC066A__INCLUDED_)
#define AFX_STDAFX_H__E9D3F307_4FF6_4F29_8A63_617B77EC066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//header file for dynamic link libraries
#include "mv.h"
#include "../mvCore/mvCore.h"
#include "../mvGUI/mvGUI.h"
#include "../MvImgProc/mvImgProc.h"

#include "../MvFeatMatch/MvFeatMatch.h"
#include "../mvCore/mvtypes.h"

//calling dynamic link libraries 
#pragma comment(lib, "../MvFeatMatch/Debug/MvFeatMatch.lib")
#pragma comment(lib, "../mvImgProc/Debug/mvImgProc.lib")
#pragma comment(lib, "../mvGUI/Debug/mvGUI.lib")
#pragma comment(lib, "../mvCore/Debug/mvCore.lib")


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E9D3F307_4FF6_4F29_8A63_617B77EC066A__INCLUDED_)
