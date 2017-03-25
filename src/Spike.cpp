#include "Spike.h"

Spike::Spike(sf::Time l_flipTime) : Entity(Entities::Type::Spike) ,
                                    m_time(sf::Time::Zero) ,
                                    m_flipTime(l_flipTime)

{
    //ctor
}


void Spike::flipDirection()
{
    b2Vec2 speed = m_body->GetLinearVelocity();
    speed.y *= -1;
    speed.x *= -1;
    m_body->SetLinearVelocity(speed);
}


void Spike::update()
{
    m_time += m_clock.restart();
    if(m_time > m_flipTime)
    {
        m_time -= m_flipTime;
        flipDirection();
    }
}
