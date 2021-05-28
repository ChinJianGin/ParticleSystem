#pragma once
#include <iostream>
#include <map>
#include "flyweight.h"
#include "CXParticle.h"
#include "ConcreteBehavior.h"

using namespace std;

class Flyweight_Factory
{
public:
	Flyweight_Factory();
	~Flyweight_Factory();
	CXParticle* getParticleBehavior(const int key);
private:
	map<int, CXParticle*> ParticleBehavior;
};