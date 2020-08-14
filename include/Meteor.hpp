#pragma once

#include <map>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "Lanes.hpp"

class Meteor : public sf::Drawable
{
    sf::Sprite m_body;

    const std::map<Lane, sf::Vector2f> m_position = {
        {Lane::Left, {16.5, -640}},
        {Lane::Middle, {(16.5 * 2 + 98), -640}},
        {Lane::Right, {(16.5 * 3 + 98 * 2), -640}},
    };

    const sf::Vector2f m_speed = sf::Vector2f(0, 1500.f);

public:
    Meteor();
    ~Meteor();

    void Init(const sf::Texture &texture);
    void Move(sf::Time deltaTime);
    sf::Vector2f GetPoition() const;
    void Reset();

    sf::FloatRect GetGlobalBounds() const; 

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};