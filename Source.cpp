#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <memory>
#include <thread>
#include "Menu.h"
#include "ghostmoving.h"
#include "ShortestRandom.h"
#include "scoreboard.h"
#include "Besh_Random.h"
#include "LostWin.h"
#include <SFML/Window.hpp>
#include <string>
#include <vector>
#include <algorithm>
using namespace sf;
using namespace std;

LostWin lost_win;
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

Texture backGround, pac, wall, blinkyTexture, dot, bigdot, pinkyTexture;
Sprite  backGroundsprite, pacSprite, wallSprite, blinkySprite, dotSprite, bigdotSprite, pinkySprite;

Texture backgr, lives_pacman1, lives_pacman2, lives_pacman3, lives_pacman4, lives_pacman5, inkyTexture, clydeTexture;
Sprite  backgr_score, lives_pacman_sprite1, lives_pacman_sprite2, lives_pacman_sprite3, lives_pacman_sprite4, lives_pacman_sprite5, inkySprite, clydeSprite;

Sound eatdot, eatbigdot ,eatghost , startsound ,extralive;
SoundBuffer eatdotBuffer, eatbigdotBuffer , eatghostbuffer , startsoundbuffer , extralivebuffer ;


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
	//Background
	backGround.loadFromFile("img/startbackground.jpg");
	backGroundsprite.setTexture(backGround);
	backGroundsprite.setTextureRect(IntRect(0, 0, 1920, 1080));
	backGroundsprite.setColor(Color(255, 255, 255, 64));



	backgr.loadFromFile("img/Back__Score.png"); 
	backgr_score.setTexture(backgr);
	backgr_score.setColor(Color(255, 255, 255, 64));
	backgr_score.setPosition(Vector2f(896, 0));

	//Sonidos sounds
	dot.loadFromFile("img/dot.png");    
	dotSprite.setTexture(dot);

	eatdot.setBuffer(eatdotBuffer);		
	eatdotBuffer.loadFromFile("effects/dot.wav");

	eatbigdot.setBuffer(eatbigdotBuffer);               
	eatbigdotBuffer.loadFromFile("effects/bigdot.wav");

	eatghost.setBuffer(eatghostbuffer);
	eatghostbuffer.loadFromFile("effects/pacman_eatghost.wav");

	startsound.setBuffer(startsoundbuffer);
	startsoundbuffer.loadFromFile("effects/pacman_beginning.wav");

	extralive.setBuffer(extralivebuffer);
	extralivebuffer.loadFromFile("effects/pacman_extrapac.wav");

	//Imagenes
	bigdot.loadFromFile("img/bigdot.png");                        
	bigdotSprite.setTexture(bigdot);


	wall.loadFromFile("img/wall.jpg");                           
	wallSprite.setTexture(wall);

	pac.loadFromFile("img/sheet.png");                      
	pacSprite.setTexture(pac);
	pacSprite.setPosition(Vector2f(448, 704));
	pacSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	blinkyTexture.loadFromFile("img/g.png");          //fantasma rojo 
	blinkySprite.setTexture(blinkyTexture);
	blinkySprite.setPosition(Vector2f(384, 416));
	blinkySprite.setTextureRect(sf::IntRect(0, 0, 28, 28));


	pinkyTexture.loadFromFile("img/g3.png");       //fantasma rosa
	pinkySprite.setTexture(pinkyTexture);		
	pinkySprite.setPosition(Vector2f(416, 416));
	pinkySprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	inkyTexture.loadFromFile("img/g1.png");        //fantasma naraja
	inkySprite.setTexture(inkyTexture);			
	inkySprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	inkySprite.setPosition(Vector2f(448, 416));

	clydeTexture.loadFromFile("img/g4.png");   //fantasma celeste
	clydeSprite.setTexture(clydeTexture);				
	clydeSprite.setPosition(Vector2f(480, 416));
	clydeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));


	//Derecha backgroudn score tipo de letra

	if (!font.loadFromFile("font/arial.ttf"))
		cout << "Error" << endl;

	if (!fon.loadFromFile("font/arial.ttf"))
		cout << "Error" << endl;

	if (!fo.loadFromFile("font/arial.ttf"))
		cout << "Error" << endl;


	text_score.setFont(fo);
	text_score.setPosition(1056, 128);
	text_score.setFillColor(Color::White);
	text_score.setStyle(Text::Bold);
	text_score.setCharacterSize(80);
	text_score.setString("Score : ");

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
	control.setString("Controles");

	control1.setFont(font);
	control1.setPosition(960, 480);
	control1.setFillColor(Color::Green);
	control1.setString("Teclas de Pacman");

	control2.setFont(font);
	control2.setPosition(960, 544);
	control2.setFillColor(Color::Green);
	control2.setString("P --> Pausa/Despausa");

	control3.setFont(font);
	control3.setPosition(960, 608);
	control3.setFillColor(Color::Green);
	control3.setString("M --> Silencia/Normal");

	control4.setFont(font);
	control4.setPosition(960, 672);
	control4.setFillColor(Color::Green);
	control4.setString("Esc --> Salir");


	//Vidas

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
void enterusernamefn() {
	RenderWindow username(VideoMode(1920, 1080), "Nombre");
	while (username.isOpen()) {
		Event event;
		while (username.pollEvent(event))
			score_board.Keyboard_Handling(event, username);
	}
}


struct Inky_Ghost {

	int ghostx(Sprite & oli, int Next_Moving) {
		return (oli.getPosition().y + Next_Moving) / 32;
	}

	int ghosty(Sprite & oli, int Next_Moving) {
		return (oli.getPosition().x + Next_Moving) / 32;
	}

	void Inky(Sprite & oli, int speed) {

		inky_cnt++;
		if (inky_cnt % 5 == 0)
			haha = haha || rand() % 3;
		int x = ghostx(oli, pac_diffPOS(oliy));
		int y = ghosty(oli, pac_diffPOS(olix));

		int currX = oli.getPosition().y, currY = oli.getPosition().x;

		if ((maze1[x][y] == 1 || cnt % 25 == 0) && ((currX % 32 == 0) && (currY % 32 == 0))) {


			if ((olix > 0 || olix < 0) && oliy == 0) { //derechas y izquierda
				if (haha) {
					if (maze1[ghostx(oli, -32)][ghosty(oli, 0)] != 1) //arriba
						olix = 0, oliy = -speed;

					else if (maze1[ghostx(oli, 32)][ghosty(oli, 0)] != 1) // abajo
						olix = 0, oliy = speed;

					else if (maze1[ghostx(oli, 0)][ghosty(oli, 32)] != 1) // derecha
						olix = speed, oliy = 0;

					else if (maze1[ghostx(oli, 0)][ghosty(oli, -32)] != 1) // izquierda
						olix = -speed, oliy = 0;

				} else {
					if (maze1[ghostx(oli, 32)][ghosty(oli, 0)] != 1) // abajo
						olix = 0, oliy = speed;

					else if (maze1[ghostx(oli, -32)][ghosty(oli, 0)] != 1) //arriba
						olix = 0, oliy = -speed;

					else if (maze1[ghostx(oli, 0)][ghosty(oli, -32)] != 1) //izquierda
						olix = -speed, oliy = 0;

					else if (maze1[ghostx(oli, 0)][ghosty(oli, 32)] != 1) //derecha
						olix = speed, oliy = 0;

				}
			} else if ((oliy > 0 || oliy < 0) && olix == 0) { //arriba y abajo
				if (haha) {
					if (maze1[ghostx(oli, 0)][ghosty(oli, 32)] != 1) //derecha
						olix = speed, oliy = 0;

					else if (maze1[ghostx(oli, 0)][ghosty(oli, -32)] != 1) //izquierda
						olix = -speed, oliy = 0;

					else if (maze1[ghostx(oli, -32)][ghosty(oli, 0)] != 1) //arriba
						olix = 0, oliy = -speed;

					else if (maze1[ghostx(oli, 32)][ghosty(oli, 0)] != 1) // abajo
						olix = 0, oliy = speed;
				} else {

					if (maze1[ghostx(oli, 0)][ghosty(oli, -32)] != 1) //izquierda
						olix = -speed, oliy = 0;

					else if (maze1[ghostx(oli, 0)][ghosty(oli, 32)] != 1) //derecha
						olix = speed, oliy = 0;

					else if (maze1[ghostx(oli, 32)][ghosty(oli, 0)] != 1) //abajo
						olix = 0, oliy = speed;

					else if (maze1[ghostx(oli, -32)][ghosty(oli, 0)] != 1) //arriba
						olix = 0, oliy = -speed;

				}

			}

		}
		haha = (haha) ? 0 : 1;
		inky_cnt += rand() % 10;
		inky_cnt %= (1000000000 + 7);
		oli.move(olix, oliy);
	}
};

void startfn() {

	RenderWindow startScreen(sf::VideoMode(1920, 1080), "Pacman", Style::Close | Style::Resize);
	Menu menu(startScreen.getSize().x, startScreen.getSize().y);
	while (startScreen.isOpen()) {

		Event event;

		while (startScreen.pollEvent(event)) {

			switch (event.type) { //Movimiento en el menu
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
					case 0:                        // Iniciar Juego
						startScreen.close();
						gamefn(2);
						break;

					case 1:
						startScreen.close();      // Score
						scoreBoardfn();
						break;

					case 2:
						startScreen.close();
						draw_your_maze();                // Dibuja el Mapa
						break;

					case 3:
						exit(0);                 // Salir
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

int pac_diffPOS(int Next_moving) {
	int Next_tile = 0;
	if (Next_moving > 0)  Next_tile = 32;
	else if (Next_moving < 0)  Next_tile = -32;
	else Next_tile = 0;

	return Next_tile;
}

//Patron observer

// Interfaz Observer
class Observer {
public:
    virtual void onNotify(int score) = 0;
    virtual ~Observer() {}
};

// Clase Subject
class Subject {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(int score) {
        for (Observer* observer : observers) {
            observer->onNotify(score);
        }
    }
};

// Clase Player
class Player {
private:
    int score;
    int lives;
public:
    Player() : score(0), lives(3) {}

    void addScore(int points) {
        score += points;
    }

    int getScore() const {
        return score;
    }

    void addLife() {
        lives++;
    }

    int getLives() const {
        return lives;
    }

    void decreaseLife() {
        lives--;
    }

    void resetLives() {
        lives = 3;
    }

    bool isDead() const {
        return lives <= 0;
    }
};


// Clase LifeObserver
class LifeObserver : public Observer {
private:
    Player* player;
    int scoreThreshold;
public:
    LifeObserver(Player* player, int scoreThreshold) : player(player), scoreThreshold(scoreThreshold) {}

    void onNotify(int score) override {
        if (score >= scoreThreshold) {
            player->addLife();
            scoreThreshold += 10000; // Ajustar al siguiente umbral de puntaje
        }
    }
};

// Clase Game
class Game : public Subject {
private:
    Player player;
public:
    Game() {}

    void addScore(int points) {
        player.addScore(points);
        notify(player.getScore());
    }

    Player& getPlayer() {
        return player;
    }
};


void gamefn(int pacman_speed) {
	static Game game;
	Player& player = game.getPlayer();
	LifeObserver lifeObserver(&player, 2000); // Vida extra cada 2000 puntos
	static bool observerAdded = false;
	if(!observerAdded){
		game.addObserver(&lifeObserver);
		observerAdded = true;
	}
	
	
	Return_game_to_the_start();
	RenderWindow pacman(VideoMode(1920, 1080), "Pacman");
	
	unique_ptr<ghostmoving> blinky = make_unique<ghostmoving>(maze1, cols, rows, 2);
	unique_ptr<ShortestRandom> pinky = make_unique<ShortestRandom>(maze1, cols, rows, 2);
	unique_ptr<Besh_Random> inky = make_unique<Besh_Random>();
	unique_ptr<Besh_Random> clyde = make_unique<Besh_Random>();
	unique_ptr<Inky_Ghost> ink = make_unique<Inky_Ghost>();
	
	int xx = 0, yy = 0;
	bool move_ch = 1; 
	int Besh_x = 0, Besh_y = 0;
	
	while (pacman.isOpen()) {
		score_board.Save_Score_Board(score);
		
		if (pacSprite.getGlobalBounds().intersects(blinkySprite.getGlobalBounds())) {
			if (!fright) {
				player.decreaseLife();
				lost_win.soundlost();
				Return_game_to_the_start();
			} else {
				blinkySprite.setPosition(Vector2f(384, 416));
				if (eatghost.getStatus() == Music::Status::Stopped)
					eatghost.play();
				game.addScore(200);
				sleep(seconds(1));
			}
		} 
		if (pacSprite.getGlobalBounds().intersects(pinkySprite.getGlobalBounds())) {
			if (!fright) {
				player.decreaseLife();
				lost_win.soundlost();
				Return_game_to_the_start();
			} else {
				pinkySprite.setPosition(Vector2f(416, 416));
				if (eatghost.getStatus() == Music::Status::Stopped)
					eatghost.play();
				game.addScore(200);
				sleep(seconds(1));
			}
		} 
		if (pacSprite.getGlobalBounds().intersects(inkySprite.getGlobalBounds())) {
			if (!fright) {
				player.decreaseLife();
				lost_win.soundlost();
				Return_game_to_the_start();
			} else {
				inkySprite.setPosition(Vector2f(448, 416));
				if (eatghost.getStatus() == Music::Status::Stopped)
					eatghost.play();
				game.addScore(200);
				sleep(seconds(1));
			}
		} 
		if (pacSprite.getGlobalBounds().intersects(clydeSprite.getGlobalBounds())) {
			if (!fright) {
				player.decreaseLife();
				lost_win.soundlost();
				Return_game_to_the_start();
			} else {
				clydeSprite.setPosition(Vector2f(480, 416));
				if (eatghost.getStatus() == Music::Status::Stopped)
					eatghost.play();
				game.addScore(200);
				sleep(seconds(1));
			}
		}
		
		if (player.isDead()) {
			RenderWindow lost(VideoMode(1920, 1080), "Oops !");
			lost_win.soundlost();
			lost_win.lost(lost);
			lost.display();
			pacman.close();
			sleep(seconds(3));
			lost.close();
			player.resetLives();
			map_path = "maps/map1.txt";
			main();
		}
		
		cnt = (cnt + 1) % 21;
		
		s = to_string(player.getScore());
		text.setString(s);
		
		Event event;
		while (pacman.pollEvent(event)) {
			if (event.type == Event::Closed) {
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
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				pacman.close();
				main();
			}
			
			if (move_ch) {
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
		
		if (!(xmod % 32) && !(ymod % 32)) {
			if (maze1[x][y] != 1) {
				pacSprite.move(xx, yy), Besh_x = xx, Besh_y = yy;
				detectdirection(xx, yy);
			} else if (maze1[Besh_getx][Besh_gety] != 1) {
				pacSprite.move(Besh_x, Besh_y);
				detectdirection(Besh_x, Besh_y);
			} else {
				pacSprite.move(0, 0);
				xx = yy = 0;
			}
		} else {
			pacSprite.move(Besh_x, Besh_y);
		}
		
		pacman.clear();
		
		if (fright != 0)
			fright--;
		frightmode(fright);
		
		blinkySprite = blinky->findpath(pacSprite, blinkySprite);
		pinky->short_with_tiles(pacSprite, pinkySprite);
		ink->Inky(inkySprite, 2);
		clyde->pinky_ran_move(clydeSprite, maze1, 2);
		
		win = true;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				int pacx = pacSprite.getPosition().x / 32, pacy = pacSprite.getPosition().y / 32;
				if (maze1[i][j] == 1) {
					wallSprite.setTextureRect(IntRect(0, 0, 32, 32));
					wallSprite.setPosition(j * 32, i * 32);
					pacman.draw(wallSprite);
				} else if (maze1[i][j] == 2) {
					win = false;
					dotSprite.setTextureRect(IntRect(0, 0, 16, 16));
					dotSprite.setColor(Color::Red);
					dotSprite.setPosition(j * 32 + 8, i * 32 + 8);
					pacman.draw(dotSprite);
					if (pacx == j && pacy == i) {
						maze1[i][j] = 0;
						game.addScore(10);
						if (eatdot.getStatus() == Music::Status::Stopped)
							eatdot.play();
					}
				} else if (maze1[i][j] == 3) {
					win = false;
					bigdotSprite.setTextureRect(IntRect(0, 0, 32, 32));
					bigdotSprite.setPosition(j * 32, i * 32);
					pacman.draw(bigdotSprite);
					if (pacx == j && pacy == i) {
						maze1[i][j] = 0, fright = 1000;
						game.addScore(50);  
						if (eatbigdot.getStatus() == Music::Status::Stopped)
							eatbigdot.play();
					}
				}
			}
		}
		
		if (win == true) {
			sleep(seconds(1));
			
			if (map_path[8] < '3') {
				map_path[8]++;
				declare();
				pacman.close();
				gamefn(2);
			} else {
				RenderWindow win(VideoMode(1920, 1080), "Felicitaciones !");
				lost_win.winningsound();
				lost_win.win(win);
				win.display();
				pacman.close();
				sleep(seconds(3));
				win.close();
				player.resetLives();
				declare();
			}
		}
		
		pacman.draw(blinkySprite);
		pacman.draw(pinkySprite);
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
		if (player.getLives() >= 1) pacman.draw(lives_pacman_sprite1);
		if (player.getLives() >= 2) pacman.draw(lives_pacman_sprite2);
		if (player.getLives() >= 3) pacman.draw(lives_pacman_sprite3);
		if (player.getLives() >= 4) pacman.draw(lives_pacman_sprite4);
		if (player.getLives() >= 5) pacman.draw(lives_pacman_sprite5);
		pacman.display();
		if (dead) {
			startsound.play();
			sleep(seconds(4));
			dead = false;
		}
	}
}

void scoreBoardfn() {
	RenderWindow Score_Screen(VideoMode(1920, 1080), "Score");
	scoreboard sb;
	
	while (Score_Screen.isOpen()) {
		Event event;
		while (Score_Screen.pollEvent(event)) {
			if (event.type == Event::Closed) {
				Score_Screen.close();
			} else if (event.text.unicode == 27) { // Esc para salir
				Score_Screen.close();
				startfn();
				break;
			}
		}
		
		Score_Screen.clear();
		
		sb.Print_Score_Board(Score_Screen);
		
		Score_Screen.display();
	}
}

void cargarMapa(int drawmaze[50][50]){
	fstream inputStream;
	inputStream.open("maps/drawurmaze.txt");
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			inputStream >> drawmaze[i][j];
}

void guardarMapa(int drawmaze[50][50]){
	ofstream outfile;
	outfile.open("filename.txt", ios::out);
	outfile.clear();
	for (int i=0; i<rows; i++){
		for (int j = 0; j < cols; j++)
			outfile << drawmaze[i][j]<<" ";
		outfile<<"\n";
	}
	outfile.close();
	cout<<"done";
}

void draw_your_maze() {
	Return_game_to_the_start();
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Dibuja tu mapa");

	int drawmaze[50][50] = {};
	thread cargarHilo(cargarMapa, drawmaze);
	cargarHilo.join();

	Texture textur;
	textur.loadFromFile("img/drawurmaze.png");
	Sprite sprite(textur);
	sprite.setPosition(896, 0);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::P)) {
				thread guardarHilo(guardarMapa, drawmaze);
				guardarHilo.join();
			} if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
				startfn();
			} if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
						maze1[i][j] = drawmaze[i][j];

				window.close();
				startfn();
			}
		}

		int b = Mouse::getPosition(window).x / 32, a = Mouse::getPosition(window).y / 32;
		if (drawmaze[a][b] != 4 && drawmaze[a][b] != 6 && a != 0 && b != 0 && a != 27 && b != 27) {
			if (Keyboard::isKeyPressed(Keyboard::D))
				drawmaze[a][b] = 2;
			else if (Keyboard::isKeyPressed(Keyboard::B))
				drawmaze[a][b] = 3;
			else if (Keyboard::isKeyPressed(Keyboard::W))
				drawmaze[a][b] = 1;
			else if (Keyboard::isKeyPressed(Keyboard::S))
				drawmaze[a][b] = 0;
		}
		
		window.clear();
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++) {
				if (drawmaze[i][j] == 1) {
					wallSprite.setTextureRect(IntRect(0, 0, 32, 32));
					wallSprite.setPosition(j * 32, i * 32);
					window.draw(wallSprite);
				} else if (drawmaze[i][j] == 2) {
					dotSprite.setTextureRect(IntRect(0, 0, 16, 16));
					dotSprite.setColor(Color::Red);
					dotSprite.setPosition(j * 32 + 8, i * 32 + 8);
					window.draw(dotSprite);
				} else if (drawmaze[i][j] == 3) {
					bigdotSprite.setTextureRect(IntRect(0, 0, 32, 32));
					bigdotSprite.setPosition(j * 32, i * 32);
					window.draw(bigdotSprite);
				}
			}

		window.draw(blinkySprite);
		window.draw(pinkySprite);
		window.draw(inkySprite);
		window.draw(clydeSprite);
		window.draw(pacSprite);
		window.draw(sprite);
		window.display();

	}
}

void playeranimation(int dir, int cnt) {
	pacSprite.setTextureRect(IntRect(cnt/3 * 32, dir * 32, 32, 32));
}

void detectdirection(int x, int y) {
	if (x == 2)
		Dir = 0;
	if (x == -2)
		Dir = 2;
	if (y == 2)
		Dir = 1;
	if (y == -2)
		Dir = 3;
}

void Return_game_to_the_start() {
	dead = true;
	pacSprite.setPosition(Vector2f(448, 704));

	blinkySprite.setPosition(Vector2f(384, 416));

	pinkySprite.setPosition(Vector2f(416, 416));

	inkySprite.setPosition(Vector2f(448, 416));

	clydeSprite.setPosition(Vector2f(480, 416));

	sleep(seconds(2));

}

class FrightModeDecorator{
public:
	FrightModeDecorator(){
		frightTexture.loadFromFile("img/fright.png");
		normalTextures[0].loadFromFile("img/g.png");
		normalTextures[1].loadFromFile("img/g3.png");
		normalTextures[2].loadFromFile("img/g1.png");
		normalTextures[3].loadFromFile("img/g4.png");
	}
	
	void setFrightMode(Sprite& sprite, bool frightMode, int ghostIndex){
		if (frightMode){
			sprite.setTexture(frightTexture);
		} else {
			sprite.setTexture(normalTextures[ghostIndex]);
		}
	}
private:
	Texture frightTexture;
	Texture normalTextures[4];
};

FrightModeDecorator frightModeDecorator;		
		
void frightmode(int x) {
	frightModeDecorator.setFrightMode(blinkySprite, x, 0);
	frightModeDecorator.setFrightMode(pinkySprite, x, 1);
	frightModeDecorator.setFrightMode(inkySprite, x, 2);
	frightModeDecorator.setFrightMode(clydeSprite, x, 3);
}
