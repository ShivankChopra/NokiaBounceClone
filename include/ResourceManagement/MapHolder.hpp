#ifndef MAPHOLDER_H
#define MAPHOLDER_H

#include<map>
#include<string>
#include<vector>
#include<cassert>

#include<tmx/MapLoader.h>
#include<tmx/tmx2box2d.h>

#include<SFML/Graphics.hpp>

// can store tmx maps and parse its objects
template<typename Identifier>
class MapHolder
{
public :
                        MapHolder(const std::string& pathDirectory);
    void                addSearchPath(const std::string& pathDirectory);
    void                addMap(Identifier id , const std::string& fileName);
    void                load(Identifier id);
    void                draw(sf::RenderWindow& window);

    std::vector<tmx::MapLayer>&   getLayers();

private :
    std::map<Identifier , std::string>  maps;
    tmx::MapLoader                 ml;
};

#include "MapHolder.inl"

#endif // MAPHOLDER_H
