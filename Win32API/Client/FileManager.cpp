#include "pch.h"
#include "FileManager.h"

#include "Core.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "PathManager.h"

#include "Scene.h"
#include "Scene_Editor.h"

#include "resource.h"

CFileManager::CFileManager()
{
}

CFileManager::~CFileManager()
{
}

// Tile Information Setting Window Proc
INT_PTR CALLBACK TileSettingProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			wchar_t szPath[PATH_LIMIT] = {};

			OPENFILENAME tFileOpen = {};

			tFileOpen.lStructSize = sizeof(OPENFILENAME);
			tFileOpen.hwndOwner = CCore::GetInst()->GetMainHwnd();
			tFileOpen.lpstrFile = szPath;
			tFileOpen.nMaxFile = sizeof(szPath);
			tFileOpen.lpstrFilter = L"All\0*.*\0bmp\0*.bmp\0";
			tFileOpen.nFilterIndex = 0;
			tFileOpen.lpstrFileTitle = nullptr;
			tFileOpen.nMaxFileTitle = 0;

			wstring strDirectoryPath = CPathManager::GetInst()->GetContentPath();
			strDirectoryPath += L"Texture\\Tile";

			tFileOpen.lpstrInitialDir = strDirectoryPath.c_str();
			tFileOpen.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			// Modal
			if (GetSaveFileName(&tFileOpen))
			{
				CScene* pScene = CSceneManager::GetInst()->GetCurScene();
				SetDlgItemTextW(hDlg, IDC_EDIT3, szPath);
			}
		}

		if (LOWORD(wParam) == IDOK)
		{
			// Tile Count
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			// Tile Texture Path
			WCHAR szPath[PATH_LIMIT];
			GetDlgItemTextW(hDlg, IDC_EDIT3, szPath, PATH_LIMIT);

			// Current Scene
			CScene* pScene = CSceneManager::GetInst()->GetCurScene();
			assert(dynamic_cast<CScene_Editor*>(pScene));

			// Create Tile
			pScene->CreateTile(iXCount, iYCount, szPath);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}

void CFileManager::Synchronization_SaveTile()
{
	if (!strTilePath.empty())
	{
		CScene* pScene = CSceneManager::GetInst()->GetCurScene();
		pScene->SaveTile(strTilePath);

		return;
	}

	wchar_t szPath[PATH_LIMIT] = {};

	OPENFILENAME tFileOpen = {};

	tFileOpen.lStructSize = sizeof(OPENFILENAME);
	tFileOpen.hwndOwner = CCore::GetInst()->GetMainHwnd();
	tFileOpen.lpstrFile = szPath;
	tFileOpen.nMaxFile = sizeof(szPath);
	tFileOpen.lpstrFilter = L"All\0*.*\0til\0*.til\0";
	tFileOpen.nFilterIndex = 0;
	tFileOpen.lpstrFileTitle = nullptr;
	tFileOpen.nMaxFileTitle = 0;

	wstring strDirectoryPath = CPathManager::GetInst()->GetContentPath();
	strDirectoryPath += L"Tile";

	tFileOpen.lpstrInitialDir = strDirectoryPath.c_str();
	tFileOpen.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetSaveFileName(&tFileOpen))
	{
		CScene* pScene = CSceneManager::GetInst()->GetCurScene();

		pScene->SaveTile(szPath);

		strTilePath = szPath;
	}
}

void CFileManager::Synchronization_SaveTileAS()
{
	wchar_t szPath[PATH_LIMIT] = {};

	OPENFILENAME tFileOpen = {};

	tFileOpen.lStructSize = sizeof(OPENFILENAME);
	tFileOpen.hwndOwner = CCore::GetInst()->GetMainHwnd();
	tFileOpen.lpstrFile = szPath;
	tFileOpen.nMaxFile = sizeof(szPath);
	tFileOpen.lpstrFilter = L"All\0*.*\0til\0*.til\0";
	tFileOpen.nFilterIndex = 0;
	tFileOpen.lpstrFileTitle = nullptr;
	tFileOpen.nMaxFileTitle = 0;

	wstring strDirectoryPath = CPathManager::GetInst()->GetContentPath();
	strDirectoryPath += L"Tile";

	tFileOpen.lpstrInitialDir = strDirectoryPath.c_str();
	tFileOpen.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetSaveFileName(&tFileOpen))
	{
		CScene* pScene = CSceneManager::GetInst()->GetCurScene();

		pScene->SaveTile(szPath);

		strTilePath = szPath;
	}
}

void CFileManager::Synchronization_LoadTile()
{
	wchar_t szPath[PATH_LIMIT] = {};

	OPENFILENAME FileDirectory = {};

	FileDirectory.lStructSize = sizeof(OPENFILENAME);
	FileDirectory.hwndOwner = CCore::GetInst()->GetMainHwnd();
	FileDirectory.lpstrFile = szPath;
	FileDirectory.nMaxFile = sizeof(szPath);
	FileDirectory.lpstrFilter = L"All\0*.*\0til\0*.til\0";
	FileDirectory.nFilterIndex = 0;
	FileDirectory.lpstrFileTitle = nullptr;
	FileDirectory.nMaxFileTitle = 0;

	wstring strDirectoryPath = CPathManager::GetInst()->GetContentPath();
	strDirectoryPath += L"Tile";

	FileDirectory.lpstrInitialDir = strDirectoryPath.c_str();
	FileDirectory.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetOpenFileName(&FileDirectory))
	{
		CScene* pScene = CSceneManager::GetInst()->GetCurScene();

		pScene->LoadTile(szPath);

		strTilePath = szPath;
	}
}
