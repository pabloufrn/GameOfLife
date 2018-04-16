#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include "quadboard.h"
#include "button.h"
QuadBoard *board;
int rows;
int cols;
const int size = 20;
const int margin = 2;
void clear_board()
{
    (*board).clear();
}
void reset_board()
{
    (*board).reset();
}
bool readConfig(std::string file_name){
    std::ifstream file;
    file.open(file_name);
	char c_alive;
    char c;
	file >> rows >> cols >> c_alive;
    board = new QuadBoard(size, cols, rows, margin, sf::Color::Green);
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j){
            file >> c;
            if(c == c_alive)
                (*board).set_active(i, j);
        }
    (*board).backup();
    return true;
}
int main()
{
    // load config
    if(!readConfig("data/cfg1.dat"))return 1;
    // general variables
    size_t window_width = cols*size+cols*margin;
    size_t window_height = rows*size+rows*margin+80;
    // window elements
    sf::Text text; // iteration count
    sf::Font font;
    font.loadFromFile("font/arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(10, window_height-75);
    text.setString("Interation: 0");
    Button bt("Start", sf::Vector2f(10, window_height-40), 25, nullptr);
    Button bt2("Stop", sf::Vector2f(bt.getRightX() + 10, window_height-40), 25, nullptr);
    if(bt2.getRightX() > window_width + 2)
    {
        window_height += 35;
        bt2.move(-bt.getRightX(), 35);
    }
    Button bt3("Reset", sf::Vector2f(bt2.getRightX() + 10, window_height-40), 25, &reset_board);
    if(bt3.getRightX() > window_width + 2)
    {
        window_height += 35;
        bt3.move(-bt2.getRightX(), 35);
    }
    Button bt4("Clear", sf::Vector2f(bt3.getRightX() + 10, window_height-40), 25, &clear_board);
    if(bt4.getRightX() > window_width + 2)
    {
        window_height += 35;
        bt4.move(-bt3.getRightX(), 35);
    }
    //start_interation();
    // create a thread to update grid
    // window config
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "John Conway's Game of Life", sf::Style::Titlebar + sf::Style::Close);
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
            switch (e.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
		}
		(*board).update(e);
        bt.update(e);
        bt2.update(e);
        bt3.update(e);
        bt4.update(e);
		window.clear();
        window.draw(*board);
        window.draw(text);
        window.draw(bt);
        window.draw(bt2);
        window.draw(bt3);
        window.draw(bt4);
		window.display();
	}
	delete board;
	return 0;
}
