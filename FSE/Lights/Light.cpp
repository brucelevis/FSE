#include "Light.h"
#include "../Application.h"
#include <rttr/registration.h>


namespace fse
{

	Light::Light()
	{
	}

	Light::Light(const Light& other) : scene_(other.scene_), light_texture_(other.light_texture_)
	{
		light_ = scene_->getLightWorld()->getLightSystem()->createLightPointEmission();
		*light_ = *other.light_;
	}

	Light::Light(Scene* scene, const sf::Vector2f& spawnPos, const std::string& path, bool smooth) : scene_(scene)
	{
		light_texture_ = scene->getApplication()->getAssetLoader().getTexture(path);
		light_texture_->setSmooth(smooth);

		light_ = scene->getLightWorld()->getLightSystem()->createLightPointEmission();
		light_->setOrigin(sf::Vector2f(light_texture_->getSize().x * 0.5f, light_texture_->getSize().y * 0.5f));
		light_->setTexture(*light_texture_);
		light_->setColor(sf::Color::White);
		light_->setPosition(spawnPos * FSE_PIXELS_PER_METER);

	}

	Light::~Light()
	{
		if (scene_ != nullptr && light_ != nullptr)
			scene_->getLightWorld()->getLightSystem()->removeLight(light_);
	}

	void Light::setPosition(const sf::Vector2f pos) const
	{
		light_->setPosition(pos * FSE_PIXELS_PER_METER);
	}

	void Light::setColor(const sf::Color color) const
	{
		light_->setColor(color);
	}

	void Light::setScale(const sf::Vector2f scale) const
	{
		light_->setScale(scale);
	}

	sf::Vector2f Light::getPosition() const
	{
		return light_->getPosition() * FSE_METERS_PER_PIXEL;
	}

	sf::Color Light::getColor() const
	{
		return light_->getColor();
	}

	sf::Vector2f Light::getScale() const
	{
		return light_->getScale();
	}

	void Light::rotate(float angle) const
	{
		light_->rotate(angle);
	}

	void Light::setRotation(float angle) const
	{
		light_->setRotation(angle);
	}

	float Light::getRotation() const
	{
		return light_->getRotation();
	}

	void Light::setTurnedOn(bool on) const
	{
		light_->setTurnedOn(on);
	}

	bool Light::isTurnedOn() const
	{
		return light_->isTurnedOn();
	}

	void Light::toggleTurnedOn() const
	{
		light_->toggleTurnedOn();
	}

	Light& Light::operator=(const Light& other)
	{
		if (&other == this)
			return *this;

		Light tmp(other);
		std::swap(light_, tmp.light_);
		std::swap(scene_, tmp.scene_);
		std::swap(light_texture_, tmp.light_texture_);

		return *this;
	}
}

RTTR_REGISTRATION
{
	using namespace rttr;
using namespace fse;

registration::class_<Light>("fse::Light")
.property("position_", &Light::getPosition, &Light::setPosition)
.property("scale_", &Light::getScale, &Light::setScale)
.property("turned_on_", &Light::isTurnedOn, &Light::setTurnedOn)
.property("rotation_", &Light::getRotation, &Light::setRotation)
.property("color_", &Light::getColor, &Light::setColor)
;

}
