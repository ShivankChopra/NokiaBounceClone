#include "Game.h"
#include<iostream>

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game():
    mPlayer(),
    mWindow(sf::VideoMode(720,480),"Bounce clone"),
    mtextureHolder()
{
    mtextureHolder.load(TextureIDs::Ball , "assets/textures/ball.png");
    mPlayer.setTexture(mtextureHolder.get(TextureIDs::Ball));
    mPlayer.setScale(0.25,0.25);
    mPlayer.setPosition(10,10);
}


void  Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen()){

        processEvents();
        timeSinceLastUpdate += clock.restart();

        while(timeSinceLastUpdate>TimePerFrame){
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }

        render();
    }// end outer while
}


void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event)){

        if(event.type == sf::Event::Closed)
               mWindow.close();
    }
}


void Game::update(sf::Time elapsedTime)
{
    // real time inputs
    sf::Vector2f movement(0.f,0.f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= 50.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += 50.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += 50.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= 50.0f;

    mPlayer.move(movement*elapsedTime.asSeconds());
    //std::cout<<mPlayer.getPosition().x<<"  "<<mPlayer.getPosition().y<<std::endl;
}


void Game::render()
{
     mWindow.clear();
     mWindow.draw(mPlayer);
     mWindow.display();
}
