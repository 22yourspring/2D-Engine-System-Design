#pragma once

template <typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (_vec[i] != nullptr)
			delete _vec[i];
	}
	_vec.clear();
}

template <typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); iter++)
	{
		if (iter->second)
			delete iter->second;
	}
	_map.clear();
}

static float lerp(float _fSource, float _fDestination, float _fRatio)
{
	return _fSource + (_fDestination - _fSource) * _fRatio;
}

static Vec2 lerp(Vec2 _vSource, Vec2 _vDestination, float _fRatio)
{
	return _vSource + (_vDestination - _vSource) * _fRatio;
}

static float DegreeToRadian(float _fDegree)
{
	return (_fDegree * (PI / 180));
}

static float RadianToDegree(float _fRadian)
{
	return(_fRadian * (180 / PI));
}