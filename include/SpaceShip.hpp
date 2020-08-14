#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <map>

#include "Lanes.hpp"
#include "Meteor.hpp"

class SpaceShip : public sf::Drawable
{
private:
    const std::map<Lane, sf::Vector2f> m_position = {
        { Lane::Left, {6, 490}},
        { Lane::Middle, {(6*2 + 112), 490}},
        { Lane::Right, {(6*3 + 112*2), 490}},
    };

    sf::Sprite m_body;
    Lane m_lane;

public:
    SpaceShip();
    ~SpaceShip();

    void Init(const sf::Texture &texture);
    void Move(MoveTo move);
    bool IsOn(const Meteor &meteor) const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};