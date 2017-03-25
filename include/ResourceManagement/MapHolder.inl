
template<typename Identifier>
MapHolder<Identifier>::MapHolder(const std::string& pathDirectory):
    ml(pathDirectory)
{

}



template<typename Identifier>
void MapHolder<Identifier>::addSearchPath(const std::string& pathDirectory)
{
    ml.AddSearchPath(pathDirectory);
}



template<typename Identifier>
void MapHolder<Identifier>::addMap(Identifier id , const std::string& fileName)
{
    auto inserted = maps.insert(std::make_pair(id , fileName));
    assert(inserted.second);
}



template<typename Identifier>
void MapHolder<Identifier>::load(Identifier id)
{
    auto found = maps.find(id);
    assert(found != maps.end());

    ml.Load(found->second);
}



template<typename Identifier>
std::vector<tmx::MapLayer>& MapHolder<Identifier>::getLayers()
{
    return ml.GetLayers();
}



template<typename Identifier>
void MapHolder<Identifier>::draw(sf::RenderWindow& window)
{
    window.draw(ml);
}
