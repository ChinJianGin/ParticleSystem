#include "flyweight_factory.h"

Flyweight_Factory::~Flyweight_Factory()
{
	for (auto it = ParticleBehavior.begin(); it != ParticleBehavior.end(); it++)
	{
		delete it->second;
	}
	ParticleBehavior.clear();
}
CXParticle* Flyweight_Factory::getParticleBehavior(const int key)
{
	if (ParticleBehavior.find(key) != ParticleBehavior.end())
	{
		return ParticleBehavior[key];
	}
}

CXParticle* Flyweight_Factory::getParticleBehavior(const int key, CXParticle& Behavior)
{
	if (ParticleBehavior.find(key) != ParticleBehavior.end())
	{
		return ParticleBehavior[key];
	}
	CXParticle* _Behavior = &Behavior;
	ParticleBehavior.insert(pair<int, CXParticle*>(key, _Behavior));
	return _Behavior;
}