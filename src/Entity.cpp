#include "Entity.h"

Entity::Entity(Entities::Type l_type) : m_type(l_type) , updateUsingBody(true)
{

}


void Entity::setTexture(const sf::Texture& l_texture)
{
    m_sprite.setTexture(l_texture);
}


void Entity::setBody(b2Body* l_body)
{
    m_body = l_body;
    m_body->SetUserData(this);

    if(l_body != nullptr)
    {
        setEntitySprite();
    }
    else
        throw " m_body  is null for StaticEntity" ;
}


void Entity::setEntitySprite()
{
         b2PolygonShape* cs = static_cast<b2PolygonShape*>(m_body->GetFixtureList()->GetShape());
		 float side1 = tmx::BoxToSfFloat(cs->GetVertex(1).x - cs->GetVertex(0).x);
		 float side2 = tmx::BoxToSfFloat(cs->GetVertex(2).y - cs->GetVertex(1).y);

		 if(side1<0) side1*= -1;
		 if(side2<0) side2*= -1;

         float size_x = m_sprite.getGlobalBounds().width , size_y = m_sprite.getGlobalBounds().height;
         m_sprite.setScale(side1/size_x , side2/size_y);
         // for setting origin
         m_sprite.setOrigin(m_sprite.getLocalBounds().width/2 , m_sprite.getLocalBounds().height/2);
}


sf::Vector2f Entity::getPosition()
{
    return m_sprite.getPosition();
}


void Entity::draw(sf::RenderWindow& window)
{
    if(m_body != nullptr)
    {
        sf::Vector2f temp = tmx::BoxToSfVec(m_body->GetPosition());
        m_sprite.setPosition(temp);
    }

    if(updateUsingBody)
    {
        window.draw(m_sprite);
    }

}


void Entity::destroy(b2World& world)
{
    updateUsingBody = false;
    world.DestroyBody(m_body);
}
