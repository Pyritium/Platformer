#pragma once

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int KillFloor = 1000;
const int WinPosition = 6173;
bool WON = false;
bool GAME_RUNNING = false;

const Vector2 MAPBOUNDS = Vector2(-50, 8000);


const Vector2 CAMBOUNDS = Vector2(352, 500);

const int SPRITE_EPSILON = 33;
constexpr unsigned char CELL_SIZE = 16;



class Tile
{
public:
	bool Collideable = true;

	static std::vector<Tile> Tiles;
	sf::Sprite Sprite;
	Tile() {};
	Tile(int CorrespondingIndexToCell, int PerRow, float GridSizeF, Vector2 EPSILON, sf::Vector2f Position, const sf::Vector2f Origin, const std::string& m_tilesheet, bool Collision, int Alpha) {
		//CellType = static_cast<Cell>(CorrespondingIndexToCell);
		//std::cout << "Tile made: " << CellType << std::endl; ;
		//shape.setSize(sf::Vector2f(GridSizeF, GridSizeF));
		//shape.setPosition(Position);

		/*int Row = 0;
		int SubtractBy = 0;
		std::cout << CorrespondingIndexToCell << std::endl;
		for (int i = 0; i < CorrespondingIndexToCell; i++)
		{
			if (i % PerRow == 0 && i != 0 && i >= PerRow)
			{
				std::cout << "!\n";
				Row+=1;
				SubtractBy += PerRow+1;
				break;
			}
		}*/
		Collideable = Collision;
		int Row = floor(CorrespondingIndexToCell / PerRow);
		int SubtractBy = (PerRow * Row);
		int Sum = CorrespondingIndexToCell - SubtractBy;
		//std::cout << Row;
		const int Delta = GridSizeF / 10;


		Texture.loadFromFile(m_tilesheet);
		sf::IntRect rectSourceSprite = sf::IntRect(EPSILON.X * Sum, Row * EPSILON.Y, EPSILON.X, EPSILON.Y);

		Sprite = sf::Sprite(Texture, rectSourceSprite);
		Sprite.setPosition(sf::Vector2f(Position.x * Delta, Position.y * Delta) + Origin);
		Sprite.setScale(sf::Vector2f(Delta, Delta));
		Sprite.setColor(sf::Color(255,255,255, Alpha));

		Tiles.push_back(*this);
	}


	void Render(sf::RenderWindow& window)
	{
		window.draw(Sprite);
	}

private:
	sf::Vector2f Position;
	sf::Texture Texture;

};

std::vector<Tile> Tile::Tiles;
typedef std::vector<std::vector<Tile>> Map;
typedef std::vector<std::vector<int>> Sketch;