#include "SpaceShip.hpp"
#include "Lanes.hpp"

SpaceShip::SpaceShip() : m_body(), m_lane(Lane::Middle)
{
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::Init(const sf::Texture &texture)
{
    m_body.setTexture(texture);
    m_body.setPosition(m_position.at(Lane::Middle));
}

void SpaceShip::Move(MoveTo move)
{
    if(move == MoveTo::Left)
    {
        if(m_lane == Lane::Right)
        {
            m_body.setPosition(m_position.at(Lane::Middle));
            m_lane = Lane::Middle;
        }
        else if(m_lane == Lane::Middle)
        {
            m_body.setPosition(m_position.at(Lane::Left));
            m_lane = Lane::Left;
        }
    }
    else if(move == MoveTo::Right)
    {
        if(m_lane == Lane::Left)
        {
            m_body.setPosition(m_position.at(Lane::Middle));
            m_lane = Lane::Middle;
        }
        else if(m_lane == Lane::Middle)
        {
            m_body.setPosition(m_position.at(Lane::Right));
            m_lane = Lane::Right;
        }
    }
}

bool SpaceShip::IsOn(const Meteor &meteor) const
{
    return meteor.GetGlobalBounds().intersects(m_body.getGlobalBounds());
}

void SpaceShip::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_body);
}