#pragma once

struct __tagAnimFrame
{
	Vec2	vLT;
	Vec2	vCropSize;
	Vec2	vOffset;
	float	fDuration;
};

class CTexture;
class CAnimator;
class CAnimation
{
public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;

private:
	wstring					m_strName;
	CAnimator*				m_pAnimator;
	CTexture*				m_pTex;
	vector<__tagAnimFrame>	m_vecFrame;

	UINT					m_iFrame;
	float					m_fAccTime;

	bool					m_bFinish;

private:
	inline void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	inline const wstring& GetName() { return m_strName; }

	void SetFrame(UINT _iFrame);

	__tagAnimFrame& GetAnimFrame(int _iIdx) { return m_vecFrame[_iIdx]; }
	int GetMaxFrame() { return m_vecFrame.size(); }

public:
	bool IsFinish() { return m_bFinish; }

public:
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vCropSize, Vec2 _vInterval, float _fDuration, UINT _iFrameCount);
	void Add(Vec2 _vLT, Vec2 _vCropSize, Vec2 _vInterval, float _fDuration, UINT _iFrameCount);

public:
	void update();
	void render(HDC _DC);
};

