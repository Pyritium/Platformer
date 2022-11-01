#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Vector2.h"
#include "Math.h"
#include "Global.h"
#include <array>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <chrono>
#include <thread>

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Platformer");

sf::View view;
sf::Clock Timer;

sf::Keyboard::Key DirInputs[2] = { sf::Keyboard::Right, sf::Keyboard::Left };

sf::Music BGM;


class Entity {
public:
	bool Alive = true;
	static std::vector<Entity*>	Entities;

	sf::Sprite sprite;
	sf::RectangleShape BoundingRect;
	double Acceleration = 0;

	void Update() {
		if (!Rendered || clock.getElapsedTime().asSeconds() >= 1.f/60.f) {
			clock.restart();
			Rendered = true;
		}
		// dT
		//std::cout << Position.X << " | " << Position.Y << std::endl;
		if (Alive)
		{
			sf::Time dt = clock.restart();
			double MaxSpeed = .3 * dt.asMilliseconds();
			double AccelerationRate = 0;

			// Handle Acceleration Rate
			if (!InAir)
			{
				JumpHeight = 0;
				Extra = 1;
				AccelerationGain = TrueAccelerationGain;
			}
			else
			{
				AccelerationDampening = 1;
				AccelerationGain = 0.005;
			}

			// For hitting walls to change direction!
			if (Type == 1)
			{
				if (!Inverse)
					AccelerationRate = AccelerationGain * dt.asMilliseconds();
				else
					AccelerationRate = -AccelerationGain * dt.asMilliseconds();
			}

			//AccelerationRate = AccelerationGain * dt.asMilliseconds();

			// Acceleration biding
			Acceleration = clamp(Acceleration + AccelerationRate, -MaxSpeed, MaxSpeed);
			Acceleration *= AccelerationDampening;
			X = Acceleration;
			Y = Gravity + JumpHeight;

			Gravity += GravityUnit * dt.asMilliseconds();
			GravityUnit = TrueGravityUnit;

			// Handle Plr Location, Orientation, & Acceleration
			Position = Position + Vector2(X, Y);
			Velocity = (Position - LastPos);
			NextPos = Position + Velocity;
			// Collision Handling
			InAir = true;

			for (unsigned int i = 0; i != Tile::Tiles.size(); i++) {
				//std::cout << Tile::Tiles.size() << std::endl;
				//std::cout << &Tile::Tiles[i] << std::endl;
				Collide(Tile::Tiles[i].Sprite, Tile::Tiles[i].Collideable);
			}

			BoundingRect.setPosition(sf::Vector2f(Position.X, Position.Y));
			BoundingRect.setFillColor(sf::Color::Transparent);
			//BoundingRect.setOutlineColor(sf::Color::Blue);
			//BoundingRect.setOutlineThickness(2);
			BoundingRect.setOrigin(sf::Vector2f(15, -20));
			BoundingRect.setSize(sf::Vector2f(30, 30));

			if (Velocity.Magnitude() > .01)
			{
				if (spriteClock.getElapsedTime().asSeconds() > (.2 / Velocity.Magnitude())) {
					if (!InAir)
					{
						// Walking
						if (rectSourceSprite.left >= WalkAnimation)
							rectSourceSprite.left = SpritePosition.x;
						else
							rectSourceSprite.left += WalkAnimation;

						spriteClock.restart();
					}

					sprite.setTextureRect(rectSourceSprite);
				}


			}
			else if (!InAir)
			{
				rectSourceSprite.left = SpritePosition.x;
				sprite.setTextureRect(rectSourceSprite);
				spriteClock.restart();
			}

			// Calculate Velocity of Player & reset last position of player to re-calculate velocity when done
			LastPos = Position;
		}

		sprite.setPosition(Position.X, Position.Y);
		window.draw(sprite);
		window.draw(BoundingRect);
	}

	void Collide(sf::Sprite obj, bool CanCollide)
	{
		sf::FloatRect Area;
		sf::FloatRect RectBounds = BoundingRect.getTransform().transformRect(BoundingRect.getLocalBounds());
		bool AreColliding = obj.getGlobalBounds().intersects(BoundingRect.getGlobalBounds(), Area);
		sf::Vector3f Manifold;
		if (AreColliding && CanCollide)
		{
			/*
			Vector2 offset(0,0);
			//std::cout << Manifold.x << "," << Manifold.y << " | " << Manifold.z << std::endl;;
			*/
			sf::Vector2f CollisionNormal = (obj.getPosition() - sf::Vector2f(RectBounds.left, RectBounds.top));
			Manifold = getManifold(Area, CollisionNormal);
			sf::Vector2f Normal(Manifold.x, Manifold.y);

			if (Manifold.x != 0)
			{
				Position.X = Position.X + Manifold.x * Manifold.z;
				Acceleration *= .5;

				if (Velocity.Magnitude() <= .8)
					Inverse = !Inverse;
			}
				
			if (Manifold.y != 0)
			{

				Gravity += GravityUnit * 2;
				Position.Y = (Position.Y + Manifold.y * Manifold.z);
				if (Manifold.y == -1)
				{
					Gravity = 0;
					GravityUnit = 0;
					InAir = false;
				}

			}
			/*if (Area.width > Area.height)
			{
				if (Area.contains({ Area.left, BoundingRect.getPosition().y }))
				{
					// Up side crash
					//std::cout << "Up" << std::endl;
					Position = Vector2(Position.X, Position.Y + Area.height);
				}
				else
				{
					// Down side crash
					//std::cout << "Down" << std::endl;

					Position = Vector2(Position.X, Position.Y - Area.height);
				}
			}
			else if (Area.width < Area.height)
			{
				if (Area.contains({ BoundingRect.getPosition().x + BoundingRect.getGlobalBounds().width - 1.f, Area.top + 1.f }))
				{
					//Right side crash
					std::cout << "RIGHT!" << std::endl;
					Position.X = Position.X - Area.width;
				}
				else
				{
					//Left side crash
					//std::cout << "Left" << std::endl;
					Position.X = Position.X + Area.width;
				}
			}*/
			/*if (Manifold.y == -1)
			{
				Gravity = 0;
				GravityUnit = 0;
			}
			if (abs(CollisionNormal.x) > abs(CollisionNormal.y))
				offset.X = ((CollisionNormal.x < 0) ? -1 : 1) * Overlap.width;
			std::cout << offset.X << std::endl;
			if (abs(CollisionNormal.x) < abs(CollisionNormal.y))
				offset.Y = ((CollisionNormal.y < 0) ? -1 : 1) * Overlap.height;
			Position = Position - offset;*/
		}
	};

	void Kill()
	{
		if (Alive)
		{


			if (!SoundBuffer.loadFromFile("audio/stomp.ogg"))
				std::cout << "Cannot load death sound!" << std::endl;

			Death.setVolume(50);
			Death.setBuffer(SoundBuffer);
			Death.play();

			rectSourceSprite.left = SpritePosition.x+DeathAnimation;
			sprite.setTextureRect(rectSourceSprite);

			Alive = false;
			X = 0;

			std::thread t([&]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				sprite.setColor(sf::Color::Transparent);
				//ptr = (double*)(&TrueGravityUnit);
				//*ptr = .05;

				});

			t.detach();
		}
	}

	Entity(const int type, std::string sheet, Vector2 size, Vector2 wpos, sf::Vector2f scale, sf::Vector2f opos, sf::Vector2f SpriteOrigin, Vector2 anims)
	{
		Position = wpos;
		Type = type;
		rectSourceSprite = sf::IntRect(0, 0, size.X, size.Y);
		texture.loadFromFile(sheet);
		sprite = sf::Sprite(texture, rectSourceSprite);
		sprite.setScale(scale);
		BoundingRect.setSize(scale);
		BoundingRect.setPosition(sf::Vector2f(Position.X, Position.Y));
		rectSourceSprite.left = opos.x;
		rectSourceSprite.top = opos.y;
		sprite.setOrigin(SpriteOrigin);
		sprite.setTextureRect(rectSourceSprite);
		SpritePosition = opos;
		WalkAnimation = anims.X;
		DeathAnimation = anims.Y;
		sprite.setPosition(Position.X, Position.Y);

		Entities.push_back(this);
	}

private:
	Vector2 Position = Vector2(0, 0);
	Vector2 Velocity = Vector2(0, 0);
	Vector2 LastPos = Vector2(0, 0);
	Vector2 NextPos = Vector2(0, 0);

	sf::Texture texture;
	sf::Clock clock;
	sf::Clock spriteClock;
	sf::IntRect rectSourceSprite;
	sf::Vector2f SpritePosition;
	double WalkAnimation;
	double DeathAnimation;

	bool InAir = false;
	bool Inverse = true;
	bool Rendered = false;
	int Type = 0;

	double X = 0; // These values are to construct another Vector2 to come into play with overall acceleration to create a feel of 'ease'
	double Y = 0;
	double Extra = 1;

	double Gravity = 0;
	double GravityUnit = 0;
	double JumpHeight = 0;

	double Dir = 1;
	double LastDir = 1;
	double AccelerationGain = 0.2;
	double AccelerationDampening = .95;

	const double TrueJumpHeight = -1.5;
	const double TrueGravityUnit = 0.01;
	const double TrueAccelerationGain = .02;
	const double TrueAccelerationDampening = .95;
	
	sf::Sound Death;
	sf::SoundBuffer SoundBuffer;
};
std::vector<Entity*> Entity::Entities;

class Player {
public:
	sf::Sprite sprite;
	double Acceleration = 0;
	void Update() {
		// dT
		//std::cout << Position.X << "|" << Position.Y << std::endl;
		if (Position.Y >= KillFloor)
			Die();
		if (Position.X >= WinPosition)
			Win();

		sf::Time dt = clock.restart();
		double MaxSpeed = .5;
		double AccelerationRate = 0;
		view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		float camX = Position.X;
		float camY = Position.Y;
		if (CAMBOUNDS.X > Position.X)
			camX = CAMBOUNDS.X;
		if (CAMBOUNDS.Y < Position.Y)
			camY = CAMBOUNDS.Y;

			view.setCenter(camX, camY);
			window.setView(view);

			// Handle Acceleration Rate
			if (!InAir)
			{
				JumpHeight = 0;
				Extra = 1;
				AccelerationGain = TrueAccelerationGain;
				AccelerationDampening = TrueAccelerationDampening;
			}
			else
			{
				AccelerationDampening = 1;
				AccelerationGain = 0.005;
			}
			// To calculate whether the player changes direction, so that we can effectively have them slide in the initial direction
			// before continuing
			//std::cout << Velocity.X << " | " << Dir << std::endl;
			int SpeedDifference = abs((Velocity.X/2.5) - Dir);
			if (SpeedDifference != 0 && !InAir && isMoving())
			{
				AccelerationDampening = .99;
				AccelerationGain = 0.005;
			}


			if (isMoving())
			{
				AccelerationRate = AccelerationGain;
			}
			else
			{
				AccelerationRate *= AccelerationDampening * dt.asMilliseconds();
			}

			// Check which direction they're facing
			//JumpHeight = clamp(JumpHeight + .5, -100.0, 0.0);
			if (Alive)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					if (!InAir)
						Dir = 1;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					if (!InAir)
						Dir = -1;
					AccelerationRate = AccelerationRate * -1;
				}


				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !InAir)
				{
					HoldingJump = true;
					InAir = true;
					Gravity = 0;

					if (!SoundBuffer.loadFromFile("audio/jump.ogg"))
						std::cout << "Unable to load jump sound!" << std::endl;

					Jump.setVolume(50);
					Jump.setBuffer(SoundBuffer);
					Jump.play();
				}
				else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					HoldingJump = false;
			}

			if (InAir)
			{

				if (HoldingJump)
					Extra = clamp(Extra + 0.1, 1.0, JumpApex);

				if (Extra != JumpApex && HoldingJump)
					JumpHeight = (TrueJumpHeight - (Extra)); // Problem lies here!
			}
			else
				Jump.stop();

			// Acceleration biding

			Acceleration = clamp(Acceleration + AccelerationRate, -MaxSpeed, MaxSpeed);
			Acceleration *= AccelerationDampening;
			X = Acceleration * dt.asMilliseconds();
			Y = (Gravity + JumpHeight); //* dt.asMilliseconds();
			Gravity += TrueGravityUnit;
			// Handle Plr Location, Orientation, & Acceleration
			Position = Position + Vector2(X, Y);
			if (Position.X <= MAPBOUNDS.X)
			{
				Acceleration = 0;
				Position.X = MAPBOUNDS.X;
			}

			Velocity = (Position - LastPos);
			NextPos = Position + Velocity;
			// Collision Handling
			InAir = true;
			if (Alive)
			{
				for (unsigned int i = 0; i != Tile::Tiles.size(); i++) {
					//std::cout << Tile::Tiles.size() << std::endl;
					//std::cout << &Tile::Tiles[i] << std::endl;
					Collide(Tile::Tiles[i].Sprite, Tile::Tiles[i].Collideable);
				}
			}
			

			// Enemy Collision
			for (unsigned int i = 0; i != Entity::Entities.size(); i++) {
				Entity* Ety = Entity::Entities.at(i);
				Overlapping(Ety);
				//std::cout << Overlap << std::endl;
				//std::cout << Overlap << std::endl;
			}


			BoundingRect.setPosition(sf::Vector2f(Position.X, Position.Y));
			BoundingRect.setFillColor(sf::Color::Transparent);
			//BoundingRect.setOutlineColor(sf::Color::Blue);
			//BoundingRect.setOutlineThickness(1);
			BoundingRect.setOrigin(sf::Vector2f(15, -20));
			BoundingRect.setSize(sf::Vector2f(30, 30));

			// Calculate Velocity of Player & reset last position of player to re-calculate velocity when done
			sprite.setPosition(Position.X, Position.Y);
			//std::cout << (abs(SpeedDifference)) << std::endl;
			if (SpeedDifference == 0)
				sprite.setScale(sf::Vector2f(-Dir, 1));
			// Walk animation;

			if (Alive)
			{
				if (Velocity.Magnitude() > .01)
				{

					if (SpeedDifference != 0 && isMoving() && !InAir && Velocity.Magnitude() > .8)
					{
						rectSourceSprite.left = 330; // Sliding
						sprite.setTextureRect(rectSourceSprite);
						sprite.setScale(sf::Vector2f(Dir, 1));
					}

					if (spriteClock.getElapsedTime().asSeconds() > (.2 / Velocity.Magnitude())) {
						if (!InAir)
						{
							// Walking
							if (rectSourceSprite.left >= 63)
								rectSourceSprite.left = 0;
							else
								rectSourceSprite.left += 63;

							spriteClock.restart();
						}
						else if (InAir && abs(Gravity) > 1)
							rectSourceSprite.left = 195; // Jumping

						sprite.setTextureRect(rectSourceSprite);
					}


				}
				else if (!InAir)
				{
					rectSourceSprite.left = 0;
					sprite.setTextureRect(rectSourceSprite);
					spriteClock.restart();
				}
			}
			
		window.draw(sprite);
		window.draw(BoundingRect);

		LastPos = Position;
	}

	void Overlapping(Entity* ety)
	{
		//std::cout << obj.getPosition().x << std::endl;
		sf::RectangleShape obj = ety->BoundingRect;
		sf::FloatRect Area;
		sf::FloatRect RectBounds = BoundingRect.getTransform().transformRect(BoundingRect.getLocalBounds());
		sf::Vector2f CollisionNormal = (obj.getPosition() - sf::Vector2f(RectBounds.left, RectBounds.top));
		bool Colliding = obj.getGlobalBounds().intersects(BoundingRect.getGlobalBounds(), Area);
		sf::Vector3f Manifold = getManifold(Area, CollisionNormal);

		if (Colliding)
		{
			if (Manifold.x != 0 && ety->Alive)
				Die();
			else if (Manifold.y == -1 && Alive)
			{
				if (ety->Alive)
				{
					JumpHeight = -(Extra * 1.35);
					Gravity = 0;
					ety->Kill();
				}
			}	
		}
	}

	void Collide(sf::Sprite obj, bool CanCollide)
	{
		sf::FloatRect Area;
		sf::FloatRect RectBounds = BoundingRect.getTransform().transformRect(BoundingRect.getLocalBounds());
		bool AreColliding = obj.getGlobalBounds().intersects(BoundingRect.getGlobalBounds(), Area);
		sf::Vector3f Manifold;
		if (AreColliding && CanCollide)
		{
			/*
			Vector2 offset(0,0);
			//std::cout << Manifold.x << "," << Manifold.y << " | " << Manifold.z << std::endl;;
			*/
			sf::Vector2f CollisionNormal = (obj.getPosition() - sf::Vector2f(RectBounds.left, RectBounds.top));
			Manifold = getManifold(Area, CollisionNormal);
			sf::Vector2f Normal(Manifold.x, Manifold.y);

			

			if (Manifold.x != 0)
			{
				Position.X = Position.X + Manifold.x * Manifold.z;
				Acceleration *= .5;
			}
			if (Manifold.y != 0)
			{
				
				Gravity += GravityUnit*2;
				Position.Y = (Position.Y + Manifold.y * Manifold.z);
				if (Manifold.y == -1)
				{
					Gravity = 0;
					GravityUnit = 0;
					InAir = false;
				}
				else if (Manifold.y == 1)
				{
					JumpHeight *= .85;
					Extra = 0;
					HoldingJump = false;
				}
					
			}
			/*if (Area.width > Area.height)
			{
				if (Area.contains({ Area.left, BoundingRect.getPosition().y }))
				{
					// Up side crash
					//std::cout << "Up" << std::endl;
					Position = Vector2(Position.X, Position.Y + Area.height);
				}
				else
				{
					// Down side crash
					//std::cout << "Down" << std::endl;

					Position = Vector2(Position.X, Position.Y - Area.height);
				}
			}
			else if (Area.width < Area.height)
			{
				if (Area.contains({ BoundingRect.getPosition().x + BoundingRect.getGlobalBounds().width - 1.f, Area.top + 1.f }))
				{
					//Right side crash
					std::cout << "RIGHT!" << std::endl;
					Position.X = Position.X - Area.width;
				}
				else
				{
					//Left side crash
					//std::cout << "Left" << std::endl;
					Position.X = Position.X + Area.width;
				}
			}*/
			/*if (Manifold.y == -1)
			{
				Gravity = 0;
				GravityUnit = 0;
			}
			if (abs(CollisionNormal.x) > abs(CollisionNormal.y))
				offset.X = ((CollisionNormal.x < 0) ? -1 : 1) * Overlap.width;
			std::cout << offset.X << std::endl;
			if (abs(CollisionNormal.x) < abs(CollisionNormal.y))
				offset.Y = ((CollisionNormal.y < 0) ? -1 : 1) * Overlap.height;
			Position = Position - offset;*/
		}
	};

	void Die()
	{
		if (Alive)
		{
			Alive = false;
			BGM.stop();
			rectSourceSprite.left = 910;
			rectSourceSprite.top = 90;
			rectSourceSprite.height = 50;

			sprite.setTextureRect(rectSourceSprite);

			if (!SoundBuffer.loadFromFile("audio/ouch.ogg"))
				std::cout << "Unable to load death sound!" << std::endl;

			Death.setVolume(50);
			Death.setBuffer(SoundBuffer);
			Death.play();

			
			Acceleration = 0;
			X = 0;
			Gravity = 0;
			Velocity.X = 0;
			JumpHeight = 0;
			Extra = 0;
			HoldingJump = 0;
			TrueGravityUnit = 0;
			//double* ptr;
			//ptr = (double*)(&TrueGravityUnit);
			//*ptr = 0;
			std::thread t([&]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				Gravity = -5;
				TrueGravityUnit = .05;
				//ptr = (double*)(&TrueGravityUnit);
				//*ptr = .05;

				std::this_thread::sleep_for(std::chrono::milliseconds(2500));

				window.close();
				});

			t.detach();

			
		}
		
	}

	void Win()
	{
		if (!WON)
		{
			WON = true;
			window.close();
			BGM.stop();
		}
	}

	Player() {
		rectSourceSprite = sf::IntRect(0, 0, 50, 100);
		texture.loadFromFile("sprites/mario.png");
		sprite = sf::Sprite(texture, rectSourceSprite);
		sprite.setOrigin(sf::Vector2f(27, 0));
		Position = Vector2(5300, 100);
	}
private:
	// Movement related values
	Vector2 Position = Vector2(0, 0);
	Vector2 Velocity = Vector2(0, 0);
	Vector2 LastPos = Vector2(0, 0);
	Vector2 NextPos = Vector2(0, 0);

	sf::Texture texture;
	sf::Clock clock;
	sf::Clock spriteClock;
	sf::IntRect rectSourceSprite;
	sf::RectangleShape BoundingRect;
	// Variables
	bool Alive = true;
	bool InAir = false;
	bool HoldingJump = false;

	double X = 0; // These values are to construct another Vector2 to come into play with overall acceleration to create a feel of 'ease'
	double Y = 0;
	double Extra = 1;
	
	double Gravity = 0;
	double GravityUnit = 0;
	double JumpHeight = 0;

	double Dir = 1;
	double LastDir = 1;
	double AccelerationGain = .02;
	double AccelerationDampening = .95;

	// Constant Variables (some being "constant")
	const double TrueJumpHeight = -1.5;
	double TrueGravityUnit = .05;
	const double TrueAccelerationGain = .02;
	const double TrueAccelerationDampening = .95;
	const double JumpApex = 3.5;

	bool isMoving()
	{
		if (Alive)
		{
			for (int i = 0; i < 2; i++)
			{
				if (sf::Keyboard::isKeyPressed(DirInputs[i]))
				{
					return true;
				}
			}	
		}
		return false;
	}

	sf::Sound Jump;
	sf::Sound Death;
	sf::SoundBuffer SoundBuffer;
};


/*
ENTITY TYPES:
0 - Idle
1 - Walking
*/


class TileMap
{
public:
	Map MappedTiles;
	sf::Vector2u MaxSize;
	TileMap(Sketch t_Sketch, const int PerRow, const float Size, const Vector2 EPSILON, const sf::Vector2f Origin, const std::string& tilesheet, const std::vector<int>& IgnoreList) {
		GridSizeF = Size;
		MaxSize.x = t_Sketch[0].size();
		MaxSize.y = t_Sketch.size();

		/*
		for (int i = 0; i-1 < t_Sketch[0].size() - 1; i++)
		{
			std::cout << i << std::endl;
			//MappedTiles.push_back(std::vector<Tile>());
			MappedTiles[i].resize(MaxSize.y);  // resize each of the contained vectors
			for (int j = 0; j < t_Sketch.size() - 1; j++)
			{
				//std::cout << t_Sketch[i][j];
				MappedTiles[i][j] = Tile(t_Sketch[i][j], GridSizeF * i, sf::Vector2f(i * GridSizeF, j * GridSizeF));
			}
		}
		*/
		/*std::cout << MaxSize.x << " & " << MaxSize.y << std::endl;
		MappedTiles.resize(MaxSize.y);  // resize top level vector
		for (unsigned int i = 0; i != MaxSize.y; i++) {
			MappedTiles[i].resize(MaxSize.x);
			for (unsigned int j = 0; j != MaxSize.x; j++) {

				std::cout << MappedTiles[j].size() << std::endl;
				MappedTiles[i][j] = Tile(t_Sketch[i][j], GridSizeF, sf::Vector2f(i * GridSizeF, j * GridSizeF));
			}
			std::cout << std::endl;
		}*/


		//std::cout << MaxSize.x << " & " << MaxSize.y << std::endl;
		MappedTiles.resize(MaxSize.y);  // resize top level vector
		for (unsigned int i = 0; i != MaxSize.y; i++) {
			MappedTiles[i].resize(MaxSize.x);
			for (unsigned int j = 0; j != MaxSize.x; j++) {
				bool CanCollide = true;
				int Opacity = 255;
				if (std::find(IgnoreList.begin(), IgnoreList.end(), t_Sketch[i][j]) != IgnoreList.end())
				{
					if (IgnoreList[0] == t_Sketch[i][j])
						Opacity = 0;
					CanCollide = false;
				}

				Tile *t = new Tile(t_Sketch[i][j], PerRow, GridSizeF, EPSILON, sf::Vector2f(j * EPSILON.X, i * EPSILON.Y), Origin, tilesheet, CanCollide, Opacity);
				//Tile t(15, 12, 10.0f, Vector2(16, 16), sf::Vector2f(10, 10), "sprites/map.png");
				MappedTiles[i][j] = *t;
			}
			//std::cout << std::endl;
		}
	}

	void Render() {
		for (auto& x : MappedTiles) {
			for (auto& y : x) {
				y.Render(window);
			}
		}
	}

private:
	float GridSizeF = 0;
	
	
};


// Example(s) To help me create Tiles & mapping!
/* class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
	{
		// load the tileset texture
		if (!m_tileset.loadFromFile(tileset))
			return false;

		// resize the vertex array to fit the level size
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		// populate the vertex array, with one quad per tile
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
				// get the current tile number
				int tileNumber = tiles[i + j * width];

				// find its position in the tileset texture
				int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
				int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

				// get a pointer to the current tile's quad
				sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			}

		return true;
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_tileset;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};
*/
/*class Map {
public:

	Map(std::wstring InitSketch) {
		Sketch = InitSketch;
		//MapHeight = CountLines(Sketch);
		//MapWidth = (Sketch.length() / MapHeight) - 1; // To account for Line Feed
		std::cout << "Map is: " << MapWidth << " X " << MapHeight;
	}

	void Update() {
		// Utility Lambdas
		
	}

private:
	std::wstring Sketch;

	int MapWidth = 0;
	int MapHeight = 0;

	int TileWidth = 16;
	int TileHeight = 16;

	int VisibleTilesX = ScreenWidth / TileWidth;
	int VisibleTilesY = ScreenHeight / TileHeight;

	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;

	unsigned int CountLines(std::wstring wstr) {
		int newlines = 0;
		std::wstring::iterator it;
		for (it = wstr.begin(); it != wstr.end();
			it++) {
			// Print current character
			if (*it == 10) {
				newlines++;
			}
		}
		return newlines;
	}
};*/
/*class Tile {
public:
	
	sf::Sprite sprite;
	
	void Update() {
		int beta = 0;
		for (int i = 0; i < Alpha; i++) {
			if (i % 29 == 0 && i != 0) {
				beta += 1;
			}
		}

		std::cout << beta;

		rectSourceSprite = sf::IntRect(Alpha * SPRITE_EPSILON, beta * SPRITE_EPSILON, SPRITE_EPSILON, SPRITE_EPSILON);
		sprite = sf::Sprite(texture, rectSourceSprite);
		sprite.setOrigin(sf::Vector2f(10, -15 + (Size * 4)));
		sprite.setPosition(Position.X, Position.Y);
		sprite.setScale(sf::Vector2f(Size, Size));
	};

	Tile(int alpha, int size, Vector2 t_Position) {
		Position = t_Position;
		Size = size;
		Alpha = alpha;
		texture.loadFromFile("sprites/tilesheet.png");
		Update();

		std::cout << this << std::endl;
		//Array.push_back(*this);
	}

private:
	Vector2 Position = Vector2(0, 0);
	int Size;
	int Alpha;
	bool Collidable;

	sf::Texture texture;
	sf::IntRect rectSourceSprite;
};*/