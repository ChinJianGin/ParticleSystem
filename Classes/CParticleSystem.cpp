#include "CParticleSystem.h"

#define NUMBER_PARTICLES 1000 // 預設一次取得 1000 個 Particles

USING_NS_CC;

CParticleSystem::CParticleSystem()
{
	_fGravity = 0;
	_bEmitterOn = false;
	_pngName = nullptr;
	_windDir = Point(0,0);
}

void CParticleSystem::setEmitter(bool bEm)
{
	_bEmitterOn = bEm;
}

void CParticleSystem::init(cocos2d::Scene &stage)
{
	_BehaviorManager = new Flyweight_Factory();
	_BehaviorManager->getParticleBehavior(0, *(new Stay_For_Two_Seconds));
	_BehaviorManager->getParticleBehavior(1, *(new Random_Fallen));
	_BehaviorManager->getParticleBehavior(2, *(new Free_Fly));
	_BehaviorManager->getParticleBehavior(3, *(new Explosion));
	_BehaviorManager->getParticleBehavior(4, *(new HeartShape));
	_BehaviorManager->getParticleBehavior(5, *(new Butterfly));
	_BehaviorManager->getParticleBehavior(6, *(new Split));
	_BehaviorManager->getParticleBehavior(7, *(new Cannabis));
	_BehaviorManager->getParticleBehavior(8, *(new Test_One));
	_BehaviorManager->getParticleBehavior(9, *(new Rain));	
	_BehaviorManager->getParticleBehavior(99, *(new Emitter_Default));
	_iFree = NUMBER_PARTICLES;
	_VisibleSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();
	_iInUsed = 0;
	_pParticles = new CParticle[NUMBER_PARTICLES]; // 取得所需要的 particle 空間
	 // 讀入儲存多張圖片的 plist 檔
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
	_pngName = "flare.png";
	for (int i = 0; i < NUMBER_PARTICLES; i++) {
		_pParticles[i].setParticle("flare.png", stage);
		_FreeList.push_front(&_pParticles[i]);
	}
}

void CParticleSystem::setPngName(const char& pngName)
{
	_pngName = &pngName;
}


void CParticleSystem::update(float dt)
{
	CParticle *get;
	list <CParticle *>::iterator it;	
	if (_bEmitterOn) { // 根據 Emitter 設定的相關參數，產生相對應的分子		
		int n = (int)(_fElpasedTime * _iNumParticles); // 到目前為止應該產生的分子個數
		switch (_iType)
		{
		case STAY_FOR_TWOSECONDS:
			if (n > _iGenParticles) {  // 產生的分子個數不足，產生到 n 個分子
				for (int i = 0; i < n - _iGenParticles; i++) {
					// 根據 Emitter 的相關參數，設定所產生分子的參數
					if (_iFree != 0) {
						get = _FreeList.front();
						get->setBehavior(*(_BehaviorManager->getParticleBehavior(EMITTER_DEFAULT)));
						get->setVelocity(_fVelocity);
						get->setLifetime(_fLifeTime);
						get->setGravity(_fGravity);
						get->setPosition(_emitterPt);
						get->setColor(Color3B(_fRed, _fGreen, _fBlue));
						get->setOpacity(_fOpacity);
						get->setParticleTexture(_pngName);
						get->setSpin(_fSpin);
						get->setSize(0.125f);
						get->setWind(_windDir);
						get->setWindVel(_fWindVel);
						// 根據 _fSpread 與 _vDir 產生方向
						float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
						t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
						t = (_fDir + t) * M_PI / 180.0f;
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
			break;
		case RANDOMS_FALLING:
			if (n > _iGenParticles) {  // 產生的分子個數不足，產生到 n 個分子
				for (int i = 0; i < n - _iGenParticles; i++) {
					// 根據 Emitter 的相關參數，設定所產生分子的參數
					if (_iFree != 0) {
						get = _FreeList.front();
						get->setBehavior(*(_BehaviorManager->getParticleBehavior(RAIN)));
						get->setVelocity(_fVelocity);
						get->setGravity(_fGravity);
						get->setPosition(Vec2(_VisibleSize.width / 2 + _origin.x + ((rand() % 1600) - 900), _VisibleSize.height ));
						get->setColor(Color3B(_fRed, _fGreen, _fBlue));
						get->setOpacity(_fOpacity);
						get->setParticleTexture(_pngName);
						get->setSpin(_fSpin);
						get->setWind(_windDir);
						get->setWindVel(_fWindVel);
						// 根據 _fSpread 與 _vDir 產生方向
						float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
						t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
						t = (_fDir * 2 + t) * M_PI_2 / 180.0f;
						Vec2 vdir(cosf(t), (-sinf(t)));
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

			break;
		}
		// 先計算在累加
		_fElpasedTime += dt;
	}

	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); ) {
			if ((*it)->update(dt) || (*it)->getPosition().x < -10 || (*it)->getPosition().x > 1600) { // 分子生命週期已經到達
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
			get->setBehavior(*(_BehaviorManager->getParticleBehavior(STAY_FOR_TWOSECONDS)));
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setColor(Color3B(_fRed, _fGreen, _fBlue));
			get->setOpacity(_fOpacity);
			get->setLifetime(_fLifeTime);
			get->setParticleTexture(_pngName);
			get->setSpin(_fSpin);
			get->setWind(_windDir);
			get->setWindVel(_fWindVel);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case RANDOMS_FALLING :
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(*(_BehaviorManager->getParticleBehavior(RANDOMS_FALLING)));
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setColor(Color3B(_fRed, _fGreen, _fBlue));
			get->setOpacity(_fOpacity);
			get->setLifetime(_fLifeTime);
			get->setParticleTexture(_pngName);
			get->setSpin(_fSpin);
			get->setWind(_windDir);
			get->setWindVel(_fWindVel);
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
			get->setBehavior(*(_BehaviorManager->getParticleBehavior(FREE_FLY)));
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setColor(Color3B(_fRed, _fGreen, _fBlue));
			get->setOpacity(_fOpacity);
			get->setLifetime(_fLifeTime);
			get->setParticleTexture(_pngName);
			get->setSpin(_fSpin);
			get->setWind(_windDir);
			get->setWindVel(_fWindVel);
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
				get->setBehavior(*(_BehaviorManager->getParticleBehavior(EXPLOSION)));
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				get->setColor(Color3B(_fRed, _fGreen, _fBlue));
				get->setOpacity(_fOpacity);
				get->setLifetime(_fLifeTime);
				get->setParticleTexture(_pngName);
				get->setSpin(_fSpin);
				get->setWind(_windDir);
				get->setWindVel(_fWindVel);
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
				get->setBehavior(*(_BehaviorManager->getParticleBehavior(HEARTSHAPE)));
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				get->setColor(Color3B(_fRed, _fGreen, _fBlue));
				get->setOpacity(_fOpacity);
				get->setLifetime(_fLifeTime);
				get->setParticleTexture(_pngName);
				get->setSpin(_fSpin);
				get->setWind(_windDir);
				get->setWindVel(_fWindVel);
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
				get->setBehavior(*(_BehaviorManager->getParticleBehavior(BUTTERFLYSHAPE)));
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				get->setColor(Color3B(_fRed, _fGreen, _fBlue));
				get->setOpacity(_fOpacity);
				get->setLifetime(_fLifeTime);
				get->setParticleTexture(_pngName);
				get->setSpin(_fSpin);
				get->setWind(_windDir);
				get->setWindVel(_fWindVel);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case SPLIT:
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setBehavior(*(_BehaviorManager->getParticleBehavior(SPLIT)));
				get->setPosition(Vec2(_VisibleSize.width / 2 + _origin.x, _VisibleSize.height / 2 + _origin.y));
				get->setGravity(_fGravity);
				get->setColor(Color3B(_fRed, _fGreen, _fBlue));
				get->setOpacity(_fOpacity);
				get->setLifetime(_fLifeTime);
				get->setParticleTexture(_pngName);
				get->setSpin(_fSpin);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
			
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case CANNABIS:
		if (_iFree > 200) {
			for (int i = 0; i < 200; i++) {
				get = _FreeList.front();
				get->setBehavior(*(_BehaviorManager->getParticleBehavior(CANNABIS)));
				get->setPosition(Vec2(_VisibleSize.width / 2 + _origin.x, _VisibleSize.height / 2 + _origin.y - 100));
				get->setGravity(_fGravity);
				get->setColor(Color3B(_fRed, _fGreen, _fBlue));
				get->setOpacity(_fOpacity);
				get->setLifetime(_fLifeTime);
				get->setParticleTexture(_pngName);
				get->setSpin(_fSpin);
				get->setWind(_windDir);
				get->setWindVel(_fWindVel);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}

		}
		else return;// 沒有分子, 所以就不提供
		break;
	case TEST_ONE:
		if (_iFree > 50) {
			for (int i = 0; i < 50; i++) {
				get = _FreeList.front();
				get->setBehavior(*(_BehaviorManager->getParticleBehavior(TEST_ONE)));
				get->setPosition(Vec2(_VisibleSize.width / 2 + _origin.x, _VisibleSize.height / 2 + _origin.y));
				get->setGravity(_fGravity);
				get->setColor(Color3B(_fRed, _fGreen, _fBlue));
				get->setOpacity(_fOpacity);
				get->setLifetime(_fLifeTime);
				get->setParticleTexture(_pngName);
				get->setSpin(_fSpin);
				get->setWind(_windDir);
				get->setWindVel(_fWindVel);
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
			get->setBehavior(*(_BehaviorManager->getParticleBehavior(STAY_FOR_TWOSECONDS)));
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setColor(Color3B(_fRed, _fGreen, _fBlue));
			get->setOpacity(_fOpacity);
			get->setLifetime(_fLifeTime);
			get->setParticleTexture(_pngName);
			get->setSpin(_fSpin);
			get->setWind(_windDir);
			get->setWindVel(_fWindVel);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case RANDOMS_FALLING:
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(*(_BehaviorManager->getParticleBehavior(RANDOMS_FALLING)));
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setColor(Color3B(_fRed, _fGreen, _fBlue));
			get->setOpacity(_fOpacity);
			get->setLifetime(_fLifeTime);
			get->setParticleTexture(_pngName);
			get->setSpin(_fSpin);
			get->setWind(_windDir);
			get->setWindVel(_fWindVel);
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
			get->setBehavior(*(_BehaviorManager->getParticleBehavior(FREE_FLY)));
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setColor(Color3B(_fRed, _fGreen, _fBlue));
			get->setOpacity(_fOpacity);
			get->setLifetime(_fLifeTime);
			get->setParticleTexture(_pngName);
			get->setSpin(_fSpin);
			get->setWind(_windDir);
			get->setWindVel(_fWindVel);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	}
}

void CParticleSystem::setWind(float wind)
{
	float t;
	t = wind * M_PI;
	_windDir.x = cosf(t);
	_windDir.y = sinf(t);		
	list <CParticle*>::iterator it;
	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
			(*it)->setWind(_windDir);
		}
	}
	//log("x = %1.4f", _windDir.x);
	//log("y = %1.1f", _windDir.y);
}

void CParticleSystem::setWindVel(float vel)
{
	_fWindVel = vel;
	list <CParticle*>::iterator it;
	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
			(*it)->setWindVel(_fWindVel);
		}
	}
}