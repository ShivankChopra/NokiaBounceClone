#include "GameLogic.h"

GameLogic::GameLogic(Ball& l_ball) : m_ball(l_ball)
{

}


std::vector<b2Body*>& GameLogic::getDestroyBodyList()
{
    return destroyBodyList;
}

// functions to determine colliding entity types
bool GameLogic::isBall(Entities::Type l_type)
{
    if(l_type == Entities::Type::Ball)
        return true;
    else
        return false;
}


bool GameLogic::isFire(Entities::Type l_type)
{
    if(l_type == Entities::Type::Fire)
        return true;
    else
        return false;
}

// functions to handle properties during collision
void GameLogic::handleFire()
{
    m_ball.setLives(m_ball.getLives() - 1);
    m_ball.respawn();
}


// handle collision
void GameLogic::BeginContact(b2Contact* contact)
{
    b2Body* b_A = contact->GetFixtureA()->GetBody();
    b2Body* b_B = contact->GetFixtureB()->GetBody();

    Entities::Type* t_A = static_cast<Entities::Type*>(b_A->GetUserData());
    Entities::Type* t_B = static_cast<Entities::Type*>(b_B->GetUserData());

    if(isFire(*t_A) || isFire(*t_B))
    {
        std::cout<<"handling fire";
        //handleFire();
    }
}


void GameLogic::EndContact(b2Contact* contact)
{

}
