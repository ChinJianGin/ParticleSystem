#include <cmath>
#include "CParticle.h"


// 根據重力與時間計算 delta time 之間的位移差量 再轉成螢幕的位移
// 假設 2.5 秒讓一個分子從螢幕最上方移動到最下方, 也就是移動 720 PIXEL
// 720 PIXEL = 0.5*9.8*2.5*2.5 m => 1M = 23.5102 PIXEL
// 因為Y 軸往下為負, 所以重力要加上負號, 代表方向

#define FALLING_TIME 2.5f
#define MAX_HEIGHT 720.0f
#define PIXEL_PERM (2.0f*MAX_HEIGHT/(9.8f*FALLING_TIME*FALLING_TIME))
#define GRAVITY_Y(t,dt,g) ((g)*((t)+0.5f*(dt)))  //已經經過 t 秒後，再經過 dt 時間內落下距離

#define LIFE_NOISE(f) ((f)*(1.0f-(rand()%2001/1000.0f)))
//#define INTENSITY(f)  ( (f) >= 255 ? 255 : (f) )

inline int INTENSITY(float f) {
	if (f >= 255) return(255);
	else if (f <= 0) return(0);
	else return((int)f);
}

USING_NS_CC;

CParticle::CParticle()
{
	_fGravity = 0;
	_lifeTimeComtrol = 0;
}


bool CParticle::update(float dt)
{
	float cost, sint;
	switch (_iType) {
	case STAY_FOR_TWOSECONDS:
		if (!_bVisible && _fElapsedTime >= _fDelayTime ) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime> _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(1 + sint * 2);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY((_color.r + sint * 64)*(1 + sint)), 
			INTENSITY((_color.g - cost * 32)*(1 + sint)), INTENSITY((_color.b - sint * 64)*(1 + sint))));			
			if (_WindDir != Point(0, 0))
			{
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.x += ((_Direction.x * _fVelocity) + (this->WindXCal(dt)/* * _WindVel*/)) * dt * PIXEL_PERM;				
				_Pos.y += ((_Direction.y * _fVelocity + tt) + (this->WindYCal(dt))) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);
			}
			else {
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.y += (_Direction.y * _fVelocity + tt) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);
			}
			_Particle->setRotation(this->calSpin(dt)); 
		}
		break;
	case RANDOMS_FALLING:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(1 + sint * 1.25f);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			if (_WindDir != Point(0, 0))
			{
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.x += ((_Direction.x * _fVelocity) + (this->WindXCal(dt) * _WindVel)) * dt * PIXEL_PERM;
				_Pos.y += ((_Direction.y * _fVelocity + tt) + (this->WindYCal(dt))) * dt * PIXEL_PERM;
				//log("%1.2f", (this->WindYCal(dt) * _WindDir.y));
				_Particle->setPosition(_Pos);
			}
			else
			{
				_Pos.x += _Direction.x * _fVelocity * dt * PIXEL_PERM;
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.y += (_Direction.y * _fVelocity + tt) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);
			}			
			_Particle->setRotation(this->calSpin(dt));
		}
		break;
	case FREE_FLY:

		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(1 + sint * 2);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			if (_WindDir != Point(0, 0))
			{
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.x += ((_Direction.x * _fVelocity) + (this->WindXCal(dt) * _WindVel)) * dt * PIXEL_PERM;
				_Pos.y += ((_Direction.y * _fVelocity + tt) + (this->WindYCal(dt) + tt)) * dt * PIXEL_PERM;
				//log("%1.2f", (this->WindYCal(dt) * _WindDir.y));
				_Particle->setPosition(_Pos);
			}
			else
			{
				_Pos.x += _Direction.x * _fVelocity * dt * PIXEL_PERM;
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.y += (_Direction.y * _fVelocity + tt) * dt * PIXEL_PERM;
				//_Pos.y += _Direction.y * _fVelocity * dt;
				_Particle->setPosition(_Pos);
			}			
			_Particle->setRotation(this->calSpin(dt));
		}
		break;
	case EXPLOSION:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(1.25 + sint*2.0);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r*(1 + sint)), INTENSITY(_color.g*(1 + sint)), INTENSITY(_color.b*(1 + sint))));
			if (_WindDir != Point(0, 0))
			{
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.x += ((_Direction.x * _fVelocity) + (this->WindXCal(dt) * _WindVel)) * dt * PIXEL_PERM;
				_Pos.y += ((_Direction.y * _fVelocity + tt) + (this->WindYCal(dt) + tt)) * dt * PIXEL_PERM;
				//log("%1.2f", (this->WindYCal(dt) * _WindDir.y));
				_Particle->setPosition(_Pos);
			}
			else
			{
				_Pos.x += _Direction.x * cost * _fVelocity * dt * PIXEL_PERM;
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.y += (_Direction.y * cost * _fVelocity + tt) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);
			}			
			_Particle->setRotation(this->calSpin(dt));
		}
		break;
	case HEARTSHAPE:
	case BUTTERFLYSHAPE:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			// 根據心型公式，計算每一個分子的終止位置
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(1.25 + (1 - cost)*2.0);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			if (_WindDir != Point(0, 0))
			{
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.x += ((_Direction.x * _fVelocity) + (this->WindXCal(dt) * _WindVel)) * dt * PIXEL_PERM;
				_Pos.y += ((_Direction.y * _fVelocity + tt) + (this->WindYCal(dt) + tt)) * dt * PIXEL_PERM;
				//log("%1.2f", (this->WindYCal(dt) * _WindDir.y));
				_Particle->setPosition(_Pos);
			}
			else
			{
				_Pos.x += _Direction.x * cost * _fVelocity * dt * PIXEL_PERM;
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.y += (_Direction.y * cost * _fVelocity + tt) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);
			}			
			_Particle->setRotation(this->calSpin(dt));
		}
		break;
	case EMITTER_DEFAULT:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(_fSize + sint * 1.5f );
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(Color3B(INTENSITY(_color.r*(1 + sint)), INTENSITY(_color.g*(1 + sint)), INTENSITY(_color.b*(1 + sint))));
//			_Particle->setColor(_color);
			if (_WindVel != 0.0f)
			{
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.x += ((_Direction.x * _fVelocity) + (this->WindXCal(dt))) * dt * PIXEL_PERM;
				_Pos.y += ((_Direction.y * _fVelocity + tt) + (this->WindYCal(dt) + tt)) * dt * PIXEL_PERM;
				//log("%1.2f", _Pos.x);
				_Particle->setPosition(_Pos);
			}
			else
			{
				_Pos.x += _Direction.x * _fVelocity * dt * PIXEL_PERM;
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.y += (_Direction.y * _fVelocity + tt) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);
			}			
			_Particle->setRotation(this->calSpin(dt));
		}
		break;
	case SPLIT:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI_2 * _fElapsedTime / _fLifeTime);
			cost = cosf(2 * M_PI_2 * _fElapsedTime / _fLifeTime);
			_Particle->setScale(1.25 + sint * 2.0);
			_Particle->setOpacity(_fOpacity);
			_Particle->setColor(Color3B(INTENSITY(_color.r* (1 + sint)), INTENSITY(_color.g* (1 + sint)), INTENSITY(_color.b* (1 + sint))));
			_Pos.x += _Direction.x * cost * _fVelocity * dt * PIXEL_PERM;
			float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
			_Pos.y += (_Direction.y * cost * _fVelocity + tt) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);				
			_Particle->setRotation(this->calSpin(dt));
		}
		break;
	case CANNABIS:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI * _fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2 * _fElapsedTime / _fLifeTime);
			_Particle->setScale(1.25 + sint * 2.0);
			_Particle->setOpacity(_fOpacity);
			_Particle->setColor(Color3B(INTENSITY(_color.r * (1 + sint)), INTENSITY(_color.g * (1 + sint)), INTENSITY(_color.b * (1 + sint))));
			if (_WindDir != Point(0, 0))
			{
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.x += ((_Direction.x * _fVelocity) + (this->WindXCal(dt) * _WindVel)) * dt * PIXEL_PERM;
				_Pos.y += ((_Direction.y * _fVelocity + tt) + (this->WindYCal(dt) + tt)) * dt * PIXEL_PERM;
				//log("%1.2f", (this->WindYCal(dt) * _WindDir.y));
				_Particle->setPosition(_Pos);
			}
			else
			{
				_Pos.x += _Direction.x * cost * _fVelocity * dt * PIXEL_PERM;
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.y += (_Direction.y * cost * _fVelocity + tt) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);
			}			
			_Particle->setRotation(this->calSpin(dt));
		}
		break;
	case RAIN:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI * _fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2 * _fElapsedTime / _fLifeTime);
			_Particle->setScale(1 + sint * (rand() % 2));
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			if (_WindDir != Point(0, 0))
			{
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.x += ((_Direction.x * _fVelocity) + (this->WindXCal(dt) * _WindVel)) * dt * PIXEL_PERM;
				_Pos.y += ((_Direction.y * _fVelocity + tt) + (this->WindYCal(dt))) * dt * PIXEL_PERM;
				//log("%1.2f", (this->WindYCal(dt) * _WindDir.y));
				_Particle->setPosition(_Pos);
			}
			else
			{
				_Pos.x += _Direction.x * _fVelocity * dt * PIXEL_PERM;
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.y += (_Direction.y * _fVelocity + tt) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);
			}
			_Particle->setRotation(this->calSpin(dt));
		}
		break;
	case TEST_ONE:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI * _fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2 * _fElapsedTime / _fLifeTime);
			_Particle->setScale(1 + sint * 2.0);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			if (_WindDir != Point(0, 0))
			{
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.x += ((_Direction.x * _fVelocity) + (this->WindXCal(dt) * _WindVel)) * dt * PIXEL_PERM;
				_Pos.y += ((_Direction.y * _fVelocity + tt) + (this->WindYCal(dt))) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);				
			}
			else
			{
				_Pos.x += _Direction.x * _fVelocity * dt * PIXEL_PERM;
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.y += (_Direction.y * _fVelocity + tt) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);				
			}
			_Particle->setRotation(this->calSpin(dt));	
			
			//log("Old Pos = %1.2f", _OldPos.x);
		}
		break;
	case TEST_TWO:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI * _fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2 * _fElapsedTime / _fLifeTime);
			_Particle->setScale(1 + sint * 2.0);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			if (_WindDir != Point(0, 0))
			{
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.x += ((_Direction.x * _fVelocity) + (this->WindXCal(dt) * _WindVel)) * dt * PIXEL_PERM;
				_Pos.y += ((_Direction.y * _fVelocity + tt) + (this->WindYCal(dt))) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);
				_OldPos = _Pos;
			}
			else
			{
				_Pos.x += _Direction.x * _fVelocity * dt * PIXEL_PERM;
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.y += (_Direction.y * _fVelocity + tt) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);
				_OldPos = _Pos;
			}
			_Particle->setRotation(this->calSpin(dt));
		}
		break;
	case TEST_THREE:		
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI_2 * _fElapsedTime / _fLifeTime ) + _lifeTimeComtrol;
			cost = sinf(M_PI_2 * _fElapsedTime / _fLifeTime ) - _lifeTimeComtrol;
			_lifeTimeComtrol += 0.002;
			_Particle->setScale(1 + sint * 2.0);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			if (_WindDir != Point(0, 0))
			{
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
				_Pos.x += ((_Direction.x * _fVelocity) + (this->WindXCal(dt) * _WindVel)) * dt * PIXEL_PERM;
				_Pos.y += ((_Direction.y * _fVelocity + tt) + (this->WindYCal(dt))) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);
			}
			else
			{
				float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);				
				_Pos.x += _Direction.x * _fVelocity * dt * PIXEL_PERM;					
				_Pos.y += (_Direction.y * _fVelocity + tt) * dt * PIXEL_PERM;
				_Particle->setPosition(_Pos);
			}
			_Particle->setRotation(this->calSpin(dt));
			if (_lifeTimeComtrol > 0.1)_lifeTimeComtrol = 0;
		}
		break;
	}
	// 累加時間
	_fElapsedTime += dt;
	return false;
}


void CParticle::setBehavior(CXParticle& type)
{
	float t;
	
	_fVelocity = type.getVelocity();
	_fLifeTime = type.getLifeTime();
	_fIntensity = type.getIntensity();
	_fOpacity = type.getOpacity();
	_fSpin = type.getSpin();
	_fSize = type.getSize();
	_color = type.getColor3B();
	_fElapsedTime = type.getElapsedTime();
	_fDelayTime = 0;
	this->setDirection(type.getDir());
	_fGravity = type.getGravity();
	_Particle->setOpacity(_fOpacity);
	_Particle->setScale(_fSize);
	_iType = type.getType();
}
void CParticle::setLifetime(const float lt) {
	_fLifeTime = lt + LIFE_NOISE(0.15f);;
}

void CParticle::setColor(const cocos2d::Color3B& color) { _color = color; }

void CParticle::setParticle(const std::string& pngName, cocos2d::Scene &stage)
{
	_Particle = Sprite::createWithSpriteFrameName(pngName);
	_Particle->setPosition(Point(rand() % 1024, rand() % 768));
	_Particle->setOpacity(255);
	_Particle->setColor(Color3B::WHITE);
	_bVisible = false;
	_Particle->setVisible(false);
	_iType = 0;
	//BlendFunc blendfunc = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};  
	BlendFunc blendfunc = { GL_SRC_ALPHA, GL_ONE };
	_Particle->setBlendFunc(blendfunc);
	stage.addChild(_Particle, 1);
}

void CParticle::setVisible()
{
	_bVisible = true;
	_Particle->setVisible(_bVisible);
}

void CParticle::setPosition(const cocos2d::Point &inPos) {
	_Pos = inPos;
};

void CParticle::setGravity(const float fGravity)
{
	_fGravity = fGravity;
}

void CParticle::setOpacity(float op)
{
	_fOpacity = op;
}

void CParticle::setParticleTexture(const std::string& pngName)
{
	_Particle->setSpriteFrame(pngName);
}

void CParticle::setSpin(float spin)
{
	_fSpin = spin;
}

float CParticle::calSpin(float dt)
{
	float degree = _Particle->getRotation();
	degree += dt * _fSpin;
	if (_fSpin == 0)degree = 0;
	return degree;
}

void CParticle::setWind(cocos2d::Point& wind)
{
	_WindDir = wind;
}

void CParticle::setWindVel(float vel)
{
	_WindVel = vel;
}

float CParticle::WindXCal(float dt)
{
	float windxVel = 0;
	if (_WindDir.x < 0)
		windxVel = ((-_WindVel) * _fElapsedTime) + ((0.5f * dt) * (_WindVel + ((_WindDir.x * _WindVel) * dt)));
	else if (_WindDir.x > 0)
		windxVel = (_WindVel * _fElapsedTime) + ((0.5f * dt) * (_WindVel + ((_WindDir.x * _WindVel) * dt)));
	return	windxVel;
}

float CParticle::WindYCal(float dt)
{
	float windyVel = 0;
	windyVel = (_fGravity + (_WindVel * _WindDir.y)) * (_fElapsedTime + (0.5 * (dt)));
	return	windyVel;
}

cocos2d::Point& CParticle::getPosition()
{
	return this->_Pos;
}

cocos2d::Point CParticle::getOldPosition()
{
	return this->_OldPos;
}