#include <chrono>
#include <SFML/Graphics.hpp>

#include <sstream>

#include "Headers/DrawText.hpp"
#include "Headers/Global.hpp"

void draw_text(bool i_black, bool i_horizontal_center, bool i_vertical_center, unsigned short i_x, unsigned short i_y, const std::string& i_text, sf::RenderWindow& i_window)
{
	short character_x = i_x;
	short character_y = i_y;

	unsigned char character_width;

	sf::Sprite character_sprite;

	sf::Texture font_texture;
	font_texture.loadFromFile("Resources/Images/Font.png");

	//There are 96 characters in the texture.
	character_width = font_texture.getSize().x / 96;

	character_sprite.setTexture(font_texture);

	if (1 == i_black)
	{
		character_sprite.setColor(sf::Color(0, 0, 0));
	}

	if (1 == i_horizontal_center)
	{
		//I'd love to explain this, but I don't know how it works myself.
		character_x += static_cast<short>(round(0.5f * (SCREEN_WIDTH - character_width * i_text.substr(0, i_text.find_first_of('\n')).size())));
	}

	if (1 == i_vertical_center)
	{
		//If you know any better way to do this, please let me know.
		character_y += static_cast<short>(round(0.5f * (SCREEN_HEIGHT - FONT_HEIGHT * (1 + std::count(i_text.begin(), i_text.end(), '\n')))));
	}

	for (std::string::const_iterator a = i_text.begin(); a != i_text.end(); a++)
	{
		if ('\n' == *a)
		{
			if (1 == i_horizontal_center)
			{
				character_x = i_x + static_cast<short>(round(0.5f * (SCREEN_WIDTH - character_width * i_text.substr(1 + a - i_text.begin(), i_text.find_first_of('\n', 1 + a - i_text.begin()) - (1 + a - i_text.begin())).size())));
			}
			else
			{
				character_x = i_x;
			}

			character_y += FONT_HEIGHT;

			continue;
		}

		character_sprite.setPosition(character_x, character_y);
		character_sprite.setTextureRect(sf::IntRect(character_width * (*a - 32), 0, character_width, FONT_HEIGHT));

		character_x += character_width;

		i_window.draw(character_sprite);
	}
}


void text_draw(unsigned int score , sf::RenderWindow& window)
{
	std::stringstream ss;

	ss << score;
	std::string ch = ss.str();

	sf::Sprite score_sprite;

	sf::Texture score_texture;
	score_texture.loadFromFile("Resources/Images/Font.png");

	size_t size = ch.size();

	unsigned int length = SCREEN_WIDTH - 8 * size;

	for (int i = 0; i < ch.size(); i++)
	{
		char c = ch[i];

		
		score_sprite.setPosition(i == 0 ? length : length += 16, SCREEN_HEIGHT / 4.0);

		score_sprite.setTextureRect(sf::IntRect(BIRD_SIZE * 16 + (c - '0') * 16, 0, BIRD_SIZE, BIRD_SIZE * 2));
		score_sprite.setTexture(score_texture);

		window.draw(score_sprite);

	}

}