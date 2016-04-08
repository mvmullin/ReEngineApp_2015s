//http://www.3dgep.com/understanding-the-view-matrix/

#ifndef __CAMERAMANAGER_H_
#define __CAMERAMANAGER_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng 
{
	class ReEngDLL CameraManager
	{
		int m_nData = 0;
		static CameraManager* m_pCameraInstance;
		std::vector<int> m_lData;

		CameraManager(void);
		CameraManager(CameraManager const& other);
		CameraManager& operator=(CameraManager const& other);
		~CameraManager(void);
		void Release(void);
		void Init(void);

		bool m_bFPS = true; 

		CAMERAMODE m_nMode = CAMERAMODE::CAMPERSP;

		float m_fFOV = 45.0f;

		vector2 m_v2NearFar = vector2(0.001f, 1000.0f);

		vector3 m_v3Position = vector3(0.0f, 0.0f, 5.0f);
		vector3 m_v3Target = vector3(0.0f, 0.0f, 0.0f);
		vector3 m_v3Top = vector3(0.0f, 1.0f, 0.0f);

		vector3 m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
		vector3 m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
		vector3 m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);

		vector3 m_v3PitchYawRoll = vector3(0.0f);

		matrix4 m_m4Projection = matrix4(1.0f);
		matrix4 m_m4View = matrix4(1.0f);

	public:
		static CameraManager* GetInstance();

		static void ReleaseInstance(void);

		matrix4 GetView(void);

		matrix4 GetProjection(bool bOrthographic);

		void SetPosition(vector3 v3Position);

		void SetTarget(vector3 v3Target);

		void SetUp(vector3 v3Up);

		void MoveForward(float fIncrement);

		void MoveSideways(float fIncrement);

		void MoveVertical(float fIncrement);

		void ChangePitch(float fIncrement);

		void ChangeRoll(float fIncrement);

		void ChangeYaw(float fIncrement);


	};

}

#endif