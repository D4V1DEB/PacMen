#include "scoreboard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <iomanip> // setw
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>   // std::greater
#include <ostream>      // std::flush
using namespace std;
using namespace sf;


scoreboard::scoreboard() {
	scoreIn.open("Score/Score.txt");
	
	if (scoreIn.fail()) {
		cerr << "Error al abrir el archivo\n";
		exit(1);
	}
	while (!scoreIn.eof()) {
		pair<string, int > name_and_score;
		scoreIn >> name_and_score.first;
		if (scoreIn.fail() || name_and_score.first[0]=='0')
			scoreIn >> name_and_score.first;

		scoreIn>> name_and_score.second;
		if(scoreIn.fail())
			scoreIn >> name_and_score.second;
		Score[name_and_score.first] = name_and_score.second;

	}
	scoreIn.close();


	size = Score.size();
	it = Score.begin();
	for (; it != Score.end(); it++, i++) {
		Sorted_Score[i].first = it->second;
		Sorted_Score[i].second = it->first;
	}

	sort(Sorted_Score, Sorted_Score + size);
	Score.clear();
	for (int i=0 ; i<size ;  i++) {
		Score[Sorted_Score[i].second] = Sorted_Score[i].first;

	}
}


void scoreboard::Text_Style(Text& t, float Xposition, float Yposition, string s, Color c, int font_size) {
	if (!font1.loadFromFile("font/prstartk.ttf"))
		cout << "Error" << endl;

	t.setFont(font1);
	t.setCharacterSize(font_size);
	t.setFillColor(c);
	t.setStyle(Text::Bold);
	t.setString(s);
	t.setPosition(Xposition, Yposition);
}

void scoreboard::Keyboard_Handling(Event& event, RenderWindow& window) {
	if (event.type == Event::Closed)
		exit(0);

	if (event.type == Event::TextEntered) {
		if (event.text.unicode >= 32 && event.text.unicode <= 126)
			sentence += (char)event.text.unicode;

		 if ((event.text.unicode == 8  && sentence.length() > 0) || Keyboard::isKeyPressed(Keyboard::Space))
			sentence.erase(sentence.length() - 1, 1);

		 if (Keyboard::isKeyPressed(Keyboard::Enter) && sentence.length()>0 && sentence.length()<15) {
			Score[sentence]=max(Score[sentence],0);
			if(Event::KeyReleased)
			window.close();
		}
	}
		Text_Style(User_Name, 250,400, "Nombre:   ", Color::Yellow, 60);
		Text_Style(User_Input, 650, 400 , sentence, Color::White, 55);
		User_Input.setString(sentence);
		User_Name.setString("Nombre:   ");
		window.clear();
	window.draw(User_Name);
	window.draw(User_Input);
	window.display();
}


void scoreboard::Print_Score_Board(RenderWindow& window) {
	float x = 600.0, y = 0;

	Text_Style(Desplay_Score_Word, x, y, "Puntuacion", Color::White, 100);

	x = 470.0; y = 120.0;
	window.draw(Desplay_Score_Word);
	for (i = size - 1; i >= 0; i--, y += 90) {
		if (Sorted_Score[i].second == "")
			break;

		convert = to_string(Sorted_Score[i].first);

		Text_Style(Desplay_Name, x, y, Sorted_Score[i].second, Color::Yellow, 60);
		Text_Style(Desplay_Score, x + 400, y, convert, Color::Green, 45);

		window.draw(Desplay_Name);
		window.draw(Desplay_Score);
	}

}


void scoreboard :: Save_Score_Board(int finale_score) {
	scoreOut.open("Score/Score.txt");
	Score[sentence] = max(finale_score, Score[sentence]);

	scoreOut.clear();
	it = Score.begin();
	for (; it != Score.end(); it++)
	{
		scoreOut << it->first << " " << it->second << " ";
	}
	scoreOut.close();

}
