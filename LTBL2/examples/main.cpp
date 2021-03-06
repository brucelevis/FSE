#include <SFML/Graphics.hpp>
#include <iostream>

// Include LetThereBeLight.hpp
#include "../src/LightSystem.hpp"

int main()
{
	// Create an SFML window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Let There Be Light 2", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	sf::View view = window.getDefaultView();

	// Create the LightSystem
	ltbl::LightSystem ls;
	ls.create({ -1000.f, -1000.f, 2000.f, 2000.f }, window.getSize());

	// Load light texture
	sf::Texture pointLightTexture;
	pointLightTexture.loadFromFile("LTBL2/examples/pointLightTexture.png");
	pointLightTexture.setSmooth(true);
	sf::Texture spookyLightTexture;
	spookyLightTexture.loadFromFile("LTBL2/examples/spookyLightTexture.png");
	spookyLightTexture.setSmooth(true);


	// Add a sun light
	ltbl::LightDirectionEmission* sun = ls.createLightDirectionEmission();
	sun->setColor(sf::Color(255, 230, 200));

	// Add a light point
	ltbl::LightPointEmission* mlight = ls.createLightPointEmission();
	mlight->setOrigin(sf::Vector2f(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f));
	mlight->setTexture(pointLightTexture);
	mlight->setScale(3.f, 3.f);
	mlight->setColor(sf::Color::White);

	// Create a shape
	std::vector<sf::RectangleShape> shapes;
	sf::RectangleShape blocker;
	blocker.setSize({ 200.f, 50.f });
	blocker.setPosition({ 500.f, 300.f });
	blocker.setFillColor(sf::Color::Red);
	shapes.push_back(blocker);

	// Create a light shape with the same shape
	ls.createLightShape(blocker);

	// Main loop
	float angle = 0.f;
	sf::Vector2f beginRight, endRight;
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			// Remove the mouse light when middle click
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle)
			{
				if (mlight != nullptr)
				{
					ls.removeLight(mlight);
					mlight = nullptr;
				}
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
			{
				beginRight = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }, view);
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
			{
				endRight = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }, view);

				sf::RectangleShape blocker;
				blocker.setSize(endRight - beginRight);
				blocker.setPosition(beginRight);
				blocker.setFillColor(sf::Color::Red);
				shapes.push_back(blocker);

				// Add a new light shape
				ls.createLightShape();
			}
			// Add a point light when left click
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				auto light = ls.createLightPointEmission();
				light->setOrigin(sf::Vector2f(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f));
				light->setTexture(pointLightTexture);
				light->setScale(1.f, 1.f);
				light->setColor(sf::Color::White);
				light->setPosition(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }, view));
			}
		}

		sf::Time dt = clock.restart();

		// Rotate the sun light
		angle += 10.f * dt.asSeconds();
		sun->setCastAngle(angle);

		// Move the mouse light
		if (mlight != nullptr)
		{
			mlight->setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window), view));
		}

		// Move the view
		sf::Vector2f mvt;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			mvt.y--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			mvt.y++;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			mvt.x--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			mvt.x++;
		view.move(mvt * dt.asSeconds() * 200.f);

		// Render
		window.clear(sf::Color::White);
		window.setView(view);
		for (std::size_t i = 0; i < shapes.size(); i++)
		{
			window.draw(shapes[i]);
		}

		// Render the lights
		ls.render(window);

		window.display();
	}

	return 0;
}