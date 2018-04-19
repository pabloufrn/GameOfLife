#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include "life.h"
#include "button.h"
Life *game;
int gen = 0;
sf::Text text; // iteration count text
void clear_board()
{
    game->board->clear();
}
void reset_board()
{
    game->board->reset();
}
void update()
{
    game->update();
}
void start()
{
    std::function<void(void)> func = update;
    unsigned int interval = 1000;
    if(game->board->is_disable())
        return;
    game->board->disable();
    game->load_from_board();
    std::thread([func, interval]() {
        while (game->board->is_disable())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            func();
            if(game->is_extinct()){
                text.setString("Extinct at gen " + std::to_string(gen));
                break;
            }
            if(game->is_stable()){
                text.setString("Stable at gen " + std::to_string(gen));
                break;
            }
            if(!game->board->is_disable()) // extra verification, cause the stop button may be pressed
                break;
            gen++;
            text.setString("Generation: " + std::to_string(gen));
        }
    }).detach();
    return;
}
void stop()
{
    if(!game->board->is_disable())
        return;
    game->clear_ids();
    game->board->enable();
    game->board->reset();
    text.setString("Generation: 0");
    gen = 0;
    return;
}

int main(int argc, char* argv[])
{
    if(argc < 2){
		std::cout << "Wrong syntaxe!\n"
			<< "Use: life <input_cfg_file> [<output_cfg_evolution_file>]" << std::endl;
		return 0;
    }
    if(argv[1][0] == '-' and argv[1][1] == 's')
    {
        std::string::size_type sz;
        int cols = std::stoi(argv[2], &sz);
        int rows = std::stoi(argv[3], &sz);
        game = new Life(rows, cols);
    }
    else {
            game = new Life(argv[1]);
    }
    // load config
    
    int rows = game->get_rows();
    int cols = game->get_columns();
    size_t margin = game->board->get_margin();
    size_t size = game->board->get_quad_size();
    // general variables
    size_t window_width = cols*size+cols*margin;
    size_t window_height = rows*size+rows*margin+80;
    // window elements
    sf::Font font;
    font.loadFromFile("font/arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(10, window_height-75);
    text.setString("Generation: 0");
    Button bt("Start", sf::Vector2f(10, window_height-40), 25, &start);
    Button bt2("Stop", sf::Vector2f(bt.getRightX() + 10, window_height-40), 25, &stop);
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
		(*game->board).update(e);
        bt.update(e);
        bt2.update(e);
        bt3.update(e);
        bt4.update(e);
		window.clear();
        window.draw(*game->board);
        window.draw(text);
        window.draw(bt);
        window.draw(bt2);
        window.draw(bt3);
        window.draw(bt4);
		window.display();
	}
	return 0;
}
