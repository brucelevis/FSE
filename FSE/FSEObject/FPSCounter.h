#pragma once

#include "FSEObject.h"

namespace fse
{
	/*!
	 * \brief Prebuilt FPSCounter
	 * 
	 * Default z-order = 257
	 */
	class FPSCounter : public FSEObject
	{
	public:
		FPSCounter(Scene* scene);
		FPSCounter(Scene* scene, const sf::Vector2f& spawnPos);
		~FPSCounter();

		void update(float deltaTime) override;
		void draw(sf::RenderTarget& target) override;
		void spawned() override;

		void setShowDetailed(bool detailed);
		bool isDetailed() const;

	protected:

		sf::Font font_;
		sf::Text fps_text_;
		sf::RectangleShape background_;

	private:
		sf::View counter_view_;

		bool detailed_view_ = false;
		float current_time_;
		sf::Clock measureclock_;
		float fps_ = 0;
		float last_fps_ = 0;
		float smoothing_ = 0.58f;
		sf::Clock updclock_;

		Signal<>::Connection on_resize_connection_;

		RTTR_ENABLE(fse::FSEObject)
		RTTR_REGISTRATION_FRIEND
	};
}