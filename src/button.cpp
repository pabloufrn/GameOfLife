#include "button.h"
Button::Button(std::string textstr, const sf::Vector2f &position, size_t height, void (*on_press)(), sf::Color default_color)
{
    
    // text config
    this->font.loadFromFile("font/arial.ttf");
    this->text.setFont(this->font);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(height*0.8);
    this->text.setPosition(position.x+0.5*height, position.y-0.05*height);
    this->text.setString(textstr);
    // rectangle config
    sf::FloatRect frect = text.getGlobalBounds();
    this->size = sf::Vector2f(frect.width + height, height);
    this->rect.setSize(this->size);
    this->position = position;
    this->rect.setPosition(position);
    this->rect.setFillColor(default_color);
    // othe config
    this->state = BT_ENABLE;
    this->on_press = on_press;
}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();
    // draw button
    target.draw(this->rect, states);
    target.draw(this->text, states);
}
unsigned int Button::getRightX()
{
   return this->position.x+this->size.x;
}
void Button::press()
{
    // TODO::change button color
    this->on_press();   
}
void Button::update(sf::Event& e)
{
    if(this->state == BT_DISABLE)return;
    if(e.type == sf::Event::MouseMoved)
    {
        int offsetx = e.mouseMove.x - this->position.x;
        int offsety = e.mouseMove.y - this->position.y;
        if(offsetx < 0 || offsetx > this->size.x || offsety < 0 || offsety > this->size.y) // outside button area
        {
            if(this->state == BT_HOVER) // change color
            {
                this->state = BT_ENABLE;
                sf::Color color = this->rect.getFillColor();
                color.a = 255;
                this->rect.setFillColor(color);
            }
            return;
        }
        // inside button area
        if(this->state == BT_HOVER)return;
        // hover button
        this->state = BT_HOVER;
        sf::Color color = this->rect.getFillColor();
        color.a = 100;
        this->rect.setFillColor(color);
        return;
    }
    if(e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left)
    {
        int offset = e.mouseButton.x - this->position.x;
        if(offset < 0 || offset > this->size.x)return;
        offset = e.mouseButton.y - this->position.y;
        if(offset < 0 || offset > this->size.y)return;
        this->press();
    }
}
void Button::move(int rx, int ry)
{
     sf::Vector2f pos;
     pos = this->text.getPosition();
     pos.x += rx;
     pos.y += ry;
     this->text.setPosition(pos.x, pos.y);
     pos = this->rect.getPosition();
     pos.x += rx;
     pos.y += ry;
     this->rect.setPosition(pos.x, pos.y);
     this->position = pos;
}













