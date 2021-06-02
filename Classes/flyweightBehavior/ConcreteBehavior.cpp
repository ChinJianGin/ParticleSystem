#include "ConcreteBehavior.h"

Stay_For_Two_Seconds::Stay_For_Two_Seconds()
{
	_fVelocity = 0.25f;
	_fLifeTime = 2.5f;
	_Direction = Point(0, 0);
	_fIntensity = 1;
	_fOpacity = 255;
	_fSize = 1;
	_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 64 + rand() % 128);
	_fElapsedTime = 0;
	_fGravity = 0;
	_iType = STAY_FOR_TWOSECONDS;
}

Point Stay_For_Two_Seconds::getDir()
{
	/*float t;
	t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
	_Direction.x = cosf(t);
	_Direction.y = sinf(t);*/
	return _Direction;
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

Point Random_Fallen::getDir()
{
	return _Direction;
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

Point Free_Fly::getDir()
{
	float t;
	t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
	_Direction.x = cosf(t);
	_Direction.y = sinf(t);
	return _Direction;
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

Point Emitter_Default::getDir()
{
	float t;
	t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
	_Direction.x = cosf(t);
	_Direction.y = sinf(t);
	return _Direction;
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

Point Explosion::getDir()
{
	float t;
	t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
	_Direction.x = cosf(t);
	_Direction.y = sinf(t);
	return _Direction;
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

Point HeartShape::getDir()
{
	float t;
	t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
	float sint, cost, cos2t, cos3t, cos4t, sin12t;
	sint = sinf(t);  cost = cosf(t); cos2t = cosf(2 * t); cos3t = cosf(3 * t); cos4t = cosf(4 * t);
	sin12t = sin(t / 12.0f);
	_Direction.x = 16 * sint * sint * sint;
	_Direction.y = 13 * cost - 5 * cos2t - 2 * cos3t - cos4t;
	return _Direction;
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

Point Butterfly::getDir()
{
	float t;
	float sint, cost, cos4t, sin12t;
	t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
	sint = sinf(t);  cost = cosf(t); cos4t = cosf(4 * t); sin12t = sin(t / 12.0f);
	_Direction.x = sint * (expf(cost) - 2 * cos4t - powf(sin12t, 5));
	_Direction.y = cost * (expf(cost) - 2 * cos4t - powf(sin12t, 5));
	return _Direction;
}

Split::Split()
{
	_fVelocity = 2.0f;
	_fLifeTime = 1.5f;
	_fIntensity = 1;
	_fOpacity = 255;
	_fSpin = 0;
	_fSize = 1;
	_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
	//_color = Color3B(255, 255, 255);
	_fElapsedTime = 0;
	_fGravity = 0;
	_iType = SPLIT;
}

Point Split::getDir()
{
	float t;
	t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;	
	_Direction.x = sinf(t) * (rand() % 50);
	_Direction.y = cosf(t) * (rand() % 50);
	return _Direction;
}

Cannabis::Cannabis()
{
	_fVelocity = 5.0f;
	_fLifeTime = 1.5f;
	_fIntensity = 1;
	_fOpacity = 255;
	_fSpin = 0;
	_fSize = 1;
	_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
	//_color = Color3B(255, 255, 255);
	_fElapsedTime = 0;
	_fGravity = 0;
	_iType = CANNABIS;
}

Point Cannabis::getDir()
{
	float t;
	float cos8f, cos24f, sint, cost;
	t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
	sint = sinf(t); cost = cosf(t); cos8f = cos(8 * t); cos24f = cosf(24 * t);
	_Direction.x = ((1.0f + 0.9 * cos8f) * (1 + 0.1 * cos24f) * (1 + sint)) * cost;
	_Direction.y = ((1.0f + 0.9 * cos8f) * (1 + 0.1 * cos24f) * (1 + sint)) * sint;
	return _Direction;
}