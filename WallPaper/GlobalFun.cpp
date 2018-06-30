#include "stdafx.h"
#include "GlobalFun.h"

// 程序开机自动启动
void autostart(CString strExeName)
{
	if ( strExeName.IsEmpty() )
	{
		return;
	}
	HKEY hKey;
	CString strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

	//1、找到系统的启动项  
	if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) ///打开启动项       
	{
		//2、得到本程序自身的全路径
		TCHAR strExeFullDir[MAX_PATH];
		GetModuleFileName(NULL, strExeFullDir, MAX_PATH);

		//3、判断注册表项是否已经存在
		TCHAR strDir[MAX_PATH] = {};
		DWORD nLength = MAX_PATH;
		long result = RegGetValue(hKey, nullptr, strExeName, RRF_RT_REG_SZ, 0, strDir, &nLength);

		//4、已经存在
		if (result != ERROR_SUCCESS || _tcscmp(strExeFullDir, strDir) != 0)
		{
			//5、添加一个子Key,并设置值，"GISRestart"是应用程序名字（不加后缀.exe） 
			RegSetValueEx(hKey, "GISRestart", 0, REG_SZ, (LPBYTE)strExeFullDir, (lstrlen(strExeFullDir) + 1)*sizeof(TCHAR));

			//6、关闭注册表
			RegCloseKey(hKey);
		}
	}
	else
	{
		//QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("\n系统参数错误,不能随系统启动n"));
	}
}

// 取消开机自动启动
void cancelAutoStart(CString strExeName)
{
	if ( strExeName.IsEmpty() )
	{
		return;
	}

	HKEY hKey;
	CString strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

	//1、找到系统的启动项  
	if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
	{
		//2、删除值
		RegDeleteValue(hKey, strExeName);

		//3、关闭注册表
		RegCloseKey(hKey);
	}
}


CString	GetExePath()   
{  
	CString strAppPath;  // 保存结果
	TCHAR szModuleFileName[MAX_PATH]; // 全路径名
	TCHAR drive[_MAX_DRIVE];  // 盘符名称，比如说C盘啊，D盘啊
	TCHAR dir[_MAX_DIR]; // 目录
	TCHAR fname[_MAX_FNAME];  // 进程名字
	TCHAR ext[_MAX_EXT]; //后缀，一般为exe或者是dll

	if (NULL == GetModuleFileName(NULL, szModuleFileName, MAX_PATH)) //获得当前进程的文件路径
		return FALSE;

	_tsplitpath_s( szModuleFileName, drive, dir, fname, ext );  //分割该路径，得到盘符，目录，文件名，后缀名

	strAppPath = drive;
	strAppPath += dir;


	return strAppPath;

}