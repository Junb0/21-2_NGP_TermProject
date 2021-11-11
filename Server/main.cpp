#include "stdafx.h"
#include "GameFramework.h"

CGameFramework gGameFramework;

int main() {
	XMFLOAT3 xmf3Test = { 0.1f, 1.3f, 3.2f };
	cout << xmf3Test.x << " " << xmf3Test.y << " " << xmf3Test.z << endl;
}