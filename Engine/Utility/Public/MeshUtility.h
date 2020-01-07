#pragma once
#include <float.h>
#include <cmath>
#include <Eigen/Dense>

#include "../../Frame/Public/Mesh.h"

class MeshUtility
{
	static bool CreateCube(Mesh& outMesh, float sideSize = 1.0f);

	static bool CreateSphere(Mesh& outMesh, float Radius = 0.5f);
};