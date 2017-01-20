#include "FSELightWorld.h"
#include "../Application.h"

//#include "../../LTBL2/src/LightSystem.hpp"

namespace fse
{
	FSELightWorld::FSELightWorld(Scene* scene) : FSELightWorld(scene, sf::Vector2f(0, 0))
	{

	}

	FSELightWorld::FSELightWorld(Scene* scene, const sf::Vector2f& spawnPos) : FSEObject(scene, spawnPos)
	{
		setZOrder(255);
		light_system_ = std::make_unique<ltbl::LightSystem>(true);
	}

	FSELightWorld::~FSELightWorld()
	{
		light_system_->removeLight(sun_);
	}

	void FSELightWorld::update(float deltaTime)
	{
	}

	void FSELightWorld::draw(sf::RenderTarget& target)
	{
		if (lighting_)
			light_system_->render(target);
	}

	void FSELightWorld::spawned()
	{
	}

	void FSELightWorld::init(sf::RenderTarget* target)
	{
		light_system_->create({ -1000.f, -1000.f, 2000.f, 2000.f }, target->getSize());
		sun_ = light_system_->createLightDirectionEmission();
		sun_->setColor(sf::Color::Black);
	}

	bool FSELightWorld::getLighting() const
	{
		return lighting_;
	}

	void FSELightWorld::setLighting(bool lighting)
	{
		lighting_ = lighting;
	}

	ltbl::LightDirectionEmission* FSELightWorld::getSun() const
	{
		return sun_;
	}

	ltbl::LightSystem* FSELightWorld::getLightSystem()
	{
		return light_system_.get();
	}
}
