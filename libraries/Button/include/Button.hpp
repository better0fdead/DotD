
#ifndef BUTTON_HPP
#define BUTTON_HPP


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameContext.hpp"
#include <memory>
class Button{  
    public:
        sf::Vector2f position;
        sf::Vector2f text_position;
        sf::Vector2f icon_position;
        sf::RectangleShape rect;
        bool is_hovering;
        int width, height;
        sf::Font font;
        sf::Text m_text;
        sf::Text m_shadow;
        bool is_muted = false;
        bool is_answer = false;
        Button(){
            rect.setFillColor(sf::Color(0,167,189));
        }
        
        void setText(std::string s)
            {
                m_text.setString(s);
                m_shadow = m_text;
            };

        void create(float w, float h, float x, float y, std::string but_text){
            font.loadFromFile("../assets/fonts/ARCADECLASSIC.TTF");
            width = w;
            height = h;
            position = {x,y};
            text_position = {x + (w / 2), y};
            icon_position = {x + (w / 2), y + h / 2 - 5};
            m_text.setString(but_text);
            m_text.setFont(font);
            m_text.setCharacterSize(h);
            //m_text.setOrigin(x, y);
            m_text.setOrigin(m_text.getLocalBounds().width / 2,
                       m_text.getLocalBounds().height / 2);
            m_text.setPosition(text_position);
            //m_text.setColor(sf::Color(200,200,200));
            rect.setSize(sf::Vector2f(w,h));
            rect.setPosition(position);
        }
        

        void draw(std::shared_ptr<GameContext> context)
        {
            context->window->draw(rect);
            context->window->draw(m_text);
        }
        void collidepoint(sf::Vector2f mouse){
            if (mouse.x > position.x &&
            mouse.x < (position.x + width) &&
            mouse.y > position.y &&
            mouse.y < position.y + height){
                is_hovering = true;
            }
            else{
                is_hovering = false;
            }
           
            if (is_hovering)
                rect.setFillColor(sf::Color(50,50,50));
            else
                rect.setFillColor(sf::Color(0,167,189));
        }
        
        void set_text_size(int h)
        {
            m_text.setCharacterSize(h);
            //m_text.setOrigin(x, y);
            m_text.setOrigin(m_text.getLocalBounds().width / 2,
                       m_text.getLocalBounds().height / 2);
            m_text.setPosition(icon_position);
        }

        void clicked(){
            std::cout << "button pressed" << std::endl;
        }
};
#endif // BUTTON_HPP