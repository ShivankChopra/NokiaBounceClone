#ifndef SPIKE_H
#define SPIKE_H

#include<Entities/Entity.h>

class Spike : public Entity
{
    public:
                                 Spike(sf::Time);
        void                     update();

    private:
        void                     flipDirection();

        sf::Time                 m_time;
        sf::Time                 m_flipTime;
        sf::Clock                m_clock;
};

#endif // SPIKE_H
