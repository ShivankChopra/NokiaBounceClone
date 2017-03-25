#ifndef STATICENTITY_H
#define STATICENTITY_H

#include<Box2D/Box2D.h>
#include<SFML/Graphics.hpp>

#include<tmx/tmx2box2d.h>
#include<Entities/EntityTypes.h>

class Entity
{
    public:
        Entities::Type           m_type;

                                 Entity(Entities::Type);
        void                     setBody(b2Body*);
        void                     setTexture(const sf::Texture&);
        void                     draw(sf::RenderWindow& window);

    protected:
        sf::Sprite               m_sprite;
        b2Body*                  m_body;


    private:
        void                     setEntitySprite();
};

#endif // STATICENTITY_H
