#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include<ResourceManagement/ResourceHolder.hpp>
#include<ResourceManagement/MapHolder.hpp>

#include<Entities/Spike.h>
#include<Entities/Ball.h>

#include<string>
#include<stdlib.h>

enum maps
{
    m1
    // add more maps
};

struct ballData
{
    int lives = 0;
    int score = 0;
};

typedef MapHolder<maps> Maps;
typedef ResourceHolder<sf::Texture , Texture::Id> t_holder;

class EntityFactory
{
    public:
                                 EntityFactory(b2World&);
                                ~EntityFactory();

        void                     loadNextMap();
        std::vector<Entity*>&    getStaticEntities();
        std::vector<Spike*>&     getSpikes();
        Ball&                    getBall();
        Maps&                    getMapObject();

    // private methods
    private:

        void                     loadWalls(const tmx::MapLayer&);
        void                     loadStaticEntities(const tmx::MapLayer& ,Entities::Type ,Texture::Id);
        void                     loadSpikes(const tmx::MapLayer&);
        void                     loadBall(const tmx::MapLayer&);
        void                     loadTextures();
        void                     loadMaps();
        void                     loadMapObjects(maps);
        void                     destroyEntities();

    private:

        b2World&                 m_world;
        std::vector<Entity*>     m_staticEntities;
        std::vector<Spike*>      m_spikes;
        Ball                     m_ball;

        ballData                 m_data;

        Maps                     m_maps;
        t_holder                 m_textures;
};

#endif // ENTITYFACTORY_H
