#pragma once


#define STAY_FOR_TWOSECONDS 0	// �b����ƹL���a�貣�� particle
#define RANDOMS_FALLING     1	// �b����ƹL���a�詹�U���� particle
#define FREE_FLY 2				// �b����ƹL���a����N�V�|�貣�� particle
#define EXPLOSION 3				// �Q�g�X��Ϊ��Ϥ�
#define HEARTSHAPE 4			// �Q�g�X�߫����Ϥ�
#define BUTTERFLYSHAPE	5		// �Q�g�X�����~�����Ϥ�
#define SPLIT 6
#define CANNABIS 7
#define RAIN 8
#define EMITTER_DEFAULT 99
#include "cocos2d.h"

USING_NS_CC;

class CXParticle
{
protected:
	cocos2d::Sprite* _Particle;	// ���l����
	cocos2d::Point  _OldPos;		// ���l�e�@�Ӧ�m
	cocos2d::Point  _Pos;			// ���l�ثe����m
	cocos2d::Point  _Direction;	// ���l�ثe���B�ʤ�V�A���V�q

	float _fVelocity;	// ���l���t��
	float _fLifeTime;	// �ͩR�g��
	float _fIntensity;// ���l��q���̤j�ȡA�q�`�Ω���ܤ��l���C��
	float _fOpacity;	// �ثe���l���z����
	float _fSpin;		// ���l������q
	float _fSize;		// ���l���j�p
	float _fGravity;	// ���l�����쪺���O�j�p
	cocos2d::Color3B _color;	// ���l���C��
	// �ɶ�
	float _fElapsedTime; // ���l�q��ܨ�ثe����ɶ�
	//float _fDelayTime;	 // ���l��ܫe������ɶ�

	// �欰�Ҧ�
	int _iType;
	// ��ܻP�_
	bool _bVisible;

public:
	CXParticle();

	bool update(float dt);

	float getVelocity();
	float getLifeTime();
	float getIntensity();
	float getOpacity();
	float getSpin();
	float getSize();
	float getGravity();
	cocos2d::Color3B getColor3B();
	virtual cocos2d::Point getDir() = 0;
	float getElapsedTime();
	int getType();
	
};