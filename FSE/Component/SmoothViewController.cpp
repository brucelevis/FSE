#include "SmoothViewController.h"
#include "../Scene.h"
#include "../FMath.h"

namespace fse
{
	SmoothViewController::SmoothViewController() : ViewController()
	{

	}

	SmoothViewController::SmoothViewController(sf::RenderTarget* render_target) : ViewController(render_target)
	{

	}

	void SmoothViewController::moveView(sf::Vector2f objectPos, float deltaTime)
	{
		if (render_target_ == nullptr)
			return;

		sf::View view = render_target_->getView();

		sf::Vector2f sz = view.getSize() * size_percentage_;
		sf::Vector2f ct = view.getCenter();

		sf::FloatRect viewRekt(ct.x - (sz.x * 0.5f), ct.y - (sz.y * 0.5f) - view.getSize().y*vertical_offset_, sz.x, sz.y);
		
		objectPos = sf::Vector2f(objectPos.x, objectPos.y - (view.getSize().y * FSE_METERS_PER_PIXEL * vertical_offset_));

		sf::Vector2f toCenter = fse::FMath::Lerp(view.getCenter(), objectPos*FSE_PIXELS_PER_METER, deltaTime /** 0.75f*/);
		if (!viewRekt.contains(objectPos * FSE_PIXELS_PER_METER))
		{
			if (objectPos == oldPosition)
			{
				view.setCenter(toCenter);
			}
 			view.move((objectPos - oldPosition) * FSE_PIXELS_PER_METER);
		}
		else
		{
			view.setCenter(toCenter);
		}

		oldPosition = objectPos;

		render_target_->setView(view);
	}

	void SmoothViewController::setView(sf::Vector2f objectPos)
	{
		if (render_target_ == nullptr)
			return;

		sf::View view = render_target_->getView();
		sf::Vector2f sz = view.getSize() * size_percentage_;
		sf::Vector2f ct = view.getCenter();
		sf::FloatRect viewRekt(ct.x - (sz.x * 0.5f), ct.y - (sz.y * 0.5f) - view.getSize().y*vertical_offset_, sz.x, sz.y);
		objectPos = sf::Vector2f(objectPos.x, objectPos.y - (view.getSize().y * FSE_METERS_PER_PIXEL * vertical_offset_));
		view.setCenter(objectPos * FSE_PIXELS_PER_METER);
		oldPosition = objectPos;
		render_target_->setView(view);
	}

	void SmoothViewController::setSizePercentage(float size_percentage)
	{
		size_percentage_ = size_percentage;
	}

	void SmoothViewController::setVerticalOffset(float vertical_offset)
	{
		vertical_offset_ = vertical_offset;
	}

	float SmoothViewController::getSizePercentage() const
	{
		return size_percentage_;
	}

	float SmoothViewController::getVerticalOffset() const
	{
		return vertical_offset_;
	}

}
