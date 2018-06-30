#include "stdafx.h"
#include "GlobalFun.h"

// ���򿪻��Զ�����
void autostart(CString strExeName)
{
	if ( strExeName.IsEmpty() )
	{
		return;
	}
	HKEY hKey;
	CString strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

	//1���ҵ�ϵͳ��������  
	if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) ///��������       
	{
		//2���õ������������ȫ·��
		TCHAR strExeFullDir[MAX_PATH];
		GetModuleFileName(NULL, strExeFullDir, MAX_PATH);

		//3���ж�ע������Ƿ��Ѿ�����
		TCHAR strDir[MAX_PATH] = {};
		DWORD nLength = MAX_PATH;
		long result = RegGetValue(hKey, nullptr, strExeName, RRF_RT_REG_SZ, 0, strDir, &nLength);

		//4���Ѿ�����
		if (result != ERROR_SUCCESS || _tcscmp(strExeFullDir, strDir) != 0)
		{
			//5�����һ����Key,������ֵ��"GISRestart"��Ӧ�ó������֣����Ӻ�׺.exe�� 
			RegSetValueEx(hKey, "GISRestart", 0, REG_SZ, (LPBYTE)strExeFullDir, (lstrlen(strExeFullDir) + 1)*sizeof(TCHAR));

			//6���ر�ע���
			RegCloseKey(hKey);
		}
	}
	else
	{
		//QMessageBox::warning(0, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("\nϵͳ��������,������ϵͳ����n"));
	}
}

// ȡ�������Զ�����
void cancelAutoStart(CString strExeName)
{
	if ( strExeName.IsEmpty() )
	{
		return;
	}

	HKEY hKey;
	CString strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

	//1���ҵ�ϵͳ��������  
	if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
	{
		//2��ɾ��ֵ
		RegDeleteValue(hKey, strExeName);

		//3���ر�ע���
		RegCloseKey(hKey);
	}
}


CString	GetExePath()   
{  
	CString strAppPath;  // ������
	TCHAR szModuleFileName[MAX_PATH]; // ȫ·����
	TCHAR drive[_MAX_DRIVE];  // �̷����ƣ�����˵C�̰���D�̰�
	TCHAR dir[_MAX_DIR]; // Ŀ¼
	TCHAR fname[_MAX_FNAME];  // ��������
	TCHAR ext[_MAX_EXT]; //��׺��һ��Ϊexe������dll

	if (NULL == GetModuleFileName(NULL, szModuleFileName, MAX_PATH)) //��õ�ǰ���̵��ļ�·��
		return FALSE;

	_tsplitpath_s( szModuleFileName, drive, dir, fname, ext );  //�ָ��·�����õ��̷���Ŀ¼���ļ�������׺��

	strAppPath = drive;
	strAppPath += dir;


	return strAppPath;

}