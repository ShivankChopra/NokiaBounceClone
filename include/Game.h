#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include<ResourceManagement/ResourceHolder.hpp>

enum TextureIDs{ Ball , None};

class Game
{
     public:

                                 Game();
         void                    run();

     private:

         void                    processEvents();
         void                    update(sf::Time elapsedTime);
         void                    render();

         sf::Sprite              mPlayer;
         sf::RenderWindow        mWindow;
         static const sf::Time   TimePerFrame;
         ResourceHolder<sf::Texture , TextureIDs>          mtextureHolder;

};

#endif // GAME_H
