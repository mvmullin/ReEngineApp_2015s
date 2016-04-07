#include "CameraManager.h"

using namespace ReEng;

CameraManager * CameraManager::m_pInstance = nullptr;
void CameraManager::Init(void)
{
}

void CameraManager::Release(void)
{
}

CameraManager * CameraManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CameraManager();
	}
	return m_pInstance;
}

void CameraManager::ReleaseInstance(void)
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
	
}

CameraManager::CameraManager(void) { Init(); }
CameraManager::CameraManager(CameraManager const & other){}
CameraManager & CameraManager::operator=(CameraManager const & other) { return *this; }
CameraManager::~CameraManager(void) { Release(); }

matrix4 CameraManager::GetView(void)
{
	m_m4View = glm::lookAt(m_v3Position, m_v3Target, m_v3Top);
	return m_m4View;
}

matrix4 CameraManager::GetProjection(bool bOrthographic)
{
	if (bOrthographic)
	{
		m_m4Projection = glm::ortho();
	}

	return m_m4Projection;
}

void CameraManager::SetPosition(vector3 v3Position)
{
	m_v3Position = v3Position;
}

void CameraManager::SetTarget(vector3 v3Target)
{
	m_v3Target = v3Target;
}

void CameraManager::SetUp(vector3 v3Up)
{
	m_v3Upward = v3Up;
}

void CameraManager::MoveForward(float fIncrement)
{
}

void CameraManager::MoveSideways(float fIncrement)
{
}

void CameraManager::MoveVertical(float fIncrement)
{
}

void CameraManager::ChangePitch(float fIncrement)
{
}

void CameraManager::ChangeYaw(float fIncrement)
{
}

void CameraManager::ChangeRoll(float fIncrement)
{
}


