#pragma once
#include <souistd.h>
#include <interface/SFactory-i.h>
#include "SFuncSlot.h"
#include <commgr2.h>
#include <resprovider-zip/zipresprovider-param.h>
#include <resprovider-7zip/zip7resprovider-param.h>
#include <shellapi.h>
#include "souidlgs.h"

void Slog(const char* szLog) {
	SStringW str = S_CA2W(szLog, CP_UTF8);
	SLOGI2("qjs") << str.c_str();
}

void SDebugBreak(int id) {
	(id);
}

IWindow* GetCaptured(IObject* pObj) {
	IWindow* pWnd = sobj_cast<SWindow>(pObj);
	if (!pWnd) return 0;
	SWND hCap = pWnd->GetCapture();
	SWindow* pCap = SWindowMgr::GetWindow(hCap);
	return (IWindow*)pCap;
}

void Slog2(const char* szLog,int level) {
	SStringW str = S_CA2W(szLog, CP_UTF8);
	SLOG("qjs",level) << str.c_str();
}

BOOL InitFileResProvider(IResProvider* pResProvider, const char* path)
{
	SStringT strPath = S_CA2T(path,CP_UTF8);
	return pResProvider->Init((WPARAM)strPath.c_str(), 0);
}

BOOL InitPEResProvider(IResProvider* pResProvider, const char* path)
{
	SStringT strPath = S_CA2T(path, CP_UTF8);
	return pResProvider->Init((WPARAM)strPath.c_str(), 1);
}

IApplication* GetApp() {
	return SApplication::getSingletonPtr();
}

HWND GetActiveWnd() {
	return GetActiveWindow();
}

BOOL SConnect(IWindow* pObj, int evtId, Value& jsThis, Value& jsFun) {
	IEvtSlot* pSlot = new SFuncSlot(jsThis, jsFun);
	BOOL bRet = pObj->SubscribeEvent(evtId, pSlot);
	pSlot->Release();
	return bRet;
}

LPARAM SGetItemIndex(IWindow* pItem) {
	pItem = pItem->GetIRoot();
	IItemPanel* pItemPanel = NULL;
	LPARAM ret = -1;
	pItem->QueryInterface(__uuidof(IItemPanel), (IObjRef**) & (pItemPanel));
	if (pItemPanel) {
		ret = pItemPanel->GetItemIndex();
		pItemPanel->Release();
	}
	return ret;
}

int SMessageBoxA(HWND hOwner, LPCSTR pszText, LPCSTR pszTitle, UINT uType) {
	SStringT strText = S_CA2T(pszText,CP_UTF8);
	SStringT strTitle = S_CA2T(pszTitle, CP_UTF8);
	return SMessageBox(hOwner, strText, strTitle, uType);
}

namespace SOUI {
	extern SComMgr2  g_comMgr;
}

IResProvider* CreateZipResProvider(IApplication * pApp,LPCSTR pszPath, LPCSTR pszPsw) {
	IResProvider* pRet = NULL;
	if (g_comMgr.CreateResProvider_ZIP((IObjRef**)&pRet))
	{
		SStringT strPath = S_CA2T(pszPath, CP_UTF8);
		IRenderFactory* pRenderFactory = pApp?pApp->GetRenderFactory():NULL;
		ZIPRES_PARAM param;
		ZipFile(&param,pRenderFactory, strPath, pszPsw);
		BOOL bRet = pRet->Init((WPARAM)&param, 0);
		if (!bRet) {
			pRet->Release();
			pRet = NULL;
		}
	}
	return pRet;
}

IResProvider* Create7ZResProvider(IApplication* pApp, LPCSTR pszPath, LPCSTR pszPsw) {
	IResProvider* pRet = NULL;
	if (g_comMgr.CreateResProvider_7ZIP((IObjRef**)&pRet))
	{
		SStringT strPath = S_CA2T(pszPath, CP_UTF8);
		IRenderFactory* pRenderFactory = pApp? pApp->GetRenderFactory():NULL;
		ZIP7RES_PARAM param;
		Zip7File(&param, pRenderFactory, strPath, pszPsw);
		BOOL bRet = pRet->Init((WPARAM)&param, 0);
		if (!bRet) {
			pRet->Release();
			pRet = NULL;
		}
	}
	return pRet;
}

ITranslatorMgr* CreateTranslatorMgr() {
	ITranslatorMgr* pRet = NULL;
	g_comMgr.CreateTranslator((IObjRef**)&pRet);
	return pRet;
}

IHttpClient* CreateHttpClient() {
	IHttpClient* pRet = NULL;
	g_comMgr.CreateHttpClient((IObjRef**)&pRet);
	return pRet;
}

ILogMgr* CreateLogMgr() {
	ILogMgr* pRet = NULL;
	g_comMgr.CreateLog4z((IObjRef**)&pRet);
	return pRet;
}

BOOL SetXmlTranslator(IApplication * pApp,LPCSTR xmlId) {
	ITranslatorMgr* pTransMgr = pApp->GetTranslator();
	if (!pTransMgr || !pTransMgr->IsValid())
		return FALSE;
	IXmlDoc * xmlLang = pApp->LoadXmlDocmentA(xmlId);
	if (!xmlLang)
		return FALSE;
	SAutoRefPtr<ITranslator> langCN;
	pTransMgr->CreateTranslator(&langCN);
	BOOL bRet = FALSE;
	IXmlNode* xmlNode = xmlLang->Root()->Child(L"language", false);
	if (xmlNode) {
		langCN->Load(xmlNode, 1);
		pTransMgr->InstallTranslator(langCN);
		SStringW strFont;
		langCN->getFontInfo(&strFont);
		if (!strFont.IsEmpty())
		{//从翻译文件中获取并设置程序的字体信息
			pApp->SetDefaultFontInfo(strFont.c_str());
		}
		bRet = TRUE;
	}
	xmlLang->Release();
	return bRet;
}

HINSTANCE SFork(LPCSTR pszDir) {
	TCHAR szHostPath[MAX_PATH];
	::GetModuleFileName(NULL, szHostPath, MAX_PATH);
	SStringT strApp = S_CA2T(pszDir, CP_UTF8);
	return ::ShellExecute(NULL,_T("open"),szHostPath,strApp.c_str(),NULL,SW_SHOWNORMAL);
}

HINSTANCE SShellExecute(HWND hWnd,LPCSTR pszOp,LPCSTR pszFile,LPCSTR pszParam,LPCSTR pszDir,int show) {
	SStringT strOp = S_CA2T(pszOp, CP_UTF8);
	SStringT strFile = S_CA2T(pszFile, CP_UTF8);
	SStringT strParam = S_CA2T(pszParam, CP_UTF8);
	SStringT strDir = S_CA2T(pszDir, CP_UTF8);
	HINSTANCE hRet = ::ShellExecute(hWnd, strOp, strFile, strParam, strDir, show);
	return hRet;
}

typedef HRESULT(WINAPI* FunSHCreateItemFromParsingName)(PCWSTR, IBindCtx*, REFIID, void**);

string PickFolder(const char * initPath) {
	SStringA defPath(initPath);
	SStringA ret;
	bool bNewDialog = false;
	do {
		CShellFileOpenDialog dlg;
		if (dlg.IsNull()) break;
		DWORD dwOptions;
		if (!SUCCEEDED(dlg.GetPtr()->GetOptions(&dwOptions)))
			break;
		if (!SUCCEEDED(dlg.GetPtr()->SetOptions(dwOptions | FOS_PICKFOLDERS)))
			break;
		if (!defPath.IsEmpty()) {
			HMODULE hShell = LoadLibrary(_T("shell32.dll"));
			if (hShell)
			{
				IShellItem* folderItem = NULL;
				SStringW strDefPath = S_CA2W(defPath.c_str(), CP_UTF8);
				FunSHCreateItemFromParsingName funSHCreateItemFromParsingName = (FunSHCreateItemFromParsingName)GetProcAddress(hShell, "SHCreateItemFromParsingName");
				if (funSHCreateItemFromParsingName &&
					funSHCreateItemFromParsingName(strDefPath.c_str(), NULL, IID_PPV_ARGS(&folderItem)) == S_OK) {
					dlg.GetPtr()->SetFolder(folderItem);
					folderItem->Release();
				}
				FreeLibrary(hShell);
			}
		}
		bNewDialog = true;
		if (IDOK == dlg.DoModal()) {
			SStringW strDir;
			dlg.GetFilePath(strDir);
			ret = S_CW2A(strDir, CP_UTF8);
		}
	} while (false);
	if (!bNewDialog) {
		CFolderDialog folderDialog;
		if (folderDialog.DoModal() == IDOK) {
			SStringT folder = folderDialog.GetFolderPath();
			ret = S_CT2A(folder, CP_UTF8);
		}
	}
	return string(ret.c_str(), ret.GetLength());
}

string GetSpecialPath(const char * pszType) {
	SStringA type(pszType);
	type.MakeLower();
	int ClsId = -1;
	if (type == "video") {
		ClsId = CSIDL_MYVIDEO;
	}
	else if (type == "music")
	{
		ClsId = CSIDL_MYMUSIC;
	}
	else if (type == "document") {
		ClsId = CSIDL_MYDOCUMENTS;
	}
	else if (type == "appdata") {
		ClsId = CSIDL_APPDATA;
	}
	else if (type == "desktop") {
		ClsId = CSIDL_DESKTOP;
	}
	if (ClsId == -1)
		return "";
	wchar_t buf[MAX_PATH] = { 0 };
	SHGetSpecialFolderPath(NULL, buf, ClsId, TRUE);
	SStringA ret= S_CW2A(buf, CP_UTF8);
	return string(ret.c_str(), ret.GetLength());
}

BOOL IsRunAsAdmin()         
{
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;

	BOOL  b = AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&AdministratorsGroup);

	if (b)
	{
		CheckTokenMembership(NULL, AdministratorsGroup, &b);
		FreeSid(AdministratorsGroup);
	}

	return  b;
}

int RunAsAdmin(LPCSTR szFolder, LPCSTR szJs,BOOL waitEnd) {
	TCHAR szExe[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szExe, MAX_PATH);

	SStringT strFolder = S_CA2T(szFolder, CP_UTF8);
	SStringT strJs = S_CA2T(szJs, CP_UTF8);
	SStringT strParam;
	if(strJs.IsEmpty())
		strParam.Format(_T("\"%s\""), strFolder.c_str());
	else
		strParam.Format(_T("\"%s\" %s"), strFolder.c_str(), strJs.c_str());
	SHELLEXECUTEINFO sei = { 0 };
	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI;
	sei.lpVerb = _T("runas"); // 以管理员身份运行
	sei.lpFile = szExe; // 要启动的程序
	sei.lpParameters = strParam.c_str();
	sei.nShow = SW_SHOWNORMAL;
	if (!ShellExecuteEx(&sei)) {
		// 处理启动失败的情况
		SLOGE2("soui4js")<<"RunAsAdmin failed! err="<< GetLastError();
		return -1;
	}
	int nRet = 0;
	if (waitEnd) {
		WaitForSingleObject(sei.hProcess, INFINITE);
		DWORD exitCode = 0;;
		GetExitCodeProcess(sei.hProcess, &exitCode);
		nRet = (int)exitCode;
	}
	CloseHandle(sei.hProcess);
	return nRet;
}

BOOL MkPath(const std::string& path,const std::string &root) {
	SStringT strPath = S_CA2T(path.c_str(), CP_UTF8);
	SStringT strRoot = S_CA2T(root.c_str(), CP_UTF8);

	SStringT strFullPath;
	if (!strRoot.IsEmpty()) {
		strFullPath = strRoot;
		if (!strFullPath.EndsWith('\\'))
			strFullPath += '\\';
	}
	strPath.ReplaceChar('/', '\\');

	struct _stat64i32 st;
	int ret = _tstat(strFullPath+strPath, &st);
	if (ret == 0 && st.st_mode & _S_IFDIR) {
		return TRUE;
	}

	TCHAR szCurDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szCurDir);

	BOOL bRet = TRUE;
	SStringTList subPaths;
	SplitString(strPath, '\\', subPaths);
	for (UINT i = 0; i < subPaths.GetCount(); i++) {
		strFullPath += subPaths[i];
		struct _stat64i32 st;
		int ret = _tstat(strFullPath, &st);
		if (ret != 0 || (st.st_mode & _S_IFDIR) == 0) {
			if (!CreateDirectory(strFullPath, NULL))
			{
				bRet = FALSE;
				break;
			}
		}
		strFullPath += '\\';
	}
	SetCurrentDirectory(szCurDir);
	return bRet;
}

void Exp_Global(qjsbind::Module* module)
{
	module->ExportFunc("log", &Slog);
	module->ExportFunc("DebugBreak", &SDebugBreak);
	module->ExportFunc("log2", &Slog2);
	module->ExportFunc("GetApp", &GetApp);
	module->ExportFunc("GetActiveWindow", &GetActiveWnd);
	module->ExportFunc("GetCaptured", &GetCaptured);
	module->ExportFunc("InitFileResProvider", &InitFileResProvider);
	module->ExportFunc("InitPEResProvider", &InitPEResProvider);
	module->ExportFunc("CreateSouiFactory", &CreateSouiFactory);
	module->ExportFunc("CreateZipResProvider", &CreateZipResProvider);
	module->ExportFunc("Create7ZResProvider", &Create7ZResProvider);
	module->ExportFunc("CreateTranslatorMgr", &CreateTranslatorMgr);
	module->ExportFunc("CreateHttpClient", &CreateHttpClient);
	module->ExportFunc("CreateLogMgr", &CreateLogMgr);	
	module->ExportFunc("SetXmlTranslator", &SetXmlTranslator);
	module->ExportFunc("SConnect", &SConnect);
	module->ExportFunc("SGetItemIndex", &SGetItemIndex);
	module->ExportFunc("SMessageBox", &SMessageBoxA);
	module->ExportFunc("PickFolder", &PickFolder);
	module->ExportFunc("GetSpecialPath", &GetSpecialPath);
	module->ExportFunc("ShellExecute", &SShellExecute);
	module->ExportFunc("Fork", &SFork);
	module->ExportFunc("IsRunAsAdmin", &IsRunAsAdmin);
	module->ExportFunc("RunAsAdmin", &RunAsAdmin);
	module->ExportFunc("MkPath", &MkPath);
}
