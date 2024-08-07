#include "Menu.h"

using namespace sf;
Menu::Menu(float width, float height) {


	if (!font.loadFromFile("font/prstartk.ttf")) { }
	//-----------------------------------------MENU--------------------------------------------------
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Yellow);
	menu[0].setString("Iniciar Juego");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Score");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));


	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Dibuja Tu Mapa");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	menu[3].setFont(font);
	menu[3].setFillColor(Color::White);
	menu[3].setString("Salir");
	menu[3].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));

	selectedItemIndex = 0;

}



void Menu::draw(RenderWindow &window) {
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(menu[i]);
	}
}

//----------------------------------(Controles para mover en el Menu)----------
void Menu::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::Yellow);
	}
}
void Menu::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(Color::Yellow);
	}
}
