#pragma once

#include <SFML/System.hpp>

#include "../Signals.h"
#include "FSEObject.h"

namespace fse
{
	class Timer : public FSEObject
	{
	public:
		Timer(Scene* scene);
		~Timer();

		virtual void update(float deltaTime) override;

		virtual void draw(sf::RenderTarget& target) override;

		virtual void spawned() override;

		template <typename Slot>
		void start(Slot&& slot)
		{
			active_ = true;
			timeout_.connect(slot);
		}

		void stop();
		void setInterval(int msecs);

		bool isActive() const;
		
		void setSingleShot(bool singleShot);

		template <typename Slot>
		static void singleShot(Scene* scene,int msecs, Slot&& slot)
		{
			auto timer = std::make_unique<Timer>(scene);
			timer->setInterval(msecs);
			timer->setSingleShot(true);

			timer->start(slot);

			scene->spawnFSEObject(std::move(timer));
		}

	private:	

		bool active_ = false;
		bool single_shot_ = false;
		int interval_ = 0;
		float elapsed_time_ = 0.f;
	


	PUBLIC_SIGNALS:
		Signal<> timeout_;

	};
}