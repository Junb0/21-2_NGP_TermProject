
#include "stdafx.h"
#include "Mesh.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
//
CMeshLoadInfo::~CMeshLoadInfo()
{
	if (m_pxmf3Positions) delete[] m_pxmf3Positions;
	if (m_pxmf4Colors) delete[] m_pxmf4Colors;
	if (m_pxmf3Normals) delete[] m_pxmf3Normals;

	if (m_pnIndices) delete[] m_pnIndices;

	if (m_pnSubSetIndices) delete[] m_pnSubSetIndices;

	for (int i = 0; i < m_nSubMeshes; i++) if (m_ppnSubSetIndices[i]) delete[] m_ppnSubSetIndices[i];
	if (m_ppnSubSetIndices) delete[] m_ppnSubSetIndices;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
CMeshFromFile::CMeshFromFile(CMeshLoadInfo* pMeshInfo)
{
	m_xmOOBB = BoundingOrientedBox(pMeshInfo->m_xmf3AABBCenter, pMeshInfo->m_xmf3AABBExtents, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	TCHAR pstrDebug[256] = { 0 };
	_stprintf_s(pstrDebug, 256, _T("(OOBB: %f %f %f, %f %f %f)\n"),
		m_xmOOBB.Center.x, m_xmOOBB.Center.y, m_xmOOBB.Center.z,
		m_xmOOBB.Extents.x, m_xmOOBB.Extents.y, m_xmOOBB.Extents.z
	);
	OutputDebugString(pstrDebug);
}

CMeshFromFile::~CMeshFromFile()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
CMeshIlluminatedFromFile::CMeshIlluminatedFromFile(CMeshLoadInfo* pMeshInfo) : CMeshFromFile::CMeshFromFile(pMeshInfo)
{
}

CMeshIlluminatedFromFile::~CMeshIlluminatedFromFile()
{

}

