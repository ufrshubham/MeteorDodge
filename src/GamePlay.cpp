#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>

GamePlay::GamePlay(std::shared_ptr<Context> &context)
    : m_context(context),
      m_space(),
      m_meteors(),
      m_spaceShip(),
      m_scoreText(),
      m_score(0),
      m_spaceShipMove(MoveTo::Stay),
      m_elapsedTime(sf::Time::Zero),
      m_isPaused(false),
      m_flag1(false),
      m_flag2(false)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    m_context->m_assets->AddTexture(SPACE, "assets/textures/blue.png", true);
    m_context->m_assets->AddTexture(METEOR, "assets/textures/meteorGrey_big4.png");
    m_context->m_assets->AddTexture(SPACE_SHIP, "assets/textures/playerShip2_orange.png");

    m_space.setTexture(m_context->m_assets->GetTexture(SPACE));
    m_space.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    for (auto &meteor : m_meteors)
    {
        meteor.Init(m_context->m_assets->GetTexture(METEOR));
    }

    m_spaceShip.Init(m_context->m_assets->GetTexture(SPACE_SHIP));

    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("Score : " + std::to_string(m_score));
    m_scoreText.setCharacterSize(15);
}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        m_spaceShipMove = MoveTo::Stay;

        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Left:
                m_spaceShipMove = MoveTo::Left;
                break;
            case sf::Keyboard::Right:
                m_spaceShipMove = MoveTo::Right;
                break;
            case sf::Keyboard::Escape:
                m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
                break;
            default:
                break;
            }
        }
    }
}

void GamePlay::Update(sf::Time deltaTime)
{
    if (!m_isPaused)
    {
        m_elapsedTime += deltaTime;

        if (m_elapsedTime.asSeconds() > 0.1)
        {
            m_elapsedTime = sf::Time::Zero;

            m_spaceShip.Move(m_spaceShipMove);

            int maxIndex = 2;

            if(m_flag1)
            {
                maxIndex = 4;
            }

            if(m_flag2)
            {
                maxIndex = 6;
            }

            for (int i = 0; i < maxIndex; ++i)
            {
                if(m_spaceShip.IsOn(m_meteors[i]))
                {
                    m_context->m_states->Add(std::make_unique<GameOver>(m_context));
                }

                if (m_meteors[0].GetPoition().y > 640/2)
                {
                    m_flag1 = true;
                }
                else if((m_meteors[2].GetPoition().y > (640/2)))
                {
                    m_flag2 = true;
                }
                if(m_meteors[i].GetPoition().y > 640)
                {
                    m_meteors[i].Reset();
                    m_score += 10;
                    m_scoreText.setString(std::to_string(m_score));
                }
                m_meteors[i].Move(sf::seconds(1.f / 60.f));
            }
        }
    }
}

void GamePlay::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_space);
    m_context->m_window->draw(m_scoreText);
    m_context->m_window->draw(m_spaceShip);

    for (auto &meteor : m_meteors)
    {
        m_context->m_window->draw(meteor);
    }

    m_context->m_window->display();
}

void GamePlay::Pause()
{
    m_isPaused = true;
}

void GamePlay::Start()
{
    m_isPaused = false;
}
