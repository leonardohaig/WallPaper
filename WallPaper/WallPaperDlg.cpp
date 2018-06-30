
// WallPaperDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CWallPaperDlg �Ի���




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


// CWallPaperDlg ��Ϣ�������

BOOL CWallPaperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

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

	//���ؽ���
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN);
	  int nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	  SetWindowPos(NULL, nFullWidth, nFullHeight, 0, 0, SWP_NOZORDER);  //����0����,�Ƶ������  ����:MoveWindow(0,0,0,0);
	  ShowWindow(SW_HIDE);
	  ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);  //�Ƴ�������ͼ����ʾ

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWallPaperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
 
	//���ñ�ֽ����չ����ʽ
	//��Control Panel\Desktop�е�������ֵ��������
    // TileWallpaper
    //  0: ͼƬ����ƽ�� 
    //  1: ��ƽ�� 
    // WallpaperStyle
    //  0:  0��ʾͼƬ���У�1��ʾƽ��
    //  2:  �������������Ļ
    //  6:  ������Ӧ��Ļ�����ָ߶ȱ�
    //  10: ͼƬ��������С�ü���Ӧ��Ļ�����ݺ��

	//�Կɶ���д�ķ�ʽ��HKCU\Control Panel\Desktopע�����
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
        // ���� WallpaperStyle �� TileWallpaper ��ע�����.
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

	//ͨ������Win32 API����SystemParametersInfo ���������ֽ
	/************************************************
	֮ǰ�����Ѿ������˱�ֽ�����ͣ����Ǳ�ֽͼƬ��ʵ���ļ�·����û
	���á�SystemParametersInfo �������λ��user32.dll�У���֧��
	���Ǵ�ϵͳ�л��Ӳ����������Ϣ�������ĸ���������һ��ָ��������
	��������Ҫִ�еĲ���������������������ָ����Ҫ���õ����ݣ�����
	��һ���������趨�����һ������ָ���ı��Ƿ񱻱��档�����һ������
	����Ӧָ��SPI_SETDESKWALLPAPER��ָ��������Ҫ���ñ�ֽ����������
	�ļ�·������Vista֮ǰ������һ��.bmp���ļ���Vista�͸��߼���ϵͳ
	֧��.jpg��ʽ
	*************************************************/
	//SPI_SETDESKWALLPAPER����ʹ�ñ�ֽ�ı䱣�沢�����ɼ���
    if (SUCCEEDED(hr))
    {
		 //SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, "C:/win7/DeskTop13.jpg", SPIF_SENDCHANGE);//·��ʹ�õ���/ 

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

	int nTimeInternal = 60;//Ĭ��60s

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
	dir+="*.jpg*";//��������jpg��ʽ��ͼƬ
	BOOL ret=ff.FindFile (dir);//FindFile()��FindNextFile()Ϊ���Ҳ�����
	while(ret)
	{
		ret=ff.FindNextFile();
		if(ret!=0)
		{
			if(ff.IsDirectory ()&&!ff.IsDots ())
			{
				CString path=ff.GetFilePath ();/*�ú���������ò��ҵ����ļ�����·����������ִ����FindNextFile()��ú�������ִ�гɹ�*/
				TraverseDir (path,vec);
			}
			else if(!ff.IsDirectory ()&&!ff.IsDots ())//IsDots�ú��������жϲ��ҵ��ļ������Ƿ��ǡ�.������..������0��ʾ�ǣ�0��ʾ���ǡ�������ִ����FindNextFile()��ú�������ִ�гɹ�
			{
				CString name=ff.GetFileName ();//�ú���������ò��ҵ����ļ���ȫ�ƣ�������ִ����FindNextFile()��ú�������ִ�гɹ���
				CString path=ff.GetFilePath ();
				vec.push_back (path);
			}
		}
	}
}


void CWallPaperDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
