#include <array>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>


#include <Windows.h>
#include <iostream>

#include "Headers/Pipes.hpp"
#include "Headers/Bird.hpp"
#include "Headers/DrawText.hpp"
#include "Headers/Global.hpp"
#include "Headers/Pipes.hpp"
#include "Headers/PipesManager.hpp"

int main()
{
	//People kept telling me that I should write fewer comments.
	//SO I WILL NOT WRITE COMMENTS AT ALL!!!
	//Jk, I'll just write comments for things that in my opinion need an explanation.

	unsigned short game_speed = 1;
	unsigned short generation = 0;
	unsigned short record_score = 0;

	Bird bird;

	Pipes pipe(SCREEN_WIDTH, SCREEN_HEIGHT / 2);

	std::chrono::microseconds lag(0);

	std::chrono::steady_clock::time_point previous_time;

	std::mt19937_64 random_engine(std::chrono::system_clock::now().time_since_epoch().count());

	sf::Event event;

	sf::RenderWindow window(sf::VideoMode(2 * SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT), "Flappy Bird", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, 2 * SCREEN_WIDTH, SCREEN_HEIGHT)));

	sf::Sprite background_sprite;
	sf::Sprite ground_sprite;

	sf::Texture background_texture;
	background_texture.loadFromFile("Resources/Images/Background.png");
	background_texture.setRepeated(true);

	sf::Texture ground_texture;
	ground_texture.loadFromFile("Resources/Images/Ground.png");

	PipesManager pipes_manager;

	sf::IntRect rects(0, 0, SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_HEIGHT);

	//Since we're also gonna use rand(), we need to set a random seed.
	srand(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));

	background_sprite.setTextureRect(rects);
	background_sprite.setTexture(background_texture);

	ground_sprite.setPosition(0, GROUND_Y);

	ground_sprite.setTextureRect(rects);
	ground_sprite.setTexture(ground_texture);

	previous_time = std::chrono::steady_clock::now();


	sf::Event ev;

	while (1 == window.isOpen())
	{
		//Someone said I should use chrono more often, and I did.
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;

		while (window.isOpen())
		{
			window.pollEvent(ev);

			lag -= FRAME_DURATION;



			bird.update(true, pipes_manager.get_pipes(), &window, &ev);



			
			if (ev.type == sf::Event::Closed)
				window.close();

			if(!bird.get_dead())
			pipes_manager.update(random_engine);

			window.clear();
			window.draw(background_sprite);


			//pipe.draw(window);
			pipes_manager.draw(window);
			text_draw(bird.get_score(), window);

			bird.draw(window);
			window.draw(ground_sprite);

			window.display();
			Sleep(10);
			
		}
	}
}