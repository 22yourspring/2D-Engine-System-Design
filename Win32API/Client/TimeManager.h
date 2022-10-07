#pragma once
class CTimeManager
{
	SINGLE(CTimeManager);

private:
	LARGE_INTEGER	m_llCurrCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDt;			// 1 Frame 걸린 시간
	double			m_dAcc;			// 누적 시간
	UINT			m_iCallCount;	// 초당 함수 호출
	UINT			m_iFPS;			// 초당 프레임 시간

public:
	void init();
	void update();

public:
	double GetDT() { return m_dDt; }
	float  GetDT_f() { return static_cast<float>(m_dDt); }
};

