#include "CameraManager.h"

using namespace ReEng;

CameraManager * CameraManager::m_pInstance = nullptr;
CameraManager & CameraManager::operator=(CameraManager const & other)
{
	return *this;
}

CameraManager::~CameraManager(void){}

void CameraManager::Release(void)
{
}

void CameraManager::Init(void)
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

matrix4 CameraManager::GetView(void)
{
	matrix4 view = glm::lookAt(m_v3Position, m_v3Target, m_v3Top);
	return view;
}

matrix4 CameraManager::GetProjection(bool bOrthographic)
{
	return matrix4();
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

void CameraManager::ChangeRoll(float fIncrement)
{
}

void CameraManager::ChangeYaw(float fIncrement)
{
}
