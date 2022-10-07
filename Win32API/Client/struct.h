#pragma once

typedef struct Vec2
{
	float x;
	float y;

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{
	}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{
	}

	Vec2(int _x, int _y)
		: x(static_cast<float>(_x))
		, y(static_cast<float>(_y))
	{
	}

	Vec2(long _x, long _y)
		: x(static_cast<float>(_x))
		, y(static_cast<float>(_y))
	{
	}

	Vec2(POINT _pt)
		: x(static_cast<float>(_pt.x))
		, y(static_cast<float>(_pt.y))
	{
	}
	
public:
	void operator = (const POINT& _pt)
	{
		x = static_cast<float>(_pt.x);
		y = static_cast<float>(_pt.y);
	}

	Vec2 operator + (const Vec2& _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}

	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	Vec2 operator - (const Vec2& _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	Vec2 operator * (const Vec2& _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	Vec2 operator * (int _iValue)
	{
		return Vec2(x * (float)_iValue, y * (float)_iValue);
	}

	Vec2 operator * (float _fValue)
	{
		return Vec2(x * _fValue, y * _fValue);
	}

	Vec2 operator * (double _dValue)
	{
		return Vec2(x * (float)_dValue, y * (float)_dValue);
	}

	Vec2 operator / (const Vec2& _vOther)
	{
		assert(!(_vOther.x == 0.f || _vOther.y == 0.f));

		return Vec2(x / _vOther.x, y / _vOther.y);
	}

	Vec2 operator / (const float _fValue)
	{
		assert(!(_fValue == 0.f));

		return Vec2(x / _fValue, y / _fValue);
	}
	
	float Pythagoras_Length()
	{
		return sqrt(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float fHypotenuse = Pythagoras_Length();

		assert(fHypotenuse != 0.f);
		
		x /= fHypotenuse;
		y /= fHypotenuse;

		return *this;
	}

}VECTOR2, VEC2;

// typedef void(*__FUNCTION_PTR_0PARAM)();
// typedef void(*__FUNCTION_PTR_1PARAM)(DWORD_PTR);
// typedef void(*__FUNCTION_PTR_2PARAM)(DWORD_PTR, DWORD_PTR);
// typedef void(*__FUNCTION_PTR_3PARAM)(DWORD_PTR, DWORD_PTR, DWORD_PTR);

typedef function<void()>									__FUNCTION_PTR_0PARAM;
typedef function<void(DWORD_PTR)>							__FUNCTION_PTR_1PARAM;
typedef function<void(DWORD_PTR, DWORD_PTR)>				__FUNCTION_PTR_2PARAM;
typedef function<void(DWORD_PTR, DWORD_PTR, DWORD_PTR)>		__FUNCTION_PTR_3PARAM;

typedef struct __tagFunctionPointer
{
	__FUNCTION_PTR_0PARAM	pFuncPtr_0Param;
	__FUNCTION_PTR_1PARAM	pFuncPtr_1Param;
	__FUNCTION_PTR_2PARAM	pFuncPtr_2Param;
	__FUNCTION_PTR_3PARAM	pFuncPtr_3Param;

	DWORD_PTR		param1;
	DWORD_PTR		param2;
	DWORD_PTR		param3;
}__FUNCTION;
