#ifndef __CPARTICLE_H__
#define __CPARTICLE_H__

#define STAY_FOR_TWOSECONDS 0	// 在手指滑過的地方產生 particle
#define RANDOMS_FALLING     1	// 在手指滑過的地方往下產生 particle
#define FREE_FLY 2				// 在手指滑過的地方任意向四方產生 particle
#define EXPLOSION 3				// 噴射出圓形的煙火
#define HEARTSHAPE 4			// 噴射出心型的煙火
#define BUTTERFLYSHAPE	5		// 噴射出蝴蝶外型的煙火
#define SPLIT 6
#define CANNABIS 7
#define TEST_ONE 8
#define RAIN 9
#define TEST_ONE_CHILD 10
#define TEST_TWO 11
#define TEST_THREE 12


#define EMITTER_DEFAULT 99
#include "cocos2d.h"
#include "CXParticle.h"

USING_NS_CC;

class CParticle
{
private:
	cocos2d::Sprite *_Particle;	// 分子本體
	cocos2d::Point  _OldPos;		// 分子前一個位置
	cocos2d::Point  _Pos;			// 分子目前的位置
	cocos2d::Point  _Direction;	// 分子目前的運動方向，單位向量
	cocos2d::Point  _WindDir;		//分子被風吹的方向
	

	float _fVelocity;	// 分子的速度
	float _fLifeTime;	// 生命週期
	float _fIntensity;	// 分子能量的最大值，通常用於改變分子的顏色
	float _fOpacity;	// 目前分子的透明度
	float _fSpin;		// 分子的旋轉量
	float _fSize;		// 分子的大小
	float _fGravity;	// 分子接收到的重力大小
	float  _WindVel;    // 風的大小
	cocos2d::Color3B _color;	// 分子的顏色
	// 時間
	float _fElapsedTime; // 分子從顯示到目前為止的時間
	float _fDelayTime;	 // 分子顯示前的延遲時間
	float _lifeTimeComtrol;

	// 行為模式
	int _iType;
	// 顯示與否
	bool _bVisible;
	
public:
	CParticle();

	void setParticle(const std::string &pngName, cocos2d::Scene &stage);
	bool update(float dt);
	void setPosition(const cocos2d::Point &inPos);
	void setColor(const cocos2d::Color3B& color);
	void setBehavior(CXParticle& type); // 設定分子產生的起始行為模式
	void setVisible();
	void setGravity(const float fGravity);
	void setVelocity(const float v) { _fVelocity = v; }
	void setLifetime(const float lt);
	void setDirection(const cocos2d::Point& pt) { _Direction = pt; }
	void setSize(float s) { _fSize = s; _Particle->setScale(_fSize); }
	void setSpin(float spin);

	void setOpacity(float op);

	void setWind(cocos2d::Point& wind);

	void setWindVel(float vel);

	//Set texture
	void setParticleTexture(const std::string& pngName);

	//Calculate
	float calSpin(float dt);

	float WindXCal(float dt);
	float WindYCal(float dt);

	cocos2d::Point& getPosition();
	cocos2d::Point getOldPosition();
};

#endif