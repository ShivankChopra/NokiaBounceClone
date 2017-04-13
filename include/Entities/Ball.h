#ifndef BALL_H
#define BALL_H

#include<Box2D/Box2D.h>
#include<SFML/Graphics.hpp>

#include<tmx/tmx2box2d.h>
#include<Entities/EntityTypes.h>
/* note :- setTexture() must be called before setBody() ,
           else the ball will not display*/

class Ball
{
    public:

                                  Ball();
                                  ~Ball();

        int                       getLives();
        int                       getScore();
        int                       getFlagsTaken();
        float                     getSpeed();
        float                     getJumpImpulse();
        sf::Vector2f              getSpawnPosition();

        void                      setBody(b2Body*);
        void                      setLives(int);
        void                      addScore(int);
        void                      incrFlagsTaken();
        void                      setSpeed(float);
        void                      setJumpImpulse(float);
        void                      setSpawnPosition(sf::Vector2f);

        void                      setTexture(const sf::Texture&);

        void                      jump();
        void                      moveLeft();
        void                      moveRight();
        void                      respawn();
        void                      draw(sf::RenderWindow& ,sf::View&);
        void                      setSingleJumpState();

        bool                      isRespawn;
        Entities::Type            m_entityType;
        sf::Sprite                m_lastRespawnSprite;


    private:
        void                      setBallSprite();

        //enum Type{ small , big };
        // implement later
        enum JumpState{ singleJump , noJump};

        b2Body*                   m_body;
        sf::Vector2f              m_spawnPosition;
        sf::Sprite                m_ballSprite;
        float                     m_speed;
        float                     m_jumpImpulse;
        int                       m_lives;
        int                       m_score;
        int                       m_flagsTaken;
        JumpState                 m_jumpState;
        //Type                      m_type;

};

#endif // BALL_H
