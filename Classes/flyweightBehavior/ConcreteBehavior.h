#pragma once
#include "flyweight.h"
#include "CXParticle.h"

class Stay_For_Two_Seconds : public CXParticle
{
public:
	Stay_For_Two_Seconds();
	~Stay_For_Two_Seconds(){}

private:

};

class Random_Fallen : public CXParticle
{
public:
	Random_Fallen();
	~Random_Fallen(){}

private:

};

class Emitter_Default : public CXParticle
{
public:
	Emitter_Default();
	~Emitter_Default() {}

private:

};

class Free_Fly : public CXParticle
{
public:
	Free_Fly();
	~Free_Fly() {}

private:

};

class Explosion : public CXParticle
{
public:
	Explosion();
	~Explosion() {}

private:
};

class HeartShape : public CXParticle
{
public:
	HeartShape();
	~HeartShape(){}
private:

};

class Butterfly : public CXParticle
{
public:
	Butterfly();
	~Butterfly() {}
private:

};