#include "MyBOClass.h"
//  MyBOClass
void MyBOClass::Init(void)
{
	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_v3CenterG = vector3(0.0f);
	m_v3MinG = vector3(0.0f);
	m_v3MaxG = vector3(0.0f);

	m_v3HalfWidth = vector3(0.0f);
	m_v3HalfWidthG = vector3(0.0f);

	m_fRadius = 0.0f;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}
void MyBOClass::Swap(MyBOClass& other)
{
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_v3CenterG, other.m_v3CenterG);
	std::swap(m_v3MinG, other.m_v3MinG);
	std::swap(m_v3MaxG, other.m_v3MaxG);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
	std::swap(m_v3HalfWidthG, other.m_v3HalfWidthG);

	std::swap(m_fRadius, other.m_fRadius);

	std::swap(m_pMeshMngr, other.m_pMeshMngr);
}
void MyBOClass::Release(void) {/* No pointers allocated yet */ }
//The big 3
MyBOClass::MyBOClass(std::vector<vector3> a_lVectorList)
{
	//Init the default values
	Init();

	//Count the points of the incoming list
	uint nVertexCount = a_lVectorList.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = a_lVectorList[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > a_lVectorList[nVertex].x) //If min is larger than current
			m_v3Min.x = a_lVectorList[nVertex].x;
		else if (m_v3Max.x < a_lVectorList[nVertex].x)//if max is smaller than current
			m_v3Max.x = a_lVectorList[nVertex].x;

		if (m_v3Min.y > a_lVectorList[nVertex].y) //If min is larger than current
			m_v3Min.y = a_lVectorList[nVertex].y;
		else if (m_v3Max.y < a_lVectorList[nVertex].y)//if max is smaller than current
			m_v3Max.y = a_lVectorList[nVertex].y;

		if (m_v3Min.z > a_lVectorList[nVertex].z) //If min is larger than current
			m_v3Min.z = a_lVectorList[nVertex].z;
		else if (m_v3Max.z < a_lVectorList[nVertex].z)//if max is smaller than current
			m_v3Max.z = a_lVectorList[nVertex].z;
	}

	//with the max and the min we calculate the center
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	m_fRadius = glm::distance(m_v3Center, m_v3Max);

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f;

	m_v3MaxG = m_v3Max;
	m_v3MinG = m_v3Min;
	m_v3CenterG = m_v3Center;
	m_v3HalfWidthG = m_v3HalfWidth;
}
MyBOClass::MyBOClass(MyBOClass const& other)
{
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3CenterG = other.m_v3CenterG;
	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3HalfWidthG = other.m_v3HalfWidthG;

	m_fRadius = other.m_fRadius;

	m_pMeshMngr = other.m_pMeshMngr;
}
MyBOClass& MyBOClass::operator=(MyBOClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyBOClass temp(other);
		Swap(temp);
	}
	return *this;
}
MyBOClass::~MyBOClass() { Release(); };
//Accessors
void MyBOClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	//If there are no changes in the Model Matrix there is no need
	//of doing further calculations
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	//Calculate the vertex that makes the Object
	vector3 v3Corner[8];
	v3Corner[0] = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
	v3Corner[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	v3Corner[2] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	v3Corner[3] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);

	v3Corner[4] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	v3Corner[5] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	v3Corner[6] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	v3Corner[7] = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z);
	//Get vectors in global space
	for (uint nVertex = 0; nVertex < 8; nVertex++)
	{
		v3Corner[nVertex] = vector3(m_m4ToWorld * vector4(v3Corner[nVertex], 1.0f));
	}

	//Get the max and min out of the list
	m_v3MaxG = m_v3MinG = v3Corner[0];
	for (uint nVertex = 1; nVertex < 8; nVertex++)
	{
		if (m_v3MinG.x > v3Corner[nVertex].x) //If min is larger than current
			m_v3MinG.x = v3Corner[nVertex].x;
		else if (m_v3MaxG.x < v3Corner[nVertex].x)//if max is smaller than current
			m_v3MaxG.x = v3Corner[nVertex].x;

		if (m_v3MinG.y > v3Corner[nVertex].y) //If min is larger than current
			m_v3MinG.y = v3Corner[nVertex].y;
		else if (m_v3MaxG.y < v3Corner[nVertex].y)//if max is smaller than current
			m_v3MaxG.y = v3Corner[nVertex].y;

		if (m_v3MinG.z > v3Corner[nVertex].z) //If min is larger than current
			m_v3MinG.z = v3Corner[nVertex].z;
		else if (m_v3MaxG.z < v3Corner[nVertex].z)//if max is smaller than current
			m_v3MaxG.z = v3Corner[nVertex].z;
	}
	m_v3CenterG = (m_v3MinG + m_v3MaxG) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidthG = (m_v3MaxG - m_v3MinG) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterG, m_v3MaxG);
}
float MyBOClass::GetRadius(void) { return m_fRadius; }
matrix4 MyBOClass::GetModelMatrix(void) { return m_m4ToWorld; }
vector3 MyBOClass::GetCenterLocal(void) { return m_v3Center; }
vector3 MyBOClass::GetCenterGlobal(void) { return m_v3CenterG; }
vector3 MyBOClass::GetHalfWidth(void) { return m_v3HalfWidth; }
vector3 MyBOClass::GetHalfWidthG(void) { return m_v3HalfWidthG; }
vector3 MyBOClass::GetMin(void) { return m_v3Min; }
vector3 MyBOClass::GetMax(void) { return m_v3Max; }
vector3 MyBOClass::GetMinG(void) { return m_v3MinG; }
vector3 MyBOClass::GetMaxG(void) { return m_v3MaxG; }
//--- Non Standard Singleton Methods
void MyBOClass::DisplaySphere(vector3 a_v3Color)
{
	m_pMeshMngr->AddSphereToRenderList(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(vector3(m_fRadius * 2.0f)), a_v3Color, WIRE);
}
void MyBOClass::DisplayOriented(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(m_v3HalfWidth * 2.0f), a_v3Color, WIRE);
}
void MyBOClass::DisplayReAlligned(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(IDENTITY_M4, m_v3CenterG) *
		glm::scale(m_v3HalfWidthG * 2.0f), a_v3Color, WIRE);
}
bool MyBOClass::IsColliding(MyBOClass* const a_pOther)
{
	//Get all vectors in global space
	vector3 v3Min = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 v3Max = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 v3MinO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
	vector3 v3MaxO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));

	/*
	Are they colliding?
	For Objects we will assume they are colliding, unless at least one of the following conditions is not met
	*/
	//first check the bounding sphere, if that is not colliding we can guarantee that there are no collision
	if ((m_fRadius + a_pOther->m_fRadius) < glm::distance(m_v3CenterG, a_pOther->m_v3CenterG))
		return false;

	//If the distance was smaller it might be colliding

	bool bColliding = true;

	//Check for X
	if (m_v3MaxG.x < a_pOther->m_v3MinG.x)
		bColliding = false;
	if (m_v3MinG.x > a_pOther->m_v3MaxG.x)
		bColliding = false;

	//Check for Y
	if (m_v3MaxG.y < a_pOther->m_v3MinG.y)
		bColliding = false;
	if (m_v3MinG.y > a_pOther->m_v3MaxG.y)
		bColliding = false;

	//Check for Z
	if (m_v3MaxG.z < a_pOther->m_v3MinG.z)
		bColliding = false;
	if (m_v3MinG.z > a_pOther->m_v3MaxG.z)
		bColliding = false;

	//If bColliding is true check with SAT
	if (bColliding)
	{
		float ra, rb;
		glm::mat3 R, AbsR;

		// Compute rotation matrix expressing b in a�s coordinate frame
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				R[i][j] = glm::dot(localAxes[i], a_pOther->localAxes[j]);

		// Compute translation vector t
		glm::vec3 t = a_pOther->m_v3CenterG - m_v3CenterG;

		// Bring translation into a�s coordinate frame
		t = glm::vec3(glm::dot(t, localAxes[0]), glm::dot(t, localAxes[1]), glm::dot(t, localAxes[2]));

		// Compute common subexpressions. Add in an epsilon term to
		// counteract arithmetic errors when two edges are parallel and
		// their cross product is (near) null (see text for details)
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				AbsR[i][j] = abs(R[i][j]) + .001;

		// Test axes L = A0, L = A1, L = A2
		for (int i = 0; i < 3; i++) {
			ra = m_v3HalfWidthG[i];
			rb = a_pOther->m_v3HalfWidthG[0] * AbsR[i][0] + a_pOther->m_v3HalfWidthG[1] * AbsR[i][1] + a_pOther->m_v3HalfWidthG[2] * AbsR[i][2];
			if (abs(t[i]) > ra + rb) return 0;
		}

		// Test axes L = B0, L = B1, L = B2
		for (int i = 0; i < 3; i++) {
			ra = m_v3HalfWidthG[0] * AbsR[0][i] + m_v3HalfWidthG[1] * AbsR[1][i] + m_v3HalfWidthG[2] * AbsR[2][i];
			rb = a_pOther->m_v3HalfWidthG[i];
			if (abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb) return 0;
		}

		// Test axis L = A0 x B0
		ra = m_v3HalfWidthG[1] * AbsR[2][0] + m_v3HalfWidthG[2] * AbsR[1][0];
		rb = a_pOther->m_v3HalfWidthG[1] * AbsR[0][2] + a_pOther->m_v3HalfWidthG[2] * AbsR[0][1];
		if (abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb) return 0;

		// Test axis L = A0 x B1
		ra = m_v3HalfWidthG[1] * AbsR[2][1] + m_v3HalfWidthG[2] * AbsR[1][1];
		rb = a_pOther->m_v3HalfWidthG[0] * AbsR[0][2] + a_pOther->m_v3HalfWidthG[2] * AbsR[0][0];
		if (abs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb) return 0;

		// Test axis L = A0 x B2
		ra = m_v3HalfWidthG[1] * AbsR[2][2] + m_v3HalfWidthG[2] * AbsR[1][2];
		rb = a_pOther->m_v3HalfWidthG[0] * AbsR[0][1] + a_pOther->m_v3HalfWidthG[1] * AbsR[0][0];
		if (abs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb) return 0;

		// Test axis L = A1 x B0
		ra = m_v3HalfWidthG[0] * AbsR[2][0] + m_v3HalfWidthG[2] * AbsR[0][0];
		rb = a_pOther->m_v3HalfWidthG[1] * AbsR[1][2] + a_pOther->m_v3HalfWidthG[2] * AbsR[1][1];
		if (abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb) return 0;

		// Test axis L = A1 x B1
		ra = m_v3HalfWidthG[0] * AbsR[2][1] + m_v3HalfWidthG[2] * AbsR[0][1];
		rb = a_pOther->m_v3HalfWidthG[0] * AbsR[1][2] + a_pOther->m_v3HalfWidthG[2] * AbsR[1][0];
		if (abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb) return 0;

		// Test axis L = A1 x B2
		ra = m_v3HalfWidthG[0] * AbsR[2][2] + m_v3HalfWidthG[2] * AbsR[0][2];
		rb = a_pOther->m_v3HalfWidthG[0] * AbsR[1][1] + a_pOther->m_v3HalfWidthG[1] * AbsR[1][0];
		if (abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb) return 0;

		// Test axis L = A2 x B0
		ra = m_v3HalfWidthG[0] * AbsR[1][0] + m_v3HalfWidthG[1] * AbsR[0][0];
		rb = a_pOther->m_v3HalfWidthG[1] * AbsR[2][2] + a_pOther->m_v3HalfWidthG[2] * AbsR[2][1];
		if (abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb) return 0;

		// Test axis L = A2 x B1
		ra = m_v3HalfWidthG[0] * AbsR[1][1] + m_v3HalfWidthG[1] * AbsR[0][1];
		rb = a_pOther->m_v3HalfWidthG[0] * AbsR[2][2] + a_pOther->m_v3HalfWidthG[2] * AbsR[2][0];
		if (abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb) return 0;

		// Test axis L = A2 x B2
		ra = m_v3HalfWidthG[0] * AbsR[1][2] + m_v3HalfWidthG[1] * AbsR[0][2];
		rb = a_pOther->m_v3HalfWidthG[0] * AbsR[2][1] + a_pOther->m_v3HalfWidthG[1] * AbsR[2][0];
		if (abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb) return 0;

		//If no tests succeed, they are intersecting
		bColliding = true;

		return bColliding;
	}
}