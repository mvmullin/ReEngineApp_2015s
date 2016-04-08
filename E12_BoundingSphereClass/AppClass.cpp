#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("MyBoundingSphereClass example"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");

	// Steve
	std::vector<vector3> listOfVertex = m_pMeshMngr->GetVertexList("Steve");
	uint nCount = listOfVertex.size();
	vector3 v3Min;
	vector3 v3Max;
	if(nCount>0)
	{ 
		v3Min = listOfVertex[0];
		v3Max = listOfVertex[0];
	}
	
	for (uint i = 0; i < nCount; i++)
	{
		// Check X
		if (listOfVertex[i].x < v3Min.x)
			v3Min.x = listOfVertex[i].x;
		else if (listOfVertex[i].x > v3Max.x)
			v3Max.x = listOfVertex[i].x;
		// Check Y
		if (listOfVertex[i].y < v3Min.y)
			v3Min.y = listOfVertex[i].y;
		else if (listOfVertex[i].y > v3Max.y)
			v3Max.y = listOfVertex[i].y;
		// Check Z
		if (listOfVertex[i].z < v3Min.z)
			v3Min.z = listOfVertex[i].z;
		else if (listOfVertex[i].z > v3Max.z)
			v3Max.z = listOfVertex[i].z;
	}
	m_v3Center = (v3Min + v3Max) / 2.0f;
	float fRadius = glm::distance(m_v3Center, v3Max);

	m_pSphere1 = new PrimitiveClass();
	m_pSphere1->GenerateSphere(fRadius, 5, REGREEN);

	// Creeper
	listOfVertex = m_pMeshMngr->GetVertexList("Creeper");
	nCount = listOfVertex.size();
	v3Min;
	v3Max;
	if (nCount>0)
	{
		v3Min = listOfVertex[0];
		v3Max = listOfVertex[0];
	}

	for (uint i = 0; i < nCount; i++)
	{
		// Check X
		if (listOfVertex[i].x < v3Min.x)
			v3Min.x = listOfVertex[i].x;
		else if (listOfVertex[i].x > v3Max.x)
			v3Max.x = listOfVertex[i].x;
		// Check Y
		if (listOfVertex[i].y < v3Min.y)
			v3Min.y = listOfVertex[i].y;
		else if (listOfVertex[i].y > v3Max.y)
			v3Max.y = listOfVertex[i].y;
		// Check Z
		if (listOfVertex[i].z < v3Min.z)
			v3Min.z = listOfVertex[i].z;
		else if (listOfVertex[i].z > v3Max.z)
			v3Max.z = listOfVertex[i].z;
	}
	m_v3Center2 = (v3Min + v3Max) / 2.0f;
	fRadius = glm::distance(m_v3Center2, v3Max);

	m_pSphere2 = new PrimitiveClass();
	m_pSphere2->GenerateSphere(fRadius, 5, REGREEN);
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	bool bAreColliding = false;

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	if (bAreColliding)
		m_pMeshMngr->PrintLine("They are colliding!!! >_<", RERED);
	else
		m_pMeshMngr->PrintLine("They are not colliding!!! =)", RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Model = m_pMeshMngr->GetModelMatrix("Steve");
	m4Model *= glm::translate(m_v3Center);

	m_pSphere1->Render(m4Projection, m4View, m4Model);

	m4Model = m_pMeshMngr->GetModelMatrix("Creeper");
	m4Model *= glm::translate(m_v3Center2);
	m_pSphere2->Render(m4Projection, m4View, m4Model);
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	if (m_pSphere1 != nullptr)
	{
		delete m_pSphere1;
		m_pSphere1 = nullptr;
	}

	if (m_pSphere2 != nullptr)
	{
		delete m_pSphere2;
		m_pSphere2 = nullptr;
	}
	super::Release(); //release the memory of the inherited fields
}