#include "CParticleSystem.h"

#define NUMBER_PARTICLES 1000 // 預設一次取得 1000 個 Particles

USING_NS_CC;

CParticleSystem::CParticleSystem()
{
	_fGravity = 0;
	_bEmitterOn = false;
}

void CParticleSystem::setEmitter(bool bEm)
{
	_bEmitterOn = bEm;
}

void CParticleSystem::init(cocos2d::Scene &stage)
{
	_iFree = NUMBER_PARTICLES;
	_iInUsed = 0;
	_pParticles = new CParticle[NUMBER_PARTICLES]; // 取得所需要的 particle 空間
	 // 讀入儲存多張圖片的 plist 檔
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
	for (int i = 0; i < NUMBER_PARTICLES; i++) {
		_pParticles[i].setParticle("flare.png", stage);
		_FreeList.push_front(&_pParticles[i]);
	}
}

void CParticleSystem::update(float dt)
{
	CParticle *get;
	list <CParticle *>::iterator it;	
	if (_bEmitterOn) { // 根據 Emitter 設定的相關參數，產生相對應的分子
		// 先計算在累加
		int n = (int)(_fElpasedTime * _iNumParticles); // 到目前為止應該產生的分子個數
		if (n > _iGenParticles) {  // 產生的分子個數不足，產生到 n 個分子
			for (int i = 0; i < n - _iGenParticles; i++) {
				// 根據 Emitter 的相關參數，設定所產生分子的參數
				if (_iFree != 0) {
					get = _FreeList.front();
					get->setBehavior(EMITTER_DEFAULT);
					get->setVelocity(_fVelocity);
					get->setLifetime(_fLifeTime);
					get->setGravity(_fGravity);
					get->setPosition(_emitterPt);
					get->setColor(Color3B(_fRed, _fGreen, _fBlue));
					get->setOpacity(_fOpacity);
					get->setLifetime(_fLifeTime);
					get->setSize(0.125f);
					// 根據 _fSpread 與 _vDir 產生方向
					float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
					t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
					t = ( _fDir + t )* M_PI / 180.0f;
					Vec2 vdir(cosf(t), sinf(t));
					get->setDirection(vdir);
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--; _iInUsed++;
				}
			}
			_iGenParticles = n; // 目前已經產生 n 個分子
			
		}
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;
	}

	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); ) {
			if ((*it)->update(dt)) { // 分子生命週期已經到達
									 // 將目前這一個節點的內容放回 _FreeList
				_FreeList.push_front((*it));
				it = _InUsedList.erase(it); // 移除目前這一個, 
				_iFree++; _iInUsed--;
			}
			else it++;
		}
	}
	
}

void CParticleSystem::setGravity(float fGravity)
{
	// 設定目前 particle 是在 inused 的 gravity
	_fGravity = fGravity;
	list <CParticle *>::iterator it;
	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
			(*it)->setGravity(_fGravity);
		}
	}
}

void CParticleSystem::setSpeed(float fSpeed)
{
	_fVelocity = fSpeed;
}

CParticleSystem::~CParticleSystem()
{
	if (_iInUsed != 0) _InUsedList.clear(); // 移除所有的 NODE
	if (_iFree != 0) _FreeList.clear();
	delete[] _pParticles; // 釋放所有取得資源
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("particletexture.plist");
}

void CParticleSystem::onTouchesBegan(const cocos2d::Point &touchPoint)
{
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(STAY_FOR_TWOSECONDS);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setColor(Color3B(_fRed, _fGreen, _fBlue));
			get->setOpacity(_fOpacity);
			get->setLifetime(_fLifeTime);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case RANDOMS_FALLING :
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(RANDOMS_FALLING);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setColor(Color3B(_fRed, _fGreen, _fBlue));
			get->setOpacity(_fOpacity);
			get->setLifetime(_fLifeTime);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case FREE_FLY:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(FREE_FLY);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setColor(Color3B(_fRed, _fGreen, _fBlue));
			get->setOpacity(_fOpacity);
			get->setLifetime(_fLifeTime);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case EXPLOSION:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree > 100) {
			for (int i = 0; i < 100; i++) {
				get = _FreeList.front();
				get->setBehavior(EXPLOSION);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				get->setColor(Color3B(_fRed, _fGreen, _fBlue));
				get->setOpacity(_fOpacity);
				get->setLifetime(_fLifeTime);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case HEARTSHAPE:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setBehavior(HEARTSHAPE);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				get->setColor(Color3B(_fRed, _fGreen, _fBlue));
				get->setOpacity(_fOpacity);
				get->setLifetime(_fLifeTime);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case BUTTERFLYSHAPE:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setBehavior(BUTTERFLYSHAPE);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				get->setColor(Color3B(_fRed, _fGreen, _fBlue));
				get->setOpacity(_fOpacity);
				get->setLifetime(_fLifeTime);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// 沒有分子, 所以就不提供
		break;
	}
}

void CParticleSystem::onTouchesMoved(const cocos2d::Point &touchPoint)
{
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(STAY_FOR_TWOSECONDS);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setColor(Color3B(_fRed, _fGreen, _fBlue));
			get->setOpacity(_fOpacity);
			get->setLifetime(_fLifeTime);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case RANDOMS_FALLING:
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(RANDOMS_FALLING);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setColor(Color3B(_fRed, _fGreen, _fBlue));
			get->setOpacity(_fOpacity);
			get->setLifetime(_fLifeTime);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case FREE_FLY:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(FREE_FLY);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setColor(Color3B(_fRed, _fGreen, _fBlue));
			get->setOpacity(_fOpacity);
			get->setLifetime(_fLifeTime);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	}
}