#include "stdafx.h"
#include "GameFramework.h"

CGameFramework gGameFramework;

int main() {
	gGameFramework.BuildObjects();

	while (1) {
		gGameFramework.FrameAdvance();
	}
}