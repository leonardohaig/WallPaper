
// WallPaper.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWallPaperApp:
// �йش����ʵ�֣������ WallPaper.cpp
//

class CWallPaperApp : public CWinApp
{
public:
	CWallPaperApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWallPaperApp theApp;