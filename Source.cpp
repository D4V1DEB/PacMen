#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "ghostmoving.h"
#include "scoreboard.h"
#include <SFML/Window.hpp>
#include <string>
using namespace sf;
using namespace std;

scoreboard score_board;
int maze1[50][50];
int dead = true;
int score = 0;
bool win=1;
int lives = 3;
bool mood = false;  
bool Abnb_check1 = false;
bool Abnb_check2 = false;
string map_path = "maps/map1.txt";
int const rows = 28;
int const cols = 28;
int Dir = 0, cnt = 0, fright = 0;
bool vary = 0, haha = 1;


int olix = 0, oliy = -2;
int inky_cnt = 0;

Texture backGround, pac, wall, blinky, dot, bigdot, pink;
Sprite  backGroundsprite, pacSprite, wallSprite, blinkySprite, dotSprite, bigdotSprite, pinkSprite;

Texture backgr, lives_pacman1, lives_pacman2, lives_pacman3, lives_pacman4, lives_pacman5, inky, clyde;
Sprite  backgr_score, lives_pacman_sprite1, lives_pacman_sprite2, lives_pacman_sprite3, lives_pacman_sprite4, lives_pacman_sprite5, inkySprite, clydeSprite;

Text  text_score, text, control, control1, control2, control3, control4;
Font font, fon, fo;
string s;
void declare();
void detectdirection(int x, int y);
void playeranimation(int dir, int cnt);
int pac_diffPOS(int curr_pac_speed);

void enterusernamefn();
void frightmode(int x);
void startfn();
void gamefn(int pacman_speed);
void scoreBoardfn();
void draw_your_maze();


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



	backgr.loadFromFile("img/Back__Score.png"); 
	backgr_score.setTexture(backgr);
	backgr_score.setColor(Color(255, 255, 255, 64));
	backgr_score.setPosition(Vector2f(896, 0));


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
	text_score.setString("Puntuacion: ");  //To print word "Score"

	text.setFont(fo);
	text.setPosition(1400, 160); //1248
	text.setFillColor(Color::Blue);
	text.setStyle(Text::Bold);
	text.setString(s);                 //To print the score 


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

void gamefn(int pacman_speed)
{

	Return_game_to_the_start();
	RenderWindow pacman(VideoMode(1920, 1080), "Pacman");
	ghostmoving blinky(maze1, cols, rows, 2);

	int xx = 0, yy = 0;
	//pacman.setFramerateLimit(100);
	// Besh
	bool move_ch = 1; int Besh_x = 0, Besh_y = 0 ;
	while (pacman.isOpen())
	{
		score_board.Save_Score_Board(score);
		//Abnb
		if (pacSprite.getGlobalBounds().intersects(blinkySprite.getGlobalBounds()))
		{
			if (!fright)      //Mood --> Chase  
			{
				lives--;
				Return_game_to_the_start();
			}
			else
			{
				blinkySprite.setPosition(Vector2f(384, 416));
				score += 200;
				sleep(seconds(1));
			}

		}
		if (pacSprite.getGlobalBounds().intersects(pinkSprite.getGlobalBounds()))
		{
			if (!fright)     //Mood --> Chase 
			{
				lives--;
				Return_game_to_the_start();
			}
			else
			{
				pinkSprite.setPosition(Vector2f(416, 416));
				score += 200;
				sleep(seconds(1));
			}
		}
		if (pacSprite.getGlobalBounds().intersects(inkySprite.getGlobalBounds()))
		{
			if (!fright)      //Mood --> Chase 
			{
				lives--;
				Return_game_to_the_start();
			}
			else
			{
				inkySprite.setPosition(Vector2f(448, 416));
				score += 200;
				sleep(seconds(1));
			}
		}
		if (pacSprite.getGlobalBounds().intersects(clydeSprite.getGlobalBounds()))
		{
			if (!fright)      //Mood --> Chase 
			{
				lives--;
				Return_game_to_the_start();
			}
			else
			{
				clydeSprite.setPosition(Vector2f(480, 416));
				score += 200;
				sleep(seconds(1));
			}
		}

		if (!lives)	//Besh
		{
			RenderWindow lost(VideoMode(1920, 1080), "Oops !");

			pacman.close();
			sleep(seconds(3));
			lost.close();
			lives = 3;
			map_path = "maps/map1.txt";
			score = 0;
			main();
		}

		cnt = (cnt + 1) % 21;


		s = to_string(score);
		text.setString(s);

		Event event;
		while (pacman.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				pacman.close();
				main();
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
				xx = pacman_speed, yy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Left))
				xx = -pacman_speed, yy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Up))
				yy = -pacman_speed, xx = 0;
			if (Keyboard::isKeyPressed(Keyboard::Down))
				yy = pacman_speed, xx = 0;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				pacman.close();
				main();
			}
			//Besh
			if (move_ch)
			{
				Besh_x = xx;
				Besh_y = yy;
				move_ch = 0;
			}
		}
		playeranimation(Dir, cnt);

		int y = (pacSprite.getPosition().x + pac_diffPOS(xx)) / 32;
		int x = (pacSprite.getPosition().y + pac_diffPOS(yy)) / 32;

		int Besh_gety = (pacSprite.getPosition().x + pac_diffPOS(Besh_x)) / 32;
		int Besh_getx = (pacSprite.getPosition().y + pac_diffPOS(Besh_y)) / 32;

		int xmod = pacSprite.getPosition().y, ymod = pacSprite.getPosition().x;


		if (!(xmod % 32) && !(ymod % 32))
		{

			if (maze1[x][y] != 1) {
				pacSprite.move(xx, yy), Besh_x = xx, Besh_y = yy;
				detectdirection(xx, yy);
			}


			else if (maze1[Besh_getx][Besh_gety] != 1)
			{

				pacSprite.move(Besh_x, Besh_y);

				detectdirection(Besh_x, Besh_y);
			}

			else
			{
				//if (!(xmod % 32) && !(ymod % 32))
				{
					pacSprite.move(0, 0);
					xx = yy = 0;
				}
			}
		}

		else pacSprite.move(Besh_x, Besh_y);
		pacman.clear();

		if (fright != 0)
			fright--;
		frightmode(fright);
		blinkySprite = blinky.findpath(pacSprite, blinkySprite);


		win = true;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
			{
				int pacx = pacSprite.getPosition().x / 32, pacy = pacSprite.getPosition().y / 32;
				if (maze1[i][j] == 1)
				{
					wallSprite.setTextureRect(IntRect(0, 0, 32, 32));
					wallSprite.setPosition(j * 32, i * 32);
					pacman.draw(wallSprite);
				}
				else if (maze1[i][j] == 2)
				{
					win = false;
					dotSprite.setTextureRect(IntRect(0, 0, 16, 16));
					dotSprite.setColor(Color::Red);
					dotSprite.setPosition(j * 32 + 8, i * 32 + 8);
					pacman.draw(dotSprite);
					if (pacx == j && pacy == i)
					{
						maze1[i][j] = 0;
						score += 10;  //Abnb 

					}
				}
				else if (maze1[i][j] == 3)
				{
					win = false;
					bigdotSprite.setTextureRect(IntRect(0, 0, 32, 32));
					bigdotSprite.setPosition(j * 32, i * 32);
					pacman.draw(bigdotSprite);
					if (pacx == j && pacy == i)
					{
						maze1[i][j] = 0, fright = 1000;
						score += 50;  //Abnb 

					}
				}

			}

		/*
		Besh
		*/
		// move to next level || end
		if (win==true)
		{
			sleep(seconds(1));

			if (map_path[8] < '3')
			{
				map_path[8]++;
				declare();
				pacman.close();
				gamefn(2);
				
			}

			else
			{
				RenderWindow win(VideoMode(1920, 1080), "Felicitaciones!");
				win.display();
				pacman.close();
				sleep(seconds(3));
				win.close();
				lives = 3;
				declare();

			}
		}
		if (score >= 2000 && Abnb_check1 == false)
		{
			lives++;
			lives = min(lives, 5); //Besh
			Abnb_check1 = true;

		}
		if (score >= 4500 && Abnb_check2 == false)
		{
			lives++;//Besh
			lives = min(lives, 5);
			Abnb_check2 = true;

		}

		pacman.draw(blinkySprite);
		pacman.draw(pinkSprite);
		pacman.draw(inkySprite);
		pacman.draw(clydeSprite);
		pacman.draw(pacSprite);
		pacman.draw(backgr_score);
		pacman.draw(text); //ok
		pacman.draw(text_score);//ok
		pacman.draw(control);
		pacman.draw(control1);
		pacman.draw(control2);
		pacman.draw(control3);
		pacman.draw(control4);
		if (lives >= 1)
			pacman.draw(lives_pacman_sprite1);
		if (lives >= 2)
			pacman.draw(lives_pacman_sprite2);
		if (lives >= 3)
			pacman.draw(lives_pacman_sprite3);
		if (lives >= 4)
			pacman.draw(lives_pacman_sprite4);
		if (lives >= 5)
			pacman.draw(lives_pacman_sprite5);
		pacman.display();
		if (dead)
		{

			sleep(seconds(4));
			dead = false;
		}
	}
}
void detectdirection(int x, int y)
{
	if (x == 2)
		Dir = 0;
	if (x == -2)
		Dir = 2;
	if (y == 2)
		Dir = 1;
	if (y == -2)
		Dir = 3;
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
int pac_diffPOS(int Next_moving)
{
	int Next_tile = 0;
	if (Next_moving > 0)  Next_tile = 32;
	else if (Next_moving < 0)  Next_tile = -32;
	else Next_tile = 0;

	return Next_tile;
}

void playeranimation(int dir, int cnt)
{
	pacSprite.setTextureRect(IntRect(cnt/3 * 32, dir * 32, 32, 32));
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
				//---------------------(Control on Moving in The start Menu  )-------------------
			case Event::KeyReleased:

				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;

				case Keyboard::Down:
					menu.MoveDown();
					break;
					//----------------------------------(Control on The Return value )---------------------------
				case Keyboard::Return:

					switch (menu.GetPressedItem())
					{
					case 0:                        // start game
						startScreen.close();
						gamefn(2);
						break;
					}

					break;
				}

				break;
				//---------------------------------------------------------------------------
			case Event::Closed:
				startScreen.close();
				break;
				//---------------------------------------------------------------------------
			}
		}


		startScreen.clear();
		menu.draw(startScreen);
		startScreen.draw(backGroundsprite);
		startScreen.display();
	}

}

