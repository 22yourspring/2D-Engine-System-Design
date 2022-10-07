#pragma once

enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	AWAY,
};

enum class KEY
{
	UP,
	DOWN,
	LEFT,
	RIGHT,

	Q, 
	W, 
	E, 
	R, 
	T, 
	Y, 
	U, 
	I, 
	O, 
	P,
	A,
	S, 
	D, 
	F, 
	G, 
	H, 
	J, 
	K, 
	L,
	Z, 
	X, 
	C,
	V, 
	B, 
	N, 
	M,

	NUM_0,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,

	NUMPAD_0,
	NUMPAD_1,
	NUMPAD_2,
	NUMPAD_3,
	NUMPAD_4,
	NUMPAD_5,
	NUMPAD_6,
	NUMPAD_7,
	NUMPAD_8,
	NUMPAD_9,

	LBTN,
	RBTN,

	INSERT,
	DEL,
	HOME,	
	END,
	PAGE_UP,
	PAGE_DOWN,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	TAB,
	ESC,
	ENTER,

	COUNT,
};

struct __tagKeyInfo
{
	KEY_STATE	eState;		
	bool		bPrevPush;	
};

class CKeyManager
{
	SINGLE(CKeyManager);

private:
	vector<__tagKeyInfo> m_vecKey;
	Vec2				 m_vMousePos;

public:
	inline KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[static_cast<int>(_eKey)].eState; }
	Vec2 GetMousePos() { return m_vMousePos; }

public:
	void init();
	void update();
};

