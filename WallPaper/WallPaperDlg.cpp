
// WallPaperDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WallPaper.h"
#include "WallPaperDlg.h"
#include "afxdialogex.h"

#include "GlobalFun.h"

#include<shlobj.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWallPaperDlg 对话框




CWallPaperDlg::CWallPaperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWallPaperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_PicVec.clear();
	m_picIndex = 0;
}

void CWallPaperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWallPaperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CWallPaperDlg::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CWallPaperDlg 消息处理程序

BOOL CWallPaperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CString szFile = "C:\\win7\\DeskTop13.jpg";
	szFile = getPicPath();
	SetDesktopWallpaper(szFile,Tile);

	CString strFoldername = "C:\\Users\\liheng16\\Desktop\\WallPaper\\Debug\\PicRes\\desk7132";
	TraverseDir(strFoldername,m_PicVec);

	int nTimeInternal = getTimeInternal();
	
	SetTimer(0,nTimeInternal*1000,NULL);

	//ShowWindow(SW_HIDE);
	//OnCancel();

	/*WINDOWPLACEMENT wp;
	wp.length=sizeof(WINDOWPLACEMENT);
	wp.flags=WPF_RESTORETOMAXIMIZED;
	wp.showCmd=SW_HIDE;
	SetWindowPlacement(&wp);
	*/

	//隐藏界面
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN);
	  int nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	  SetWindowPos(NULL, nFullWidth, nFullHeight, 0, 0, SWP_NOZORDER);  //设置0像素,移到最角落  或者:MoveWindow(0,0,0,0);
	  ShowWindow(SW_HIDE);
	  ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);  //移除任务栏图标显示

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWallPaperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWallPaperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWallPaperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWallPaperDlg::OnBnClickedOk()
{
	autostart("WallPaper");
	
	CDialogEx::OnOK();
}

//
//   FUNCTION: SetDesktopWallpaper(PCWSTR, WallpaperStyle)
//
//   PURPOSE: Set the desktop wallpaper.
//
//   PARAMETERS: 
//   * pszFile - Path of the wallpaper
//   * style - Wallpaper style
//
HRESULT CWallPaperDlg::SetDesktopWallpaper(CString pszFile, WallpaperStyle style)
{
    HRESULT hr = S_OK;
 
	//设置壁纸风格和展开方式
	//在Control Panel\Desktop中的两个键值将被设置
    // TileWallpaper
    //  0: 图片不被平铺 
    //  1: 被平铺 
    // WallpaperStyle
    //  0:  0表示图片居中，1表示平铺
    //  2:  拉伸填充整个屏幕
    //  6:  拉伸适应屏幕并保持高度比
    //  10: 图片被调整大小裁剪适应屏幕保持纵横比

	//以可读可写的方式打开HKCU\Control Panel\Desktop注册表项
    HKEY hKey = NULL;
    hr = HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_CURRENT_USER, 
        "Control Panel\\Desktop", 0, KEY_READ | KEY_WRITE, &hKey));
    if (SUCCEEDED(hr))
    {
        LPCSTR pszWallpaperStyle;
        LPCSTR pszTileWallpaper;// PWSTR pszTileWallpaper;

        switch (style)
        {
        case Tile:
            pszWallpaperStyle = "0";
            pszTileWallpaper = "1";
            break;

        case Center:
            pszWallpaperStyle = "0";
            pszTileWallpaper = "0";
            break;

        case Stretch:
            pszWallpaperStyle = "2";
            pszTileWallpaper = "0";
            break;

        case Fit: // (Windows 7 and later)
            pszWallpaperStyle = "6";
            pszTileWallpaper = "0";
            break;

        case Fill: // (Windows 7 and later)
            pszWallpaperStyle = "10";
            pszTileWallpaper = "0";
            break;
        }
        // 设置 WallpaperStyle 和 TileWallpaper 到注册表项.
        DWORD cbData = lstrlen(pszWallpaperStyle) * sizeof(*pszWallpaperStyle);
        hr = HRESULT_FROM_WIN32(RegSetValueEx(hKey, "WallpaperStyle", 0, REG_SZ, 
            reinterpret_cast<const BYTE *>(pszWallpaperStyle), cbData));
        if (SUCCEEDED(hr))
        {
            cbData = lstrlen(pszTileWallpaper) * sizeof(*pszTileWallpaper);
            hr = HRESULT_FROM_WIN32(RegSetValueEx(hKey, "TileWallpaper", 0, REG_SZ, 
                reinterpret_cast<const BYTE *>(pszTileWallpaper), cbData));
        }

        RegCloseKey(hKey);
    }

	//通过调用Win32 API函数SystemParametersInfo 设置桌面壁纸
	/************************************************
	之前我们已经设置了壁纸的类型，但是壁纸图片的实际文件路径还没
	设置。SystemParametersInfo 这个函数位于user32.dll中，它支持
	我们从系统中获得硬件和配置信息。它有四个参数，第一个指明调用这
	个函数所要执行的操作，接下来的两个参数指明将要设置的数据，依据
	第一个参数的设定。最后一个允许指定改变是否被保存。这里第一个参数
	我们应指定SPI_SETDESKWALLPAPER，指明我们是要设置壁纸。接下来是
	文件路径。在Vista之前必须是一个.bmp的文件。Vista和更高级的系统
	支持.jpg格式
	*************************************************/
	//SPI_SETDESKWALLPAPER参数使得壁纸改变保存并持续可见。
    if (SUCCEEDED(hr))
    {
		 //SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, "C:/win7/DeskTop13.jpg", SPIF_SENDCHANGE);//路径使用的是/ 

        if (!SystemParametersInfo(SPI_SETDESKWALLPAPER, 0,  (LPVOID)(LPCTSTR)(pszFile), SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE))
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
        }
    }

    return hr;
}

CString CWallPaperDlg::getPicPath()
{
	CString strXMLPath = GetExePath()+ _T("\\PicSetting.xml");

	CString strPath;

	CMarkup m_markUp;
	

	m_markUp.Load(strXMLPath);
	m_markUp.ResetMainPos();
	if ( m_markUp.FindChildElem("PicPath") )
	{
		strPath = m_markUp.GetChildData();

	}
	else
	{
		;
	}

	return strPath;
}

int CWallPaperDlg::getTimeInternal()
{
	CString strXMLPath = GetExePath()+ _T("\\PicSetting.xml");

	int nTimeInternal = 60;//默认60s

	CMarkup m_markUp;


	m_markUp.Load(strXMLPath);
	m_markUp.ResetMainPos();
	if ( m_markUp.FindChildElem("TimeInternal") )
	{
		nTimeInternal = atoi( m_markUp.GetChildData() );

	}
	else
	{
		;
	}

	return nTimeInternal;
}

void CWallPaperDlg::TraverseDir(CString &dir,std::vector <CString>& vec)
{
	CFileFind ff;
	if(dir.Right (1)!="\\")
		dir+="\\";
	dir+="*.jpg*";//用来查找jpg格式的图片
	BOOL ret=ff.FindFile (dir);//FindFile()和FindNextFile()为查找操作符
	while(ret)
	{
		ret=ff.FindNextFile();
		if(ret!=0)
		{
			if(ff.IsDirectory ()&&!ff.IsDots ())
			{
				CString path=ff.GetFilePath ();/*该函数用来获得查找到的文件绝对路径，必须在执行了FindNextFile()后该函数才能执行成功*/
				TraverseDir (path,vec);
			}
			else if(!ff.IsDirectory ()&&!ff.IsDots ())//IsDots该函数用来判断查找的文件属性是否是“.”，“..”，非0表示是，0表示不是。必须在执行了FindNextFile()后该函数才能执行成功
			{
				CString name=ff.GetFileName ();//该函数用来获得查找到的文件的全称，必须在执行了FindNextFile()后该函数才能执行成功。
				CString path=ff.GetFilePath ();
				vec.push_back (path);
			}
		}
	}
}


void CWallPaperDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//MessageBox("hello");

	if ( m_picIndex < m_PicVec.size() )
	{
		SetDesktopWallpaper(m_PicVec[m_picIndex],Tile);
		m_picIndex += 1;
	}
	else
	{
		m_picIndex = 0;
	}

	CDialogEx::OnTimer(nIDEvent);
}
