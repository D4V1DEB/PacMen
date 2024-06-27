#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "scoreboard.h"
#include <SFML/Window.hpp>
#include <string>
using namespace sf;
using namespace std;

scoreboard score_board;
int maze1[50][50];
int dead = true;
int score = 0;
bool win=0;
int lives = 3;
string map_path = "maps/map1.txt";
int const rows = 28;
int const cols = 28;
int fright = 0;


Texture backGround, pac, wall, blinky, dot, bigdot, pink;
Sprite  backGroundsprite, pacSprite, wallSprite, blinkySprite, dotSprite, bigdotSprite, pinkSprite;

Texture backgr, lives_pacman1, lives_pacman2, lives_pacman3, lives_pacman4, lives_pacman5, inky, clyde;
Sprite  backgr_score, lives_pacman_sprite1, lives_pacman_sprite2, lives_pacman_sprite3, lives_pacman_sprite4, lives_pacman_sprite5, inkySprite, clydeSprite;

Text  text_score, text, control, control1, control2, control3, control4;
Font font, fon, fo;
string s;
void declare();
void enterusernamefn();
void frightmode(int x);
void gamefn(int pacman_speed);
void scoreBoardfn();



void Return_game_to_the_start();
int User_Check = 1;

int main() {
	 score = 0;
	declare();
	if (User_Check) {
		User_Check = 0;
		enterusernamefn();
		score_board.Save_Score_Board(0);
	}
	startfn();
}

void declare() {
	fstream inputStream;
	inputStream.open(map_path);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			inputStream >> maze1[i][j];

	backGround.loadFromFile("img/startbackground.jpg");
	backGroundsprite.setTexture(backGround);
	backGroundsprite.setTextureRect(IntRect(0, 0, 1920, 1080));
	backGroundsprite.setColor(Color(255, 255, 255, 64));

	dot.loadFromFile("img/dot.png");                              
	dotSprite.setTexture(dot);

	bigdot.loadFromFile("img/bigdot.png");               
	bigdotSprite.setTexture(bigdot);

	wall.loadFromFile("img/wall.jpg");                      
	wallSprite.setTexture(wall);

	pac.loadFromFile("img/sheet.png");                    
	pacSprite.setTexture(pac);
	pacSprite.setPosition(Vector2f(448, 704));
	pacSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	blinky.loadFromFile("img/g.png");                                        // Fantasma Red
	blinkySprite.setTexture(blinky);
	blinkySprite.setPosition(Vector2f(384, 416));
	blinkySprite.setTextureRect(sf::IntRect(0, 0, 28, 28));

	pink.loadFromFile("img/g3.png");
	pinkSprite.setTexture(pink);					        // Fantasma Rosa 
	pinkSprite.setPosition(Vector2f(416, 416));
	pinkSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	inky.loadFromFile("img/g1.png");
	inkySprite.setTexture(inky);						// Fantasma Celeste
	inkySprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	inkySprite.setPosition(Vector2f(448, 416));

	clyde.loadFromFile("img/g4.png");
	clydeSprite.setTexture(clyde);						// Fantasma Anaranjado
	clydeSprite.setPosition(Vector2f(480, 416));
	clydeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));



	if (!font.loadFromFile("font/prstartk.ttf"))
		cout << "Error" << endl;

	if (!fon.loadFromFile("font/prstartk.ttf"))
		cout << "Error" << endl;

	if (!fo.loadFromFile("font/prstartk.ttf"))
		cout << "Error" << endl;


	text_score.setFont(fo);
	text_score.setPosition(1056, 128);
	text_score.setFillColor(Color::White);
	text_score.setStyle(Text::Bold);
	text_score.setCharacterSize(80);
	text_score.setString("Puntuacion: ");  

	text.setFont(fo);
	text.setPosition(1400, 160);
	text.setFillColor(Color::Blue);
	text.setStyle(Text::Bold);
	text.setString(s);          


	control.setFont(fon);
	control.setPosition(1056, 416);
	control.setFillColor(Color::White);
	control.setStyle(Text::Bold);
	control.setCharacterSize(45);
	control.setString("Controles ");

	control1.setFont(font);
	control1.setPosition(960, 480);
	control1.setFillColor(Color::Green);
	control1.setString("Flechas Pacman");

	control2.setFont(font);
	control2.setPosition(960, 544);
	control2.setFillColor(Color::Green);
	control2.setString("P --> Pausa");

	control3.setFont(font);
	control3.setPosition(960, 608);
	control3.setFillColor(Color::Green);
	control3.setString("S --> Silencio");

	control4.setFont(font);
	control4.setPosition(960, 672);
	control4.setFillColor(Color::Green);
	control4.setString("Esc --> Salir ");


	lives_pacman1.loadFromFile("img/live.png");
	lives_pacman_sprite1.setTexture(lives_pacman1);
	lives_pacman_sprite1.setColor(Color::Yellow);
	lives_pacman_sprite1.setPosition(Vector2f(864 + 64, 288));
	lives_pacman_sprite1.setTextureRect(sf::IntRect(0, 0, 64, 64));

	lives_pacman2.loadFromFile("img/live.png");
	lives_pacman_sprite2.setTexture(lives_pacman2);
	lives_pacman_sprite2.setColor(Color::Yellow);
	lives_pacman_sprite2.setPosition(Vector2f(864 + 64 * 2, 288));
	lives_pacman_sprite2.setTextureRect(sf::IntRect(0, 0, 64, 64));

	lives_pacman3.loadFromFile("img/live.png");
	lives_pacman_sprite3.setTexture(lives_pacman3);
	lives_pacman_sprite3.setColor(Color::Yellow);
	lives_pacman_sprite3.setPosition(Vector2f(864 + 64 * 3, 288));
	lives_pacman_sprite3.setTextureRect(sf::IntRect(0, 0, 64, 64));

	lives_pacman4.loadFromFile("img/live.png");
	lives_pacman_sprite4.setTexture(lives_pacman4);
	lives_pacman_sprite4.setColor(Color::Yellow);
	lives_pacman_sprite4.setPosition(Vector2f(864 + 64 * 4, 288));
	lives_pacman_sprite4.setTextureRect(sf::IntRect(0, 0, 64, 64));

	lives_pacman5.loadFromFile("img/live.png");
	lives_pacman_sprite5.setTexture(lives_pacman5);
	lives_pacman_sprite5.setColor(Color::Yellow);
	lives_pacman_sprite5.setPosition(Vector2f(864 + 64 * 5, 288));
	lives_pacman_sprite5.setTextureRect(sf::IntRect(0, 0, 64, 64));

}

void enterusernamefn()
{
	RenderWindow username(VideoMode(1920, 1080), "Ingrese su nombre");
	while (username.isOpen())
	{
		Event event;
		while (username.pollEvent(event))
			score_board.Keyboard_Handling(event, username);
	}
}


void Return_game_to_the_start()
{
	dead = true;
	pacSprite.setPosition(Vector2f(448, 704));

	blinkySprite.setPosition(Vector2f(384, 416));

	pinkSprite.setPosition(Vector2f(416, 416));

	inkySprite.setPosition(Vector2f(448, 416));

	clydeSprite.setPosition(Vector2f(480, 416));

	sleep(seconds(2));

}


void frightmode(int x)
{
	if (x)
	{
		blinky.loadFromFile("img/fright.png");
		pink.loadFromFile("img/fright.png");
		inky.loadFromFile("img/fright.png");
		clyde.loadFromFile("img/fright.png");
	}
	else
	{
		blinky.loadFromFile("img/blinky.png");
		pink.loadFromFile("img/g3.png");
		inky.loadFromFile("img/g1.png");
		clyde.loadFromFile("img/g4.png");
	}
}
void startfn()
{

	RenderWindow startScreen(sf::VideoMode(1920, 1080), "Pacman", Style::Close | Style::Resize);
	Menu menu(startScreen.getSize().x, startScreen.getSize().y);
	while (startScreen.isOpen())
	{

		Event event;

		while (startScreen.pollEvent(event))
		{

			switch (event.type)
			{
				
			case Event::KeyReleased:

				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;

				case Keyboard::Down:
					menu.MoveDown();
					break;
					
				case Keyboard::Return:

					switch (menu.GetPressedItem())
					{
					case 0:                      
						startScreen.close();
						gamefn(2);
						break;
					}

					break;
				}

				break;
			
			case Event::Closed:
				startScreen.close();
				break;
		
			}
		}


		startScreen.clear();
		menu.draw(startScreen);
		startScreen.draw(backGroundsprite);
		startScreen.display();
	}

}

