
// WallPaperDlg.h : ͷ�ļ�
//

#pragma once
#include "Markup.h"
#include <vector>

// CWallPaperDlg �Ի���
class CWallPaperDlg : public CDialogEx
{
// ����
public:
	CWallPaperDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WALLPAPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	HRESULT SetDesktopWallpaper(CString pszFile, WallpaperStyle style);

	CString getPicPath();

	int getTimeInternal();

private:
	std::vector <CString> m_PicVec;
	int m_picIndex;

private:
	void TraverseDir(CString &dir,std::vector <CString >&vec);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
