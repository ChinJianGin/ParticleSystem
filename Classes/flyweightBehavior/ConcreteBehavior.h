#pragma once
#include "flyweight.h"
#include "CXParticle.h"

class Stay_For_Two_Seconds : public CXParticle
{
public:
	Stay_For_Two_Seconds();
	~Stay_For_Two_Seconds(){}

	Point getDir() override;
private:

};

class Random_Fallen : public CXParticle
{
public:
	Random_Fallen();
	~Random_Fallen(){}
	Point getDir() override;
private:

};

class Emitter_Default : public CXParticle
{
public:
	Emitter_Default();
	~Emitter_Default() {}
	Point getDir() override;
private:

};

class Free_Fly : public CXParticle
{
public:
	Free_Fly();
	~Free_Fly() {}
	Point getDir() override;
private:

};

class Explosion : public CXParticle
{
public:
	Explosion();
	~Explosion() {}
	Point getDir() override;
private:
};

class HeartShape : public CXParticle
{
public:
	HeartShape();
	~HeartShape(){}
	Point getDir() override;
private:

};

class Butterfly : public CXParticle
{
public:
	Butterfly();
	~Butterfly() {}
	Point getDir() override;
private:

};

class Split : public CXParticle
{
public:
	Split();
	~Split() {}
	Point getDir() override;
private:

};

class Cannabis : public CXParticle
{
public:
	Cannabis();
	~Cannabis() {}
	Point getDir() override;
private:

};

class Rain : public CXParticle
{
public:
	Rain();
	~Rain() {}
	Point getDir() override;
private:

};

class Test_One : public CXParticle
{
public:
	Test_One();
	~Test_One() {}
	Point getDir() override;
private:

};

class Test_One_Child : public CXParticle
{
public:
	Test_One_Child();
	~Test_One_Child() {}
	Point getDir() override;
private:

};