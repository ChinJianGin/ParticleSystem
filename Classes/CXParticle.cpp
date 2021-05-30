#include "cmath"
#include "CXParticle.h"

CXParticle::CXParticle()
{
	_Particle = nullptr;
	_fVelocity = 0;
	_fLifeTime = 0;
	_fIntensity = 1;
	_fOpacity = 255;
	_fSpin = 0;
	_fSize = 1;
	_fGravity = 0;
	_color = cocos2d::Color3B::WHITE;
}

bool CXParticle::update(float dt)
{
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		_fElapsedTime += dt;
		if (_fLifeTime <= _fElapsedTime)
		{

		}
		else return true;
		
		break;

	default:
		break;
	}
}

float CXParticle::getVelocity()
{
	return _fVelocity;
}

float CXParticle::getLifeTime()
{
	return _fLifeTime;
}

float CXParticle::getIntensity()
{
	return _fIntensity;
}

float CXParticle::getOpacity()
{
	return _fOpacity;
}

float CXParticle::getSpin()
{
	return _fSpin;
}

float CXParticle::getSize()
{
	return _fSize;
}

float CXParticle::getGravity()
{
	return _fGravity;
}

float CXParticle::getElapsedTime()
{
	return _fElapsedTime;
}

int CXParticle::getType()
{
	return _iType;
}

cocos2d::Color3B CXParticle::getColor3B()
{
	return _color;
}

