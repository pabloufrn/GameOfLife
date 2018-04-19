#ifndef BUTTON_H
#define BUTTON_H
#include <cstring>
#include <SFML/Graphics.hpp>
enum BT_STATE
{
    BT_ENABLE,
    BT_HOVER,
    BT_DISABLE
};
class Button : public sf::Drawable, public sf::Transformable
{
public:
    Button(std::string textstr, const sf::Vector2f &position, size_t height, void (*on_press)(), sf::Color default_color = sf::Color(200, 200, 200));
    unsigned int getRightX();
    /// relative move
    void move(int rx, int ry);
    void update(sf::Event& e);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void press();
    void hover();
    sf::RectangleShape rect;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Font font;
    sf::Text text;
    /// on_press action function
    void (*on_press)();
    BT_STATE state;
};
#endif
