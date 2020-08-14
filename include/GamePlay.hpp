#pragma once

#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game.hpp"
#include "State.hpp"
#include "SpaceShip.hpp"
#include "Lanes.hpp"
#include "Meteor.hpp"

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_space;
    std::array<Meteor, 6> m_meteors;
    SpaceShip m_spaceShip;

    sf::Text m_scoreText;
    int m_score;

    MoveTo m_spaceShipMove;
    sf::Time m_elapsedTime;

    bool m_isPaused;
    bool m_flag1;
    bool m_flag2;

public:
    GamePlay(std::shared_ptr<Context> &context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;
};