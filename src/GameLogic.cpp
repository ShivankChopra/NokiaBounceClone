#include "GameLogic.h"

GameLogic::GameLogic(std::vector<Entity*>& l_destroyList) : destroyEntityList(l_destroyList)
{

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
    l_ball->m_lastRespawnSprite.setPosition(l_dimond->getPosition());
    destroyEntityList.push_back(l_dimond);

}


void GameLogic::handleCrystal(Ball* l_ball , Entity* l_crystal , b2Body* l_b)
{
    l_ball->setLives(l_ball->getLives() + 1);
    destroyEntityList.push_back(l_crystal);

}


void GameLogic::handleFlag(Ball* l_ball , Entity* l_Flag , b2Body* l_b)
{
    l_ball->incrFlagsTaken();
    destroyEntityList.push_back(l_Flag);

}


// handle collision
void GameLogic::BeginContact(b2Contact* contact)
{
    /* in case of collision with wall , the body user data will be null */
    b2Body* b_A = contact->GetFixtureA()->GetBody();
    b2Body* b_B = contact->GetFixtureB()->GetBody();

    Entity* e_A = static_cast<Entity*>(b_A->GetUserData());
    Ball* l_ball = static_cast<Ball*>(b_B->GetUserData());// always a ball

    l_ball->setSingleJumpState();

    if(e_A != nullptr)
    {
        if(e_A->m_type == Entities::Type::Fire)
            handleDeath(l_ball);
        if(e_A->m_type == Entities::Type::Spike)
            handleDeath(l_ball);
        if(e_A->m_type == Entities::Type::Dimond)
            handleDimond(l_ball, e_A ,b_A);
        if(e_A->m_type == Entities::Type::Crystal)
            handleCrystal(l_ball, e_A ,b_A);
        if(e_A->m_type == Entities::Type::Flag)
            handleFlag(l_ball, e_A ,b_A);

    }
}


void GameLogic::EndContact(b2Contact* contact)
{

}
