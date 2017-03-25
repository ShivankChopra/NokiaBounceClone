#include<ResourceManagement/ResourceHolder.hpp>
#include<ResourceManagement/MapHolder.hpp>

#include<SFML/Audio.hpp>

#include<EntityFactory.h>
#include<GameLogic.h>

enum sounds
{
    s1
};

typedef ResourceHolder<sf::SoundBuffer , sounds> SoundHolder;

int main()
{
    sf::Vector2f screenSize(800,500);
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y) ,"Resource testing");
    window.setKeyRepeatEnabled(false);

    b2World world(tmx::SfToBoxVec(sf::Vector2f(0,2500)));

    EntityFactory ef(world);

    std::vector<Entity*>& s_e = ef.getStaticEntities();
    std::vector<Spike*>& spikes = ef.getSpikes();
    Ball& ball = ef.getBall();

    Maps& m = ef.getMapObject();
    // game logic
    GameLogic gl(ball);
    //world.SetContactListener(&gl);

    // load sounds
    SoundHolder s;
    s.load(s1, "assets/sounds/button_click.wav");
    sf::Sound sn(s.get(s1));
    sn.setVolume(50);

    // music
    sf::Music music;
    music.openFromFile("assets/music/track1.wav");
    music.setVolume(20);
    music.setLoop(true);
    music.play();

    // view handling
    sf::View view;
	view.setSize(600,375);

    // game loop
    sf::Clock clock;
    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Up)
                {
                    sn.play();
                }
                if(event.key.code == sf::Keyboard::Up)
                {
                    ball.jump();
                }
            }
        }

        //update
		world.Step(clock.restart().asSeconds(), 6, 3);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
                ball.moveRight();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
                ball.moveLeft();
        }

		for (auto& o : spikes)
		{
            o->update();
		}
        // Render objects
		window.clear();

        m.draw(window);

        ball.draw(window,view);

        for (auto& o : s_e)
        {
            o->draw(window);
        }

        for (auto& es : spikes)
        {
            es->draw(window);
        }

        window.display();
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
