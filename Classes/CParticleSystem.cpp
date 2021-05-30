#include "CParticleSystem.h"

#define NUMBER_PARTICLES 1000 // �w�]�@�����o 1000 �� Particles

USING_NS_CC;

CParticleSystem::CParticleSystem()
{
	_fGravity = 0;
	_bEmitterOn = false;
	_pngName = nullptr;
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
	_BehaviorManager->getParticleBehavior(6, *(new Lambda));
	_BehaviorManager->getParticleBehavior(99, *(new Emitter_Default));
	_iFree = NUMBER_PARTICLES;
	_VisibleSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();
	_iInUsed = 0;
	_pParticles = new CParticle[NUMBER_PARTICLES]; // ���o�һݭn�� particle �Ŷ�
	 // Ū�J�x�s�h�i�Ϥ��� plist ��
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
	if (_bEmitterOn) { // �ھ� Emitter �]�w�������ѼơA���ͬ۹��������l
		// ���p��b�֥[
		int n = (int)(_fElpasedTime * _iNumParticles); // ��ثe�������Ӳ��ͪ����l�Ӽ�
		if (n > _iGenParticles) {  // ���ͪ����l�ӼƤ����A���ͨ� n �Ӥ��l
			for (int i = 0; i < n - _iGenParticles; i++) {
				// �ھ� Emitter �������ѼơA�]�w�Ҳ��ͤ��l���Ѽ�
				if (_iFree != 0) {
					get = _FreeList.front();
					get->setBehavior(*(_BehaviorManager->getParticleBehavior(EMITTER_DEFAULT)));
					get->setVelocity(_fVelocity);
					get->setLifetime(_fLifeTime);
					get->setGravity(_fGravity);
					get->setPosition(_emitterPt);
					get->setColor(Color3B(_fRed, _fGreen, _fBlue));
					get->setOpacity(_fOpacity);
					get->setLifetime(_fLifeTime);
					get->setParticleTexture(_pngName);
					get->setSpin(_fSpin);
					get->setSize(0.125f);
					// �ھ� _fSpread �P _vDir ���ͤ�V
					float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
					t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
					t = ( _fDir + t )* M_PI / 180.0f;
					Vec2 vdir(cosf(t), sinf(t));
					get->setDirection(vdir);
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--; _iInUsed++;
				}
			}
			_iGenParticles = n; // �ثe�w�g���� n �Ӥ��l
			
		}
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;
	}

	if (_iInUsed != 0) { // �����l�ݭn��s��
		for (it = _InUsedList.begin(); it != _InUsedList.end(); ) {
			if ((*it)->update(dt)) { // ���l�ͩR�g���w�g��F
									 // �N�ثe�o�@�Ӹ`�I�����e��^ _FreeList
				_FreeList.push_front((*it));
				it = _InUsedList.erase(it); // �����ثe�o�@��, 
				_iFree++; _iInUsed--;
			}
			else it++;
		}
	}
	
}

void CParticleSystem::setGravity(float fGravity)
{
	// �]�w�ثe particle �O�b inused �� gravity
	_fGravity = fGravity;
	list <CParticle *>::iterator it;
	if (_iInUsed != 0) { // �����l�ݭn��s��
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
	if (_iInUsed != 0) _InUsedList.clear(); // �����Ҧ��� NODE
	if (_iFree != 0) _FreeList.clear();
	delete[] _pParticles; // ����Ҧ����o�귽
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("particletexture.plist");
}

void CParticleSystem::onTouchesBegan(const cocos2d::Point &touchPoint)
{
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
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
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case FREE_FLY:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case EXPLOSION:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case HEARTSHAPE:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case BUTTERFLYSHAPE:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case LAMBDA:
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setBehavior(*(_BehaviorManager->getParticleBehavior(LAMBDA)));
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
		else return;// �S�����l, �ҥH�N������
		break;
	}
}

void CParticleSystem::onTouchesMoved(const cocos2d::Point &touchPoint)
{
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
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
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case FREE_FLY:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	}
}