#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <array>
#include <string>
#include "Headers\Vector2.h";
#include "Headers\Game.h";


// I know this is super messy & probably not the most professional! This is my first project, so please judge lightly.
// I'm very new to C++ and I really want to know all about it, so I'm super excited to
// Dive into the language, I just have to get there and ultimately learn.


int main()
{
	if (!BGM.openFromFile("audio/overworld.ogg"))
	{
		std::cout << "Background music unable to load" << std::endl;
	}
	
	BGM.setLoop(true);
	window.setFramerateLimit(240);

	//Player Declaration
	Player Plr;

	//Enemy Declarations
	
	Entity Enemy(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(663, 570), sf::Vector2f(2,2), sf::Vector2f(0,40), sf::Vector2f(9,-5), Vector2(17, 34));
	Entity Enemy1(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(1389, 570), sf::Vector2f(2, 2), sf::Vector2f(0, 40), sf::Vector2f(9, -5), Vector2(17, 34));
	Entity Enemy2(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(1750, 570), sf::Vector2f(2, 2), sf::Vector2f(0, 40), sf::Vector2f(9, -5), Vector2(17, 34));
	Entity Enemy3(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(2490, 377), sf::Vector2f(2, 2), sf::Vector2f(0, 40), sf::Vector2f(9, -5), Vector2(17, 34));
	Entity Enemy4(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(2560, 377), sf::Vector2f(2, 2), sf::Vector2f(0, 40), sf::Vector2f(9, -5), Vector2(17, 34));
	Entity Enemy5(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(2544, 185), sf::Vector2f(2, 2), sf::Vector2f(0, 40), sf::Vector2f(9, -5), Vector2(17, 34));
	Entity Enemy6(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(2872, 570), sf::Vector2f(2, 2), sf::Vector2f(0, 40), sf::Vector2f(9, -5), Vector2(17, 34));
	Entity Enemy7(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(4061, 570), sf::Vector2f(2, 2), sf::Vector2f(0, 40), sf::Vector2f(9, -5), Vector2(17, 34));
	Entity Enemy8(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(4175, 570), sf::Vector2f(2, 2), sf::Vector2f(0, 40), sf::Vector2f(9, -5), Vector2(17, 34));
	Entity Enemy9(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(4416, 378), sf::Vector2f(2, 2), sf::Vector2f(0, 40), sf::Vector2f(9, -5), Vector2(17, 34));
	Entity Enemy10(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(4862, 570), sf::Vector2f(2, 2), sf::Vector2f(0, 40), sf::Vector2f(9, -5), Vector2(17, 34));
	Entity Enemy11(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(5034, 570), sf::Vector2f(2, 2), sf::Vector2f(0, 40), sf::Vector2f(9, -5), Vector2(17, 34));
	Entity Enemy12(1, "sprites/enemies.png", Vector2(18.5, 20), Vector2(5172, 282), sf::Vector2f(2, 2), sf::Vector2f(0, 40), sf::Vector2f(9, -5), Vector2(17, 34));

	Sketch MapSketch = {
		{7,8,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,8,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,8,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,8,9,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,8,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,9,1},
		{1,1,1,1,1,1,1,1,7,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,9,1,1,1,1,1,1,1,1,1,1,1,1,12,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,25,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,8,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,25,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,25,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,25,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,25,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,25,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,19,0,1,1,0,1,1,10,11,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,25,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,3,1,1,1,1,1,1,1,1,1,1,1,10,11,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,10,11,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,23,24,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,25,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,3,3,1,1,1,1,1,1,1,1,1,1,23,24,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,23,24,1,1,1,1,1,1,1,1,1,1,10,11,1,1,1,1,1,1,1,1,1,0,1,1,23,24,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,25,1,1,1,1},
		{1,4,6,1,1,1,1,1,1,4,5,6,1,1,1,1,1,1,1,1,1,3,3,3,1,1,3,3,3,4,6,1,1,10,11,1,1,1,23,24,1,1,4,5,6,1,1,1,1,1,1,4,5,6,1,1,1,1,1,4,5,6,1,1,1,1,23,24,1,1,1,1,1,1,1,1,1,1,23,24,1,1,1,1,4,6,1,1,1,0,1,1,23,24,1,1,1,1,1,1,1,1,1,1,4,6,1,1,1,1,1,1,1,1,1,1,1,1,0,1,4,5,6,1,1,1,1,1,1,1,19,1,1,1,1},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,1,1,1,23,24,1,1,1,1,1,1,1,1,1,1,23,24,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,1,1,1,23,24,1,1,1,1,10,11,1,1,1,1,23,24,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,1,1,1,23,24,1,1,1,1,23,24,1,1,1,1,23,24,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,1,1,1,23,24,1,1,1,1,23,24,1,1,1,1,23,24,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,1,1,1,23,24,1,1,1,1,23,24,1,1,1,1,23,24,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};
	TileMap Map(MapSketch, 13, 30.0f, Vector2(16, 16), sf::Vector2f(-50, -100), "sprites/map.png", { 1, 4, 5, 6, 7, 8, 9, 20, 21, 22 }); // First of ignore list alpha = 0
	//Tile t(3, 12, 50.0f, Vector2(16, 16), sf::Vector2f(30, -20), sf::Vector2f(0, 0), "sprites/map.png", true, 255);
	//int CorrespondingIndexToCell, int PerRow, float GridSizeF, Vector2 EPSILON, sf::Vector2f Position, const sf::Vector2f Origin, const std::string& m_tileshee
	// Handle window

	while (window.isOpen())
	{
		if (!GAME_RUNNING) {
			GAME_RUNNING = true;
			BGM.play();
			Timer.restart();
		}

		sf::Event event;

		// Update
		
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Clear screen

		window.clear(sf::Color(0,100,200));

		//Map.Render();
		Map.Render();
		//Player update
		Plr.Update();
		
		// Enemy updates
		sf::Vector2f viewCenter(window.getView().getCenter());
		sf::Vector2f viewSize(window.getView().getSize());

		sf::FloatRect currentViewRect(viewCenter - viewSize / 2.f, viewSize);
		for (unsigned int i = 0; i != Entity::Entities.size(); i++) {
			Entity* Ety = Entity::Entities.at(i);
			if (currentViewRect.intersects(Ety->sprite.getGlobalBounds()))
			{
				Ety->Update();
			}
		}
		window.display();
	}

	if (WON)
	{
		sf::RenderWindow WinScreen(sf::VideoMode(300, 300), "Congratulations!");
		sf::Text t;
		sf::Font f;

		sf::Texture ImgMan;
		sf::IntRect RectSourceSprite;
		RectSourceSprite = sf::IntRect(0, 0, 208, 43);
		bool DrawMan = false;
		if (!ImgMan.loadFromFile("images/unknown.png"))
		{
			std::cout << "Unable to load unknown.png image!" << std::endl;
		}

		sf::Sprite Man(ImgMan);
		Man.setPosition(sf::Vector2f(30, 100));

		if (!f.loadFromFile("arial.ttf"))
		{
			std::cout << "Unable to find font" << std::endl;
			// error...
		}
		
		std::string extra = "Wow! You're really fast. Good job!";
		float time = Timer.getElapsedTime().asSeconds();
		
		if (time >= 30.0f)
		{
			if (time <= 60.0f)
			{
				extra = "Good job!";
			}
			else if (time <= 90.0f)
			{
				extra = "Try to get a better time!";
			}
			else if (time <= 120.0f)
			{
				DrawMan = true;
				extra = "...";
				
			}
		}
		


		t.setString(sf::String("Congratulations on beating the game!\n Your time was:" + std::to_string(time) + " Seconds!" + "\n" + extra));
		t.setFont(f);
		t.setCharacterSize(16);
		t.setFillColor(sf::Color::Red);
		t.setStyle(sf::Text::Bold | sf::Text::Underlined);
		while (WinScreen.isOpen())
		{
			sf::Event event;

			while (WinScreen.pollEvent(event))
			{
				// Close window: exit
				if (event.type == sf::Event::Closed)
					WinScreen.close();
			}

			

			WinScreen.clear();

			WinScreen.draw(t);
			if (DrawMan)
			{
				WinScreen.draw(Man);
			}
			

			WinScreen.display();
		}
	}
	return EXIT_SUCCESS;
}

