#pragma once
class CTimeManager
{
	SINGLE(CTimeManager);

private:
	LARGE_INTEGER	m_llCurrCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDt;			// 1 Frame �ɸ� �ð�
	double			m_dAcc;			// ���� �ð�
	UINT			m_iCallCount;	// �ʴ� �Լ� ȣ��
	UINT			m_iFPS;			// �ʴ� ������ �ð�

public:
	void init();
	void update();

public:
	double GetDT() { return m_dDt; }
	float  GetDT_f() { return static_cast<float>(m_dDt); }
};

