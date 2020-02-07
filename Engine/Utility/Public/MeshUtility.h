#pragma once
#include <float.h>
#include <cmath>
#include <Eigen/Dense>

#include "../../Frame/Public/Mesh.h"

class MeshUtility
{
public:
	static bool CreateCube(ManualMesh& outMesh, float sideSize = 1.0f);

	static bool CreateSphere(ManualMesh& outMesh, float radius = 0.5f);

	static bool CreatePlane(ManualMesh& outMesh, float sideSize = 1.0f);

};