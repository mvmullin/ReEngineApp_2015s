#include "CameraManager.h"

using namespace ReEng;

CameraManager* CameraManager::m_pCameraInstance = nullptr;
void CameraManager::Init(void)
{
}

void CameraManager::Release(void)
{
}

CameraManager * CameraManager::GetInstance()
{
	if (m_pCameraInstance == nullptr)
	{
		m_pCameraInstance = new CameraManager();
	}
	return m_pCameraInstance;
}

void CameraManager::ReleaseInstance(void)
{
	if (m_pCameraInstance != nullptr)
	{
		delete m_pCameraInstance;
		m_pCameraInstance = nullptr;
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
		//m_m4Projection = glm::ortho();
	}
	else
	{
		m_m4Projection = glm::perspective(m_fFOV, 1080.0f / 768.0f, m_v2NearFar.x, m_v2NearFar.y);
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
	m_v3Forward += fIncrement;
}

void CameraManager::MoveSideways(float fIncrement)
{
	m_v3Rightward += fIncrement;
}

void CameraManager::MoveVertical(float fIncrement)
{
	m_v3Upward += fIncrement;
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


