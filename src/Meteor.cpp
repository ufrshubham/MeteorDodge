#include "Meteor.hpp"

Meteor::Meteor()
{
}

Meteor::~Meteor()
{
}

void Meteor::Init(const sf::Texture &texture)
{
    m_body.setTexture(texture);
    int laneNumber = rand() % 3;

    m_body.setPosition(m_position.at(Lane::Right));

    if (laneNumber == 0)
    {
        m_body.setPosition(m_position.at(Lane::Left));
    }
    else if (laneNumber == 1)
    {
        m_body.setPosition(m_position.at(Lane::Middle));
    }
}

void Meteor::Move(sf::Time deltaTime)
{
    m_body.move(deltaTime.asSeconds() * m_speed);
}

sf::Vector2f Meteor::GetPoition() const
{
    return m_body.getPosition();
}

void Meteor::Reset()
{
    int laneNumber = rand() % 3;

    m_body.setPosition(m_position.at(Lane::Right));

    if (laneNumber == 0)
    {
        m_body.setPosition(m_position.at(Lane::Left));
    }
    else if (laneNumber == 1)
    {
        m_body.setPosition(m_position.at(Lane::Middle));
    }
}

sf::FloatRect Meteor::GetGlobalBounds() const
{
    return m_body.getGlobalBounds();
}

void Meteor::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_body);
}