#pragma once

enum class UI_TYPE
{
	TILE,
	INVENTORY,

	COUNT
};

class CObject;
class CUI;
class CScene
{
public:
	CScene();
	virtual ~CScene();

	friend class CObjectManager;

private:
	vector<CObject*>	m_arrObject[static_cast<UINT>(GROUP_TYPE::COUNT)];
	wstring				m_strName;

	UINT				m_iTileMaxRow;		// Y
	UINT				m_iTileMaxCol;		// X
	wstring				m_strTileResourcePath;

protected:
	CUI*				m_arrUI[static_cast<UINT>(UI_TYPE::COUNT)];

private:
	void AddObject(CObject* _pObject, GROUP_TYPE _eType);
	void DeleteGroup(GROUP_TYPE _eType);

public:
	inline const vector<CObject*>& GetCollisionChannel(GROUP_TYPE _eType) { return m_arrObject[(UINT)_eType]; }
	inline const vector<CObject*>& GetObjectGroup(GROUP_TYPE _eType) { return m_arrObject[(UINT)_eType]; }
	inline vector<CObject*>& GetUIGroup() { return m_arrObject[(UINT)GROUP_TYPE::UI]; }

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileMaxRow() { return m_iTileMaxRow; }				// Y
	UINT GetTileMaxCol() { return m_iTileMaxCol; }				// X

public:
	void CreateTile(UINT _iXCount, UINT _iYCount, const wstring& _strResourceKey);

public:
	void SaveTile(const wstring& _strTilePath);
	void LoadTile(const wstring& strRelativePath);

public:
	virtual void SceneIn() = 0;
	virtual void SceneOut() = 0;

	virtual void KeyShortcut() = 0;
	virtual void RegisterUI(CUI* _pUI, UI_TYPE _eType) = 0;

	virtual void update();
	void Component_update();

	void render(HDC _DC);
};

