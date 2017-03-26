#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include<Box2d/Box2d.h>

#include<Entities/Spike.h>
#include<Entities/Ball.h>

class GameLogic : public b2ContactListener
{
    public:
                                      GameLogic();

        void                          BeginContact(b2Contact*);
        void                          EndContact(b2Contact*);

        std::vector<b2Body*>&         getDestroyBodyList();

    private:
        // to handle collision effects of various entities
        void                          handleDeath(Ball*);
        void                          handleDimond(Ball* ,Entity* ,b2Body*);

        std::vector<b2Body*>          destroyBodyList;
};

#endif // GAMELOGIC_H
