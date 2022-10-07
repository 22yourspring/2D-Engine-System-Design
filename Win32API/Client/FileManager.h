#pragma once
class CFileManager
{
	SINGLE(CFileManager);

private:
	wstring strTilePath;

public:
	void Synchronization_SaveTile();
	void Synchronization_SaveTileAS();
	void Synchronization_LoadTile();
};

