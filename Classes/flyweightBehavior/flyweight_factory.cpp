#include "flyweight_factory.h"

Flyweight_Factory::Flyweight_Factory()
{
	ParticleBehavior[0] = new Stay_For_Two_Seconds;
	ParticleBehavior[1] = new Random_Fallen;
	ParticleBehavior[2] = new Free_Fly;
	ParticleBehavior[3] = new Explosion;
	ParticleBehavior[4] = new HeartShape;
	ParticleBehavior[5] = new Butterfly;
	ParticleBehavior[99] = new Emitter_Default;
}

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