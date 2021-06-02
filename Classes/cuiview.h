#pragma once
#define TEXTURE_AMOUNT 7
#define EFFECT_AMOUNT 3

#include "cocos2d.h"
#include "ui/CocosGUI.h" // For Cocos Studio �������
#include "cocostudio/CocoStudio.h"
#include "Common/CSwitchButton.h"
#include "Common/CDraggableSprite.h"
#include "CParticleSystem.h"

class CUIView
{
private:
	// �إ߱��� particle system �һݪ��ާ@����
	cocos2d::Node* _uiRoot;
	cocos2d::Scene* _stage;
	cocos2d::Size _size; //�}�Ҫ������j�p

	// ���l���i���㤣�P�Ѽƪ����
	cocos2d::ui::TextBMFont* _GravityBMValue;
	cocos2d::ui::TextBMFont* _SpreadBMValue;
	cocos2d::ui::TextBMFont* _DirectionBMValue;
	cocos2d::ui::TextBMFont* _SpinBMValue;
	cocos2d::ui::TextBMFont* _SpeedBMValue;
	cocos2d::ui::TextBMFont* _OpacityBMValue;
	cocos2d::ui::TextBMFont* _ParticleBMValue;
	cocos2d::ui::TextBMFont* _LifeTimeBMValue;
	cocos2d::ui::TextBMFont* _RedBMValue;
	cocos2d::ui::TextBMFont* _GreenBMValue;
	cocos2d::ui::TextBMFont* _BlueBMValue;
	cocos2d::ui::TextBMFont* _WindBMValue;
	cocos2d::ui::TextBMFont* _WindVelBMValue;

	// ��ܤ��P�����l���A�A�Φb Emitter �S���}�Ҫ����A
	cocos2d::ui::TextBMFont* _TypeBMValue;

	// For Emitter
	CDraggableSprite* _EmitterSprite;
	CSwitchButton* _emitterSwitchBtn;
	bool _bEmitterOn;

	// ���V Particle System �����Ъ���
	CParticleSystem* _ParticleControl;

	//Change Texture
	CSwitchButton* _TexturSwitchBtn[TEXTURE_AMOUNT];

	//Different Particle effect
	CSwitchButton* _DifferentEffect[EFFECT_AMOUNT];
	bool _differOn;

public:
	CUIView();

	void setProperty(std::string uicsbname, cocos2d::Size vsize, cocos2d::Scene& stage);
	void setModel(CParticleSystem &model);
	void init();

	// �w�q Callback function
	void GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void ParticleEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void LifeTimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void RedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void GreenEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void BlueEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);

	void WindEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void WindVelEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);

	// touch �ƥ�
	void onTouchBegan(const cocos2d::Point& tPoint);
	void onTouchMoved(const cocos2d::Point& tPoint); //Ĳ�I���ʨƥ�
	void onTouchEnded(const cocos2d::Point& tPoint); //Ĳ�I�����ƥ� 

};