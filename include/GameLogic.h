#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include<Box2d/Box2d.h>

#include<Entities/Spike.h>
#include<Entities/Ball.h>

class GameLogic : public b2ContactListener
{
    public:
                                      GameLogic(Ball&);

        void                          BeginContact(b2Contact*);
        void                          EndContact(b2Contact*);

        std::vector<b2Body*>&         getDestroyBodyList();

    private:
        bool                          isBall(Entities::Type);
        bool                          isFire(Entities::Type);
        // to handle collision effects of various entities
        void                          handleFire();

        Ball&                         m_ball;
        std::vector<b2Body*>          destroyBodyList;
};

#endif // GAMELOGIC_H
