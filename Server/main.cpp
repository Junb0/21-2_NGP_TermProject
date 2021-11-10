#pragma comment(lib, "ws2_32")

#include <iostream>
#include <winsock2.h>

#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <DirectXPackedVector.h>

using namespace std;

using namespace DirectX;
using namespace DirectX::PackedVector;


int main() {
	XMFLOAT3 xmf3Test = { 0.1f, 1.3f, 3.2f };
	cout << xmf3Test.x << " " << xmf3Test.y << " " << xmf3Test.z << endl;
}