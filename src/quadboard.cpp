#include "quadboard.h"

QuadBoard::QuadBoard(size_t quad_size, size_t width, size_t height, size_t margin, sf::Color default_color, sf::Color active_color)
{
    // set proprieters
    this->quad_size = quad_size;
    this->width = width;
    this->height = height;
    this->margin = margin;
    this->is_enable = true;
    this->default_color = default_color;
    this->active_color = active_color;
    // resize the vertex array to fit the board size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4); // 4 vertices * width cols * height rows
    m_o_vertices.setPrimitiveType(sf::Quads);
    m_o_vertices.resize(width * height * 4);
    // populate the vertex array
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get a pointer to the current board's quad
            int index = (i * width + j) * 4;
            sf::Vertex* quad = &m_vertices[index];
            sf::Vertex* quad2 = &m_o_vertices[index];
            // define its 4 corners
            quad[0].position = sf::Vector2f(j * quad_size + j * margin, i * quad_size + i * margin);
            quad[1].position = sf::Vector2f((j + 1) * quad_size + j * margin, i * quad_size + i * margin);
            quad[2].position = sf::Vector2f((j + 1) * quad_size + j * margin, (i + 1) * quad_size + i * margin);
            quad[3].position = sf::Vector2f(j * quad_size + j * margin, (i + 1) * quad_size + i * margin);
            quad2[0].position = sf::Vector2f(j * quad_size + j * margin, i * quad_size + i * margin);
            quad2[1].position = sf::Vector2f((j + 1) * quad_size + j * margin, i * quad_size + i * margin);
            quad2[2].position = sf::Vector2f((j + 1) * quad_size + j * margin, (i + 1) * quad_size + i * margin);
            quad2[3].position = sf::Vector2f(j * quad_size + j * margin, (i + 1) * quad_size + i * margin);
            // define vertice colors
            quad[0].color = default_color;
            quad[1].color = default_color;
            quad[2].color = default_color;
            quad[3].color = default_color;
            quad2[0].color = default_color;
            quad2[1].color = default_color;
            quad2[2].color = default_color;
            quad2[3].color = default_color;
            
        }
}
void QuadBoard::set_quad_color(unsigned int x, unsigned int y, sf::Color color)
{
    // get a pointer to the quad
    sf::Vertex* quad = &this->m_vertices[(x * width + y) * 4];
    // define vertice colors
    quad[0].color = color;
    quad[1].color = color;
    quad[2].color = color;
    quad[3].color = color;
}
void QuadBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();
    // draw the vertex array
    target.draw(m_vertices, states);
}
void QuadBoard::update(sf::Event& e)
{
    if(!this->is_enable)return;
    if (e.type != sf::Event::MouseButtonPressed)return;
    if (e.mouseButton.button == sf::Mouse::Left){
        unsigned int posx = e.mouseButton.x;
        if(posx >= (this->width*this->quad_size + this->width*this->margin)) // for our case this will be ever false, because the board extends through entire window.
            return;
        unsigned int posy = e.mouseButton.y;
        if(posy >= (this->height*this->quad_size + this->height*this->margin))return; // for our case this will be ever false, because the board extends through entire window.
        //if((posx+margin) % (this->quad_size + margin) < this->margin)return;    // !
        //if((posy+margin) % (this->quad_size + margin) < this->margin)return;    // | check if the mouse is located on margin
        int j = posx / (this->quad_size+this->margin); // !
        int i = posy / (this->quad_size+this->margin); // | get the quad index. The column depends of x_axis of mouse
        this->set_quad_color(i, j, this->active_color); // | change quad color
    } else if (e.mouseButton.button == sf::Mouse::Right){
        unsigned int posx = e.mouseButton.x;
        if(posx >= (this->width*this->quad_size + this->width*this->margin)) // for our case this will be ever false, because the board extends through entire window.
            return;
        unsigned int posy = e.mouseButton.y;
        if(posy >= (this->height*this->quad_size + this->height*this->margin))return; // for our case this will be ever false, because the board extends through entire window.
        //if((posx+margin) % (this->quad_size + margin) < this->margin)return;    // !
        //if((posy+margin) % (this->quad_size + margin) < this->margin)return;    // | check if the mouse is located on margin
        int j = posx / (this->quad_size+this->margin); // !
        int i = posy / (this->quad_size+this->margin); // | get the quad index. The column depends of x_axis of mouse
        this->set_quad_color(i, j, this->default_color); // | change quad color
    }
}
void QuadBoard::clear()
{
    if(!this->is_enable)return;
    for (unsigned int i = 0; i < this->width; ++i)
        for (unsigned int j = 0; j < this->height; ++j)
        {
            sf::Vertex* quad = &m_vertices[(i * this->width + j) * 4];
            quad[0].color = this->default_color;
            quad[1].color = this->default_color;
            quad[2].color = this->default_color;
            quad[3].color = this->default_color;
        }
}
void QuadBoard::reset()
{
    if(!this->is_enable)return;
    for (unsigned int i = 0; i < this->width; ++i)
        for (unsigned int j = 0; j < this->height; ++j)
        {
            int index = (i * this->width + j) * 4;
            sf::Vertex* quad = &m_vertices[index];
            sf::Vertex* quad2 = &m_o_vertices[index];
            sf::Color color = quad2[0].color;
            quad[0].color = color;
            quad[1].color = color;
            quad[2].color = color;
            quad[3].color = color;
        }
}
void QuadBoard::backup()
{
    for (unsigned int i = 0; i < this->width; ++i)
        for (unsigned int j = 0; j < this->height; ++j)
        {
            // get a pointer to the current board's quad
            int index = (i * width + j) * 4;
            sf::Vertex quad = m_vertices[index];
            sf::Vertex* quad2 = &m_o_vertices[index];
            
            // define vertice colors
            *quad2 = quad;
        }
}
void QuadBoard::set_active(int x, int y)
{
    // get a pointer to the quad
    sf::Vertex* quad = &this->m_vertices[(x * width + y) * 4];
    // define vertice colors
    quad[0].color = this->active_color;
    quad[1].color = this->active_color;
    quad[2].color = this->active_color;
    quad[3].color = this->active_color;
}
void QuadBoard::set_default(int x, int y)
{
    // get a pointer to the quad
    sf::Vertex* quad = &this->m_vertices[(x * width + y) * 4];
    // define vertice colors
    quad[0].color = this->default_color;
    quad[1].color = this->default_color;
    quad[2].color = this->default_color;
    quad[3].color = this->default_color;
}
bool QuadBoard::get_active(int x, int y)
{
    // get a pointer to the quad
    sf::Vertex* quad = &this->m_vertices[(x * width + y) * 4];
    // check color
    if(quad[0].color == this->default_color)return false;
    return true;
}






