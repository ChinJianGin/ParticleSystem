#include "ConcreteBehavior.h"

Stay_For_Two_Seconds::Stay_For_Two_Seconds()
{
	_fVelocity = 0.25f;
	_fLifeTime = 2.5f;
	_fIntensity = 1;
	_fOpacity = 255;
	_fSize = 1;
	_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 64 + rand() % 128);
	_fElapsedTime = 0;
	_fGravity = 0;
	_iType = STAY_FOR_TWOSECONDS;
}

Random_Fallen::Random_Fallen()
{
	_fVelocity = 5.0f + rand() % 10 / 10.0f; // 單位 M/Sec
	_Direction.x = 0;
	_Direction.y = -1;
	_fLifeTime = 3.0f;
	_fIntensity = 1;
	_fOpacity = 255;
	_fSpin = 0;
	_fSize = 1;
	_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
	_fElapsedTime = 0;
	_fGravity = 0;
	_iType = RANDOMS_FALLING;
}

Free_Fly::Free_Fly()
{
	_fVelocity = 5.0f + rand() % 10 / 10.0f; // 單位 M/Sec
	_fLifeTime = 3.0f;
	_fIntensity = 1;
	_fOpacity = 255;
	_fSpin = 0;
	_fSize = 1;
	_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
	_fElapsedTime = 0;
	_fGravity = 0;
	_iType = FREE_FLY;
}

Emitter_Default :: Emitter_Default()
{
	_fIntensity = 1;
	_fOpacity = 255;
	_fSize = 1;
	_color = Color3B(rand() % 128, rand() % 128, 128 + rand() % 128);
	_fElapsedTime = 0;
	_iType = EMITTER_DEFAULT;
}

Explosion::Explosion()
{
	_fVelocity = 15.0f + rand() % 10 / 10.0f;
	_fLifeTime = 1.5f;
	_fIntensity = 1;
	_fOpacity = 255;
	_fSpin = 0;
	_fSize = 1;
	_color = Color3B(64 + rand() % 128, 64 + rand() % 128,64 + rand() % 128);
	//_color = Color3B(255, 255, 255);
	_fElapsedTime = 0;
	_fGravity = 0;
	_iType = EXPLOSION;
}

HeartShape::HeartShape()
{
	_fVelocity = 1.0f;
	_fLifeTime = 1.5f;
	_fIntensity = 1;
	_fOpacity = 255;
	_fSpin = 0;
	_fSize = 1;
	_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
	//_color = Color3B(255, 255, 255);
	_fElapsedTime = 0;
	_fGravity = 0;
	_iType = HEARTSHAPE;
}

Butterfly::Butterfly()
{
	_fVelocity = 6.5f;
	_fLifeTime = 1.5f;
	_fIntensity = 1;
	_fOpacity = 255;
	_fSpin = 0;
	_fSize = 1;
	_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
	//_color = Color3B(255, 255, 255);
	_fElapsedTime = 0;
	_fGravity = 0;
	_iType = BUTTERFLYSHAPE;
}