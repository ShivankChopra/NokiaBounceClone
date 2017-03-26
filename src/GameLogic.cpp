#include "GameLogic.h"

GameLogic::GameLogic()
{

}


std::vector<b2Body*>& GameLogic::getDestroyBodyList()
{
    return destroyBodyList;
}

// functions to handle properties during collision
void GameLogic::handleDeath(Ball* l_ball)
{
    //l_ball->setLives(l_ball->getLives() - 1);
    l_ball->isRespawn = true;
}


void GameLogic::handleDimond(Ball* l_ball , Entity* l_dimond , b2Body* l_b)
{
    l_ball->setSpawnPosition(l_dimond->getPosition());
    //destroyBodyList.push_back(l_b);

}


// handle collision
void GameLogic::BeginContact(b2Contact* contact)
{
    /* in case of collision with wall , the body user data will be null */
    b2Body* b_A = contact->GetFixtureA()->GetBody();
    b2Body* b_B = contact->GetFixtureB()->GetBody();

    Entity* e_A = static_cast<Entity*>(b_A->GetUserData());
    Ball* l_ball = static_cast<Ball*>(b_B->GetUserData());// always a ball

    if(e_A != nullptr)
    {
        if(e_A->m_type == Entities::Type::Fire)
            handleDeath(l_ball);
        if(e_A->m_type == Entities::Type::Spike)
            handleDeath(l_ball);
        if(e_A->m_type == Entities::Type::Dimond)
            handleDimond(l_ball, e_A ,b_A);
    }
}


void GameLogic::EndContact(b2Contact* contact)
{

}
