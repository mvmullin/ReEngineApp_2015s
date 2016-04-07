#include "CameraManager.h"

ReEng::CameraManager & ReEng::CameraManager::operator=(CameraManager const & other)
{
	return *this;
}

ReEng::CameraManager::~CameraManager(void)
{
}

void ReEng::CameraManager::Release(void)
{
}

void ReEng::CameraManager::Init(void)
{
}

ReEng::CameraManager * ReEng::CameraManager::GetInstance()
{
	return nullptr;
}

void ReEng::CameraManager::ReleaseInstance(void)
{
}

ReEng::matrix4 ReEng::CameraManager::GetView(void)
{
	matrix4 view = glm::lookAt(m_v3Position, m_v3Target, m_v3Top);
	return view;
}

ReEng::matrix4 ReEng::CameraManager::GetProjection(bool bOrthographic)
{
	return matrix4();
}

void ReEng::CameraManager::SetPosition(vector3 v3Position)
{
}

void ReEng::CameraManager::SetTarget(vector3 v3Target)
{
}

void ReEng::CameraManager::SetUp(vector3 v3Up)
{
}

void ReEng::CameraManager::MoveForward(float fIncrement)
{
}

void ReEng::CameraManager::MoveSideways(float fIncrement)
{
}

void ReEng::CameraManager::MoveVertical(float fIncrement)
{
}

void ReEng::CameraManager::ChangePitch(float fIncrement)
{
}

void ReEng::CameraManager::ChangeRoll(float fIncrement)
{
}

void ReEng::CameraManager::ChangeYaw(float fIncrement)
{
}
