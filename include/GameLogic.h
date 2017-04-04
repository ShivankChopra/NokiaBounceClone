#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include<Box2d/Box2d.h>

#include<Entities/Spike.h>
#include<Entities/Ball.h>

class GameLogic : public b2ContactListener
{
    public:
                                      GameLogic(std::vector<Entity*>&);

        void                          BeginContact(b2Contact*);
        void                          EndContact(b2Contact*);

    private:
        // to handle collision effects of various entities
        void                          handleDeath(Ball*);
        void                          handleDimond(Ball* ,Entity* ,b2Body*);
        void                          handleCrystal(Ball* ,Entity* ,b2Body*);
        void                          handleFlag(Ball* ,Entity* ,b2Body*);

        std::vector<Entity*>&         destroyEntityList;
};

#endif // GAMELOGIC_H
