#include "stdafx.h"
#include "Scene.h"

CScene::CScene() {

}

CScene::~CScene() {

}

void CScene::BuildObjects() {
	
	//CGameObject* pTankModelGreen = CGameObject::LoadGeometryFromFile("Model/GreenTank.bin");
	//CGameObject* pTankModelRed = CGameObject::LoadGeometryFromFile("Model/RedTank.bin");
	
	m_nTankObjects = 3;
	m_ppTankObjects = new CTankObject * [m_nTankObjects];

	CGameObject* pTankModel = CGameObject::LoadGeometryFromFile("Model/GreenTank.bin");
	CTankObject* pTankObject = NULL;

	pTankObject = new CTankObject();
	pTankObject->SetChild(pTankModel, true);
	pTankObject->OnInitialize();
	pTankObject->SetPosition(XMFLOAT3(13.0f, 0.0f, -5.0f));
	pTankObject->SetScaleVar(1.0f, 1.0f, 1.0f);
	pTankObject->Rotate(0.0f, -90.0f, 0.0f);
	pTankObject->SetFriction(40.0f);
	pTankObject->SetMaxVelocityXZ(12.0f);
	pTankObject->SetAccelSpeedXZ(70.0f);
	pTankObject->SetSpeedRotateY(180.0f);
	pTankObject->BuildBullets();
	m_ppTankObjects[0] = pTankObject;


	pTankObject = new CTankObject();
	pTankObject->SetChild(pTankModel, true);
	pTankObject->OnInitialize();
	pTankObject->SetPosition(XMFLOAT3(-3.0f, 0.0f, 30.0f));
	pTankObject->SetScaleVar(1.0f, 1.0f, 1.0f);
	pTankObject->Rotate(0.0f, 180.0f, 0.0f);
	pTankObject->SetFriction(40.0f);
	pTankObject->SetMaxVelocityXZ(12.0f);
	pTankObject->SetAccelSpeedXZ(70.0f);
	pTankObject->SetSpeedRotateY(180.0f);
	pTankObject->BuildBullets();
	m_ppTankObjects[1] = pTankObject;


	pTankObject = new CTankObject();
	pTankObject->SetChild(pTankModel, true);			
	pTankObject->OnInitialize();
	pTankObject->SetPosition(XMFLOAT3(-15.0f, 0.0f, -3.0f));	
	pTankObject->SetScaleVar(1.0f, 1.0f, 1.0f);
	pTankObject->Rotate(0.0f, 90.0f, 0.0f);					
	pTankObject->SetFriction(40.0f);
	pTankObject->SetMaxVelocityXZ(12.0f);
	pTankObject->SetAccelSpeedXZ(70.0f);
	pTankObject->SetSpeedRotateY(180.0f);
	pTankObject->BuildBullets();
	m_ppTankObjects[2] = pTankObject;
	
    // ¸ðµ¨ ºÒ·¯¿À±â

    map<char*, char*> modelDictionary;

    modelDictionary["terrain"] = "Model/Terrain.bin";
    modelDictionary["cliff"] = "Model/Cliff.bin";
    modelDictionary["concrete"] = "Model/Concrete.bin";
    modelDictionary["dunes01"] = "Model/Dunes01.bin";
    modelDictionary["dunes02"] = "Model/Dunes02.bin";
    modelDictionary["cow"] = "Model/Cow.bin";
    modelDictionary["rocks01"] = "Model/Rocks01.bin";
    modelDictionary["rocks02"] = "Model/Rocks02.bin";
    modelDictionary["rocks03"] = "Model/Rocks03.bin";
    modelDictionary["column01"] = "Model/Column01.bin";
    modelDictionary["column02"] = "Model/Column02.bin";
    modelDictionary["tree"] = "Model/Tree.bin";
    modelDictionary["palmtree"] = "Model/PalmTree.bin";
    modelDictionary["cactus"] = "Model/Cactus.bin";
    modelDictionary["building01"] = "Model/Building01.bin";
    modelDictionary["building02"] = "Model/Building02.bin";
    modelDictionary["radar"] = "Model/Radar.bin";
    modelDictionary["oilstorage"] = "Model/OilStorage.bin";
    modelDictionary["pumpjack"] = "Model/PumpJack.bin";
    modelDictionary["refinery"] = "Model/Refinery.bin";
    modelDictionary["bustedtank"] = "Model/BustedTank.bin";
    modelDictionary["crater01"] = "Model/Crater01.bin";
    modelDictionary["ruins01"] = "Model/Ruins01.bin";
    modelDictionary["helipad"] = "Model/Helipad.bin";
    modelDictionary["grape"] = "Model/Grape.bin";
    modelDictionary["apple"] = "Model/Apple.bin";
    modelDictionary["cherry"] = "Model/Cherry.bin";

    struct
    {
        char* pstrModelObject;
        XMFLOAT3 position;
        XMFLOAT3 rotation;
        XMFLOAT3 scale;
        bool isCollisionsPossible = false;
        bool isItem = false;
        int iTemType = 0;
    } formats[] = {
       { "terrain", XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.05f, 1.05f, 1.05f) },
       { "cliff", XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
       { "cliff", XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 90.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
       { "cliff", XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 180.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
       { "cliff", XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 270.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },

       { "concrete", XMFLOAT3(7.37f, 0.0f, 22.34f), XMFLOAT3(0.0f, -142.95, 0.0f), XMFLOAT3(1.35f, 1.35f, 1.35f) },
       { "concrete", XMFLOAT3(9.2f, 0.0f, 11.3f), XMFLOAT3(0.0f, 160.81f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
       { "concrete", XMFLOAT3(-6.36f, 0.0f, 12.06f), XMFLOAT3(0.0f, -8.72f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
       { "concrete", XMFLOAT3(35.9f, 0.0f, -23.7f), XMFLOAT3(0.0f, 15.298f, 0.0f), XMFLOAT3(1.35f, 1.35f, 1.35f) },
       { "concrete", XMFLOAT3(14.9f, 0.0f, -22.1f), XMFLOAT3(0.0f, -128.08f, 0.0f), XMFLOAT3(1.35f, 1.35f, 1.35f) },
       { "concrete", XMFLOAT3(9.2f, 0.0f, -33.3f), XMFLOAT3(0.0f, -47.36f, 0.0f), XMFLOAT3(1.35f, 1.35f, 1.35f) },
       { "concrete", XMFLOAT3(15.7f, 0.0f, -35.8f), XMFLOAT3(0.0f, 15.29f, 0.0f), XMFLOAT3(1.35f, 1.35f, 1.35f) },
       { "concrete", XMFLOAT3(-2.07f, 0.0f, 29.86f), XMFLOAT3(0.0f, 18.403f, 0.0f), XMFLOAT3(1.35f, 1.35f, 1.35f) },
       { "concrete", XMFLOAT3(-24.9f, 0.0f, -31.33f), XMFLOAT3(0.0f, -50.106f, 0.0f), XMFLOAT3(1.35f, 1.35f, 1.35f) },

       { "dunes01", XMFLOAT3(-15.91f, 0.0f, -2.97f), XMFLOAT3(0.0f, -81.36f, 0.0f), XMFLOAT3(0.66f, 0.41f, 0.66f) },
       { "dunes01", XMFLOAT3(-19.6f, 0.0f, 6.9f), XMFLOAT3(0.0f, 114.22f, 0.0f), XMFLOAT3(0.77f, 0.32f, 0.77f) },
       { "dunes01", XMFLOAT3(-20.2f, 0.0f, 12.5f), XMFLOAT3(0.0f, 95.79f, 0.0f), XMFLOAT3(0.65f, 0.48f, 0.65f) },
       { "dunes01", XMFLOAT3(-33.78f, 0.0f, 0.82f), XMFLOAT3(0.0f, -50.37f, 0.0f), XMFLOAT3(0.67f, 0.41f, 0.67f) },
       { "dunes01", XMFLOAT3(25.58f, 0.0f, 15.32f), XMFLOAT3(0.0f, -76.36f, 0.0f), XMFLOAT3(0.66f, 0.21f, 0.66f) },
       { "dunes01", XMFLOAT3(-26.5f, 0.0f, 23.4f), XMFLOAT3(0.0f, -79.24f, 0.0f), XMFLOAT3(0.65f, 0.48f, 0.65f) },
       { "dunes01", XMFLOAT3(-30.4f, 0.0f, 17.4f), XMFLOAT3(0.0f, 149.32f, 0.0f), XMFLOAT3(0.77f, 0.32f, 0.77f) },
       { "dunes01", XMFLOAT3(18.73f, 0.0f, 17.67f), XMFLOAT3(0.0f, 65.71f, 0.0f), XMFLOAT3(0.77f, 0.32f, 0.77f) },
       { "dunes01", XMFLOAT3(-7.17f, 0.0f, -12.15f), XMFLOAT3(0.0f, -81.36f, 0.0f), XMFLOAT3(0.66f, 0.53f, 0.66f) },
       { "dunes01", XMFLOAT3(23.2f, 0.0f, 32.7f), XMFLOAT3(0.0f, 104.55f, 0.0f), XMFLOAT3(0.65f, 0.29f, 0.65f) },
       { "dunes01", XMFLOAT3(-31.4f, 0.0f, -16.17f), XMFLOAT3(0.0f, 74.21f, 0.0f), XMFLOAT3(0.77f, 0.32f, 0.77f) },
       { "dunes01", XMFLOAT3(27.2f, 0.0f, -5.61f), XMFLOAT3(0.0f, 147.17f, 0.0f), XMFLOAT3(0.66f, 0.53f, 0.66f) },
       { "dunes01", XMFLOAT3(10.97f, 0.0f, -0.58f), XMFLOAT3(0.0f, -44.98f, 0.0f), XMFLOAT3(0.66f, 0.41f, 0.66f) },
       { "dunes02", XMFLOAT3(17.78f, 0.0f, 28.22f), XMFLOAT3(0.0f, -66.98f, 0.0f), XMFLOAT3(1.0f, 0.32f, 1.0f) },
       { "dunes02", XMFLOAT3(-21.7f, 0.0f, 18.9f), XMFLOAT3(0.0f, -71.09f, 0.0f), XMFLOAT3(1.0f, 0.53f, 1.0f) },
       { "dunes02", XMFLOAT3(-26.15f, 0.0f, -11.79f), XMFLOAT3(0.0f, 122.46f, 0.0f), XMFLOAT3(1.0f, 0.54f, 1.0f) },
       { "dunes02", XMFLOAT3(-37.19f, 0.0f, 5.68f), XMFLOAT3(0.0f, -46.0f, 0.0f), XMFLOAT3(1.0f, 0.54f, 1.0f) },
       { "dunes02", XMFLOAT3(-37.0f, 0.0f, 16.0f), XMFLOAT3(0.0f, 124.13f, 0.0f), XMFLOAT3(1.0f, 0.54f, 1.0f) },
       { "dunes02", XMFLOAT3(-27.1f, 0.0f, -5.1f), XMFLOAT3(0.0f, -52.94f, 0.0f), XMFLOAT3(1.0f, 0.7f, 1.0f) },
       { "dunes02", XMFLOAT3(-11.79f, 0.0f, -12.53f), XMFLOAT3(0.0f, 12.47f, 0.0f), XMFLOAT3(1.0f, 0.54f, 1.0f) },
       { "dunes02", XMFLOAT3(-6.8f, 0.0f, -29.0f), XMFLOAT3(0.0f, -52.17f, 0.0f), XMFLOAT3(1.0f, 0.54f, 1.0f) },
       { "cow", XMFLOAT3(-26.87f, 0.0f, 9.2f), XMFLOAT3(0.0f, 105.9f, 0.0f), XMFLOAT3(1.25f, 1.25f, 1.25f) },
       { "cow", XMFLOAT3(-2.96f, -0.18f, -16.1f), XMFLOAT3(16.51f, 116.39f, -4.54f), XMFLOAT3(1.25f, 1.25f, 1.25f) },

       { "rocks01", XMFLOAT3(-12.39f, 0.0f, 33.76f), XMFLOAT3(0.0f, 64.05f, 0.0f), XMFLOAT3(0.7f, 0.7f, 0.7f), true},
       { "rocks01", XMFLOAT3(36.93f, 0.0f, -3.7f), XMFLOAT3(0.0f, 138.52f, 0.0f), XMFLOAT3(0.73f, 0.73f, 0.73f), true },
       { "rocks01", XMFLOAT3(-17.3f, 0.0f, -11.91f), XMFLOAT3(0.0f, -169.09f, 0.0f), XMFLOAT3(0.7f, 0.7f, 0.7f), true },
       { "rocks01", XMFLOAT3(-15.21f, 0.0f, -22.2f), XMFLOAT3(0.0f, 5.88f, 0.0f), XMFLOAT3(0.43f, 0.43f, 0.43f), true },
       { "rocks01", XMFLOAT3(12.36f, 0.0f, 4.82f), XMFLOAT3(0.0f, 136.24f, 0.0f), XMFLOAT3(0.7f, 0.7f, 0.7f), true },
       { "rocks01", XMFLOAT3(15.91f, 0.0f, 4.87f), XMFLOAT3(0.0f, 153.216f, 0.0f), XMFLOAT3(0.59f, 0.59f, 0.59f), true },
       { "rocks02", XMFLOAT3(-2.01f, 0.0f, -15.59f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "rocks02", XMFLOAT3(35.31f, 0.0f, -7.3f), XMFLOAT3(0.0f, 116.22f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "rocks02", XMFLOAT3(-18.94f, 0.0f, -14.76f), XMFLOAT3(0.0f, 115.05f, 0.0f), XMFLOAT3(0.68f, 0.68f, 0.68f), true },
       { "rocks02", XMFLOAT3(-16.86f, 0.0f, 29.89f), XMFLOAT3(0.0f, -100.76f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "rocks02", XMFLOAT3(-5.93f, 0.0f, -37.44f), XMFLOAT3(0.0f, -175.0f, 0.0f), XMFLOAT3(0.84f, 0.84f, 0.84f), true },
       { "rocks02", XMFLOAT3(13.76f, 0.0f, 1.82f), XMFLOAT3(0.0f, 60.38f, 0.0f), XMFLOAT3(0.68f, 0.68f, 0.68f), true },
       { "rocks03", XMFLOAT3(40.42f, 0.0f, -3.06f), XMFLOAT3(0.0f, 33.38f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "rocks03", XMFLOAT3(-20.07f, 0.0f, -19.91f), XMFLOAT3(0.0f, -27.04f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "rocks03", XMFLOAT3(-0.13f, 0.08f, 41.97f), XMFLOAT3(3.23f, -22.52f, -176.37f), XMFLOAT3(0.91f, 0.91f, 0.91f), true },
       { "rocks03", XMFLOAT3(-20.61f, 0.03f, 43.58f), XMFLOAT3(0.0f, 155.44f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "rocks03", XMFLOAT3(33.22f, 0.0f,28.62f), XMFLOAT3(-4.37f, 88.19f, -15.89f), XMFLOAT3(0.54f, 0.54f, 0.54f), true },
       { "rocks03", XMFLOAT3(31.79f, 0.0f, 22.55f), XMFLOAT3(-4.37f, -133.54f, -15.89f), XMFLOAT3(0.54f, 0.54f, 0.54f), true },
       { "column01", XMFLOAT3(37.74f, 0.0f, -37.33f), XMFLOAT3(0.0f, 38.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "column01", XMFLOAT3(-35.77f, 0.0f, 32.06f), XMFLOAT3(0.0f, 12.13f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "column01", XMFLOAT3(31.89f, 0.0f, 11.05f), XMFLOAT3(0.0f, 6.87f, 0.0f), XMFLOAT3(0.85f, 0.85f, 0.85f), true },
       { "column02", XMFLOAT3(-16.57f, 0.0f, -29.33f), XMFLOAT3(0.0f, -8.5f, 0.0f), XMFLOAT3(0.8f, 0.8f, 0.8f), true },
       { "column02", XMFLOAT3(-18.16f, -0.7f, 37.9f), XMFLOAT3(0.0f, 22.34f, 0.0f), XMFLOAT3(0.94f, 0.94f, 0.94f), true },
       { "column02", XMFLOAT3(24.6f, 0.05f, 39.67f), XMFLOAT3(0.0f, -148.15f, 0.0f), XMFLOAT3(0.84f, 0.84f, 0.84f), true },

       { "tree", XMFLOAT3(-1.74f, 0.0f, -17.99f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "tree", XMFLOAT3(-3.07f, 0.0f, -12.44f), XMFLOAT3(0.0f, -63.4f, 0.0f), XMFLOAT3(0.73f, 0.73f, 0.73f), true },
       { "tree", XMFLOAT3(-3.1f, 0.0f, 36.77f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "tree", XMFLOAT3(1.78f, 0.0f, 41.66f), XMFLOAT3(0.0f, -113.67f, 0.0f), XMFLOAT3(0.9f, 0.9f, 0.9f), true },
       { "tree", XMFLOAT3(13.08f, 0.0f, 36.3f), XMFLOAT3(8.85f, -178.72f, 0.2f), XMFLOAT3(0.81f, 0.81f, 0.81f), true },
       { "tree", XMFLOAT3(11.7f, 0.09f, 37.28f), XMFLOAT3(0.0f, -103.53f, 0.0f), XMFLOAT3(1.24f, 1.24f, 1.24f), true },
       { "tree", XMFLOAT3(14.71f, 0.0f, 4.38f), XMFLOAT3(0.0f, -71.73f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "tree", XMFLOAT3(-2.3f, 0.0f, 43.87f), XMFLOAT3(-6.33f, 37.85f, -4.9f), XMFLOAT3(0.8f, 0.8f, 0.8f), true },
       { "tree", XMFLOAT3(-11.48f, 0.09f, 30.93f), XMFLOAT3(0.0f, -38.9f, 0.0f), XMFLOAT3(1.24f, 1.24f, 1.24f), true },
       { "tree", XMFLOAT3(42.76f, 0.09f, 26.14f), XMFLOAT3(0.0f, -103.53f, 0.0f), XMFLOAT3(1.05f, 1.05f, 1.05f), true },
       { "palmtree", XMFLOAT3(-8.7f, 0.0f, -37.01f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "palmtree", XMFLOAT3(-7.59f, 0.0f, -38.74f), XMFLOAT3(-1.69f, -48.57f, 11.72f), XMFLOAT3(0.71f, 0.71f, 0.71f), true },
       { "palmtree", XMFLOAT3(-20.45f, 0.0f, -19.21f), XMFLOAT3(0.0f, -79.44f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "palmtree", XMFLOAT3(-20.69f, 0.0f, 20.46f), XMFLOAT3(-7.12f, -45.59f, 7.59f), XMFLOAT3(0.73f, 0.73f, 0.73f), true },
       { "palmtree", XMFLOAT3(-18.08f, 0.0f, -13.94f), XMFLOAT3(11.04f, -46.24f, -10.93f), XMFLOAT3(0.76f, 0.76f, 0.76f), true },
       { "palmtree", XMFLOAT3(-12.77f, 0.0f, -31.07f), XMFLOAT3(-7.12f, -11.56f, 7.59f), XMFLOAT3(0.73f, 0.73f, 0.73f), true },
       { "palmtree", XMFLOAT3(-32.86f, 0.0f, 28.88f), XMFLOAT3(-1.69, -48.57f, 11.72f), XMFLOAT3(0.79f, 0.79f, 0.79f), true },
       { "palmtree", XMFLOAT3(-39.53f, -0.09f, 29.14f), XMFLOAT3(3.47f, 48.29f, -11.03f), XMFLOAT3(0.64f, 0.64f, 0.64f), true },
       { "palmtree", XMFLOAT3(-35.9f, -0.09f, 27.95f), XMFLOAT3(-19.30f, -51.82f, 4.37f), XMFLOAT3(0.52f, 0.52f, 0.52f), true },
       { "palmtree", XMFLOAT3(-19.76f, 0.0f, -29.22f), XMFLOAT3(0.0f, -147.945f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },

       { "cactus", XMFLOAT3(33.31f, 0.0f, -26.29f), XMFLOAT3(0.0f, -100.88f, 0.0f), XMFLOAT3(0.55f, 0.55f, 0.55f), true },
       { "cactus", XMFLOAT3(39.48f, 0.0f, -1.66f), XMFLOAT3(0.0f, 114.66f, 0.0f), XMFLOAT3(0.66f, 0.66f, 0.66f), true },
       { "cactus", XMFLOAT3(20.51f, 0.0f, -46.71f), XMFLOAT3(0.0f, -115.93f, 0.0f), XMFLOAT3(0.52f, 0.52f, 0.52f), true },
       { "cactus", XMFLOAT3(40.92f, 0.0f, -34.46f), XMFLOAT3(0.0f, -28.88f, 0.0f), XMFLOAT3(0.78f, 0.78f, 0.78f), true },

       { "building01", XMFLOAT3(8.1f, 0.0f, 7.4f), XMFLOAT3(0.0f, -80.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true }, //87
       { "building01", XMFLOAT3(12.0f, 0.0f, 14.0f), XMFLOAT3(0.0f, -171.1f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true},
       { "building01", XMFLOAT3(0.45f, 0.0f, 35.71f), XMFLOAT3(0.0f, 96.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "building01", XMFLOAT3(-22.53f, 0.0f, -25.22f), XMFLOAT3(0.0f, -63.78f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "building02", XMFLOAT3(1.34f, 0.0f, 10.16f), XMFLOAT3(0.0f, 278.91f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "building02", XMFLOAT3(-5.66f, 0.0f, 12.26f), XMFLOAT3(0.0f, -81.24f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "building02", XMFLOAT3(8.56f, 0.0f, 36.32f), XMFLOAT3(0.0f, -83.75f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "radar", XMFLOAT3(6.97f, 0.0f, 21.34f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },

       { "oilstorage", XMFLOAT3(29.9f, 0.0f, -33.4f), XMFLOAT3(0.0f, -174.2f, 0.0f), XMFLOAT3(1.75f, 1.75f, 1.75f), true },
       { "oilstorage", XMFLOAT3(35.8f, 0.0f, -24.1f), XMFLOAT3(0.0f, -167.29f, 0.0f), XMFLOAT3(1.75f, 1.75f, 1.75f), true },
       { "pumpjack", XMFLOAT3(29.51f, 0.0f, -12.67f), XMFLOAT3(0.0f, 30.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "pumpjack", XMFLOAT3(28.08f, 0.0f, -18.83f), XMFLOAT3(0.0f, 30.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "pumpjack", XMFLOAT3(22.94f, 0.0f, -15.17f), XMFLOAT3(0.0f, 30.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "refinery", XMFLOAT3(13.9f, 0.0f, -27.0f), XMFLOAT3(0.0f, -84.56f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },

       { "bustedtank", XMFLOAT3(26.23f, 0.0f, -21.90f), XMFLOAT3(0.0f, -150.5f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "crater01", XMFLOAT3(32.93f, 0.1f, 25.86f), XMFLOAT3(0.0f, 5.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
       { "crater01", XMFLOAT3(31.19f, 0.1f, 19.8f), XMFLOAT3(0.0f, 81.17f, 0.0f), XMFLOAT3(0.41f, 0.41f, 0.41f) },
       { "crater01", XMFLOAT3(25.56f, 0.1f, 23.68f), XMFLOAT3(0.0f, 5.64f, 0.0f), XMFLOAT3(0.44f, 0.44f, 0.44f) },
       { "crater01", XMFLOAT3(33.22f, 0.1f, 34.4f), XMFLOAT3(0.0f, 31.03f, 0.0f), XMFLOAT3(0.44f, 0.44f, 0.44f) },
       { "ruins01", XMFLOAT3(31.5f, 0.03f, 35.20f), XMFLOAT3(0.0f, 112.78f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), true },
       { "ruins01", XMFLOAT3(37.86f, 0.03f, 24.48f), XMFLOAT3(0.0f, -155.24f, 0.0f), XMFLOAT3(1.28f, 1.28f, 1.28f), true },


       /*{ "grape", XMFLOAT3(13.0f, 1.5f, -10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(4.0f, 4.0f, 4.0f), true, true, 2},
       { "apple", XMFLOAT3(13.0f, 1.5f, -7.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(4.0f, 4.0f, 4.0f), true, true, 1},
       { "cherry", XMFLOAT3(13.0f, 1.5f, -5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(4.0f, 4.0f, 4.0f), true, true, 3},
       { "grape", XMFLOAT3(13.0f, 1.5f, -10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(4.0f, 4.0f, 4.0f), true, true, 2},
       { "apple", XMFLOAT3(13.0f, 1.5f, -7.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(4.0f, 4.0f, 4.0f), true, true, 1},
       { "cherry", XMFLOAT3(13.0f, 1.5f, -5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(4.0f, 4.0f, 4.0f), true, true, 3}*/
    };

    m_nGameObjects = sizeof(formats) / sizeof(formats[0]);
    m_ppGameObjects = new CGameObject * [m_nGameObjects];

    for (int i = 0; i < m_nGameObjects; i++)
    {
        CGameObject* pGameObject = NULL;
        CGameObject* pNewModel = NULL;

        /*if (formats[i].isItem) pGameObject = new CItemObject(formats[i].iTemType);
        else*/ pGameObject = new CGameObject();
        pNewModel = CGameObject::LoadGeometryFromFile(modelDictionary[formats[i].pstrModelObject]);

        pGameObject->SetChild(pNewModel, true);
        pGameObject->SetPosition(formats[i].position);
        pGameObject->Rotate(formats[i].rotation.x, formats[i].rotation.y, formats[i].rotation.z);
        pGameObject->SetScale(formats[i].scale.x, formats[i].scale.y, formats[i].scale.z);
        pGameObject->m_bIsCollisionsPossible = formats[i].isCollisionsPossible;

        m_ppGameObjects[i] = pGameObject;
    }
}

void CScene::ReleaseObjects() {

}

void CScene::AnimateObjects(float fTimeElapsed) {
	m_fElapsedTime = fTimeElapsed;
	for (int i = 0; i < m_nGameObjects; ++i) m_ppGameObjects[i]->Animate(fTimeElapsed, NULL);
	for (int i = 0; i < m_nTankObjects; ++i) m_ppTankObjects[i]->Animate(fTimeElapsed, NULL);

	if (!m_bIsRoundOver)CheckTankObjectByBulletCollisions();
    CheckObjectByBulletCollisions();
}

bool CScene::ProcessInput(DWORD dwDirection, bool bIsRotateLeft, bool bIsRotateRight, bool bIsFire, int nTankIndex, float fTimeElapsed)
{

	if (!m_ppTankObjects[nTankIndex]->GetDead())
	{
		if (bIsRotateLeft) m_ppTankObjects[nTankIndex]->Rotate(0.0f, -m_ppTankObjects[nTankIndex]->GetSpeedRotateY() * fTimeElapsed, 0.0f);
		if (bIsRotateRight) m_ppTankObjects[nTankIndex]->Rotate(0.0f, m_ppTankObjects[nTankIndex]->GetSpeedRotateY() * fTimeElapsed, 0.0f);
		if (bIsFire) m_ppTankObjects[nTankIndex]->FireBullet();
		if (dwDirection) m_ppTankObjects[nTankIndex]->Move(dwDirection, m_ppTankObjects[nTankIndex]->GetAccelSpeedXZ() * fTimeElapsed, true);
	}
	m_ppTankObjects[nTankIndex]->Update(fTimeElapsed);

	return(true);
}

void CScene::CheckTankObjectByBulletCollisions()
{
	CBulletObject** ppBullets = NULL;
	for (int i = 0; i < m_nTankObjects; i++)
	{
		ppBullets = m_ppTankObjects[i]->m_ppBullets;
		for (int j = 0; j < m_nTankObjects; j++)
		{
			if (i == j) continue;
			for (int k = 0; k < m_ppTankObjects[i]->m_nBullets; k++)
			{
				if (ppBullets[k]->GetActive())
				{
					if (Vector3::Distance(m_ppTankObjects[j]->GetPosition(), ppBullets[k]->GetPosition()) < 2.0f)
					{
						m_bIsRoundOver = m_ppTankObjects[j]->DamagedByBullet(ppBullets[k]);
						ppBullets[k]->SetActive(false);
					}
				}
			}
		}
	}
}

void CScene::CheckObjectByBulletCollisions()
{
    CBulletObject** ppBullets = NULL;
    for (int i = 0; i < m_nTankObjects; i++)
    {
        ppBullets = m_ppTankObjects[i]->m_ppBullets;
        for (int j = 0; j < m_nGameObjects; j++)
        {
            if (!m_ppGameObjects[j]->m_bIsCollisionsPossible) continue;
            if (m_ppGameObjects[j]->m_bIsItem) continue;
            for (int k = 0; k < m_ppTankObjects[i]->m_nBullets; k++)
            {
                if (ppBullets[k]->GetActive())
                {
                    if (m_ppGameObjects[j]->m_pChild->m_xmOOBB.Intersects(ppBullets[k]->m_pChild->m_xmOOBB))//m_ppGameObjects[j]->HierarchyIntersects(ppBullets[k]))
                    {
                        ppBullets[k]->SetActive(false);
                        //cout << j << "¿Í " << i << "ÅÊÅ©ÀÇ " << k << "¹øÂ° ÃÑ¾Ë Ãæµ¹" << endl;
                    }
                }
            }
        }
    }
}