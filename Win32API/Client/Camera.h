#pragma once

class CObject;
class CCamera
{
	SINGLE(CCamera);

private:
	Vec2		m_vObservedPos;		// Point of view of the Camera
	Vec2		m_vCurrObservedPos;	// Curr Point of View of the Camera
	Vec2		m_vShifted;			// Camera Position Distance from Center
	CObject*	m_pObservedObject;	// Target of Observed

public:
	inline void SetObservedPosition(Vec2 _vObservedPos) { m_vObservedPos = _vObservedPos; }
	inline Vec2 GetObservedPosition() { return m_vCurrObservedPos; }
	inline void SetObservedObject(CObject* _pTarget) { m_pObservedObject = _pTarget; }

	inline Vec2 GetRenderPos(Vec2 _vObjectPos) { return _vObjectPos - m_vShifted; }
	inline Vec2 GetLocationPos(Vec2 _vRenderPos) { return _vRenderPos + m_vShifted; }

private:
	void CalculateShifted();

public:
	void update();
};

