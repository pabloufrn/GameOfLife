#ifndef QUADBOARD_H
#define QUADBOARD_H
#include <SFML/Graphics.hpp>
class QuadBoard : public sf::Drawable, public sf::Transformable
{
public:
    QuadBoard(size_t quad_size, size_t width, size_t height, size_t margin, sf::Color default_color = sf::Color::Green, sf::Color active_color = sf::Color::Yellow);
    void set_quad_color(unsigned int x, unsigned int y, sf::Color color);
    void set_active(int x, int y);
    void set_default(int x, int y);
    void update(sf::Event& e);
    void clear();
    void reset();
    void backup();
    bool get_active(int x, int y);
    size_t get_quad_size(){return this->quad_size;}
    size_t get_margin(){return this->margin;}
    void disable(){this->is_enable = false;}
    void enable(){this->is_enable = true;}
    bool is_disable(){return not this->is_enable;}
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    size_t quad_size;
    size_t margin;
    size_t width;
    size_t height;
    bool is_enable;
    sf::Color active_color;
    sf::Color default_color;
    sf::VertexArray m_vertices;
    sf::VertexArray m_o_vertices; // original vertex Array
};
#endif
