#include "EntityFactory.h"

// private methods
void EntityFactory::loadWalls(const tmx::MapLayer& l_layer)
{
    for(const auto& o : l_layer.objects)
    {
        b2Body* b = tmx::BodyCreator::Add(o ,m_world);
        b->GetFixtureList()->SetFriction(0.5f);
        // if wall is a blue rubber wall
        std::string isRubberWall = o.GetPropertyString("isRubberWall");
        if(isRubberWall == "true")
            b->GetFixtureList()->SetRestitution(1.1);
        else
            b->GetFixtureList()->SetRestitution(0.3);
    }
}


void EntityFactory::loadStaticEntities(const tmx::MapLayer& l_layer , Entities::Type l_type , Texture::Id t_id)
{
    for(const auto& o : l_layer.objects)
    {
        b2Body* b = tmx::BodyCreator::Add(o, m_world, b2BodyType::b2_staticBody);
        b->GetFixtureList()->SetFriction(0.1f);

		Entity* se = new Entity(l_type);
		se->setTexture(m_textures.get(t_id));
		se->setBody(b);

		m_staticEntities.push_back(se);
    }
}


void EntityFactory::loadSpikes(const tmx::MapLayer& l_layer)
{
    for(const auto& o : l_layer.objects)
    {
        std::string isVertical = o.GetPropertyString("isVertical");
        std::string isHorizontal = o.GetPropertyString("isHorizontal");
        float x_vel = 0 , y_vel = 0;
        if(isVertical == "true")
            y_vel = 0.5;
        if(isHorizontal == "true")
            x_vel = 1.0;

        std::string flipTime = o.GetPropertyString("flipTime");
        float f = atof(flipTime.c_str());
        sf::Time f_time = sf::seconds(f);

        b2Body* b = tmx::BodyCreator::Add(o, m_world, b2BodyType::b2_kinematicBody);
        b->GetFixtureList()->SetFriction(0.1f);
        b->SetLinearVelocity(b2Vec2(x_vel , y_vel));

		Spike* se = new Spike(f_time);
		se->setTexture(m_textures.get(Texture::Id::Spike));
		se->setBody(b);

        m_spikes.push_back(se);
    }
}


void EntityFactory::loadBall(const tmx::MapLayer& l_layer)
{
    for(const auto& o : l_layer.objects)
    {
        b2Body* b = tmx::BodyCreator::Add(o, m_world, b2BodyType::b2_dynamicBody);
        b->GetFixtureList()->SetRestitution(0.40f);
        b->GetFixtureList()->SetDensity(2.0f);
        b->GetFixtureList()->SetFriction(0.1f);
        b->SetFixedRotation(true);

        m_ball.setTexture(m_textures.get(Texture::Id::Ball));
        m_ball.setBody(b);
    }
}


void EntityFactory::loadTextures()
{
    m_textures.load(Texture::Id::Ball ,"assets/textures/ball.png");
    m_textures.load(Texture::Id::Dimond ,"assets/textures/checkpoint.png");
    m_textures.load(Texture::Id::CheckPoint ,"assets/textures/checkpoint2.png");
    m_textures.load(Texture::Id::Fire ,"assets/textures/fire.png");
    m_textures.load(Texture::Id::Flag ,"assets/textures/flag.png");
    m_textures.load(Texture::Id::FlyBoost ,"assets/textures/flyBoost.png");
    m_textures.load(Texture::Id::JumpBoost ,"assets/textures/jumpBoost.png");
    m_textures.load(Texture::Id::GateOpen ,"assets/textures/levelComplete.png");
    m_textures.load(Texture::Id::GateClosed ,"assets/textures/level_closed.png");
    m_textures.load(Texture::Id::Crystal ,"assets/textures/lifecrystal.png");
    m_textures.load(Texture::Id::MakeBig ,"assets/textures/makeBig.png");
    m_textures.load(Texture::Id::MakeSmall ,"assets/textures/makeSmall.png");
    m_textures.load(Texture::Id::SpeedBoost ,"assets/textures/speedBoost.png");
    m_textures.load(Texture::Id::Spike ,"assets/textures/spike.png");
}


void EntityFactory::loadMaps()
{
    m_maps.addSearchPath("assets/textures");
    m_maps.addMap(m1, "test2.tmx");
    // add more maps in future
}


void EntityFactory::loadMapObjects(maps l_m)
{
    m_maps.load(l_m);

    const std::vector<tmx::MapLayer>& layers = m_maps.getLayers();

    for(const auto& l : layers)
    {
        if(l.name == "walls")
            loadWalls(l);
        if(l.name == "ball")
            loadBall(l);
        if(l.name == "spikes")
            loadSpikes(l);

        if(l.name == "fire")
            loadStaticEntities(l ,Entities::Type::Fire ,Texture::Id::Fire);
        if(l.name == "dimond")
            loadStaticEntities(l ,Entities::Type::Dimond ,Texture::Id::Dimond);
        if(l.name == "flag")
            loadStaticEntities(l ,Entities::Type::Flag ,Texture::Id::Flag);
        if(l.name == "flyBoost")
            loadStaticEntities(l ,Entities::Type::FlyBoost ,Texture::Id::FlyBoost);
        if(l.name == "jumpBoost")
            loadStaticEntities(l ,Entities::Type::JumpBoost ,Texture::Id::JumpBoost);
        if(l.name == "gate")
            loadStaticEntities(l ,Entities::Type::Gate ,Texture::Id::GateClosed);
        if(l.name == "crystal")
            loadStaticEntities(l ,Entities::Type::Crystal ,Texture::Id::Crystal);
        if(l.name == "makeBig")
            loadStaticEntities(l ,Entities::Type::MakeBig ,Texture::Id::MakeBig);
        if(l.name == "makeSmall")
            loadStaticEntities(l ,Entities::Type::MakeSmall ,Texture::Id::MakeSmall);
        if(l.name == "speedBoost")
            loadStaticEntities(l ,Entities::Type::SpeedBoost ,Texture::Id::SpeedBoost);
        if(l.name == "spike")
            loadStaticEntities(l ,Entities::Type::Spike ,Texture::Id::Spike);
    }
}


void EntityFactory::destroyEntities()
{
    // save ball data before destroying objects
    m_data.lives = m_ball.getLives();
    m_data.score = m_ball.getScore();

    // clear vectors containing pointer to objects
    for(auto& a : m_spikes)
    {
        delete a;
    }
    m_spikes.clear();

    for(auto& a : m_staticEntities)
    {
        delete a;
    }
    m_staticEntities.clear();

    // destroy world objects
    for(b2Body* b = m_world.GetBodyList() ; b ; b = b->GetNext())
    {
        m_world.DestroyBody(b);
    }
}


// public methods


EntityFactory::EntityFactory(b2World& l_world) : m_world(l_world) ,m_maps("assets/maps")
{
    loadMaps();
    loadTextures();

    loadMapObjects(m1);
}


EntityFactory::~EntityFactory()
{
    destroyEntities();
}


void EntityFactory::loadNextMap()
{
    // implement afterwards
}


std::vector<Entity*>& EntityFactory::getStaticEntities()
{
    return m_staticEntities;
}


std::vector<Spike*>& EntityFactory::getSpikes()
{
    return m_spikes;
}


Ball& EntityFactory::getBall()
{
    return m_ball;
}


Maps& EntityFactory::getMapObject()
{
    return m_maps;
}
