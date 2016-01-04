/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include <math.h>
#include <stack>

#include "WorldManager.h"
#include "ObjectManager.h"
#include "GameObjectFactory.h"
#include "LongRect.h"
#include "rapidxml/rapidxml.hpp"
#include "XMLSerializeNodeVisitor.h"

WorldManager::WorldManager(sf::Vector2f ChunkSize, unsigned long MaxRandomCoordinates, char iChunkDepth)
: m_ChunkSize(ChunkSize)
, m_MaxRandomCoordinates(MaxRandomCoordinates)
, m_iChunkDepth(iChunkDepth)
{
    for(unsigned long i = 0; i < m_MaxRandomCoordinates; i++)
    {
        float x = static_cast<float>(rand() % static_cast<int>(ChunkSize.x));
        float y = static_cast<float>(rand() % static_cast<int>(ChunkSize.y));
        m_RandomCoordinates.push_back(sf::Vector2f(x, y));
    }
}

sf::Vector2f WorldManager::GetRandomChunkPositionFromChunk(Quadrant *pChunk)
{
    if(pChunk == nullptr)
    {
        throw std::runtime_error(std::string("Null-reference-expeption in pChunk Object."));
    }
    if(m_IndexRandomCoordinates >= m_RandomCoordinates.size())
    {
        m_IndexRandomCoordinates = 0;
    }
    return (pChunk->GetTopLeftPosition() + m_RandomCoordinates[m_IndexRandomCoordinates++]);
}

void WorldManager::AddQuadrant(Quadrant *Quadrant)
{
    if(Quadrant == nullptr)
    {
        throw std::runtime_error(std::string("A null-reference exception happend by Adding a Quadrant (AddQuadrant)"));
    }
    
    // Ermitlle Index von neuem Quadranten und überprüfe, ob Index nicht bereits benutzt. Sollten alle Unique sein!
    std::pair<int,int> QuadrantIndex = Quadrant->GetIndex();
    if(m_Quadrants[QuadrantIndex] != nullptr)
    {
        throw std::runtime_error(std::string("Unique Index already used, maybe wrong Index set for Quadrant?"));
    }
    m_Quadrants[QuadrantIndex] = Quadrant;
    
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    sf::Vector2f TopLeftPosition = Quadrant->GetTopLeftPosition();
    
    const int MaxAsteroidRandItems = 2;
    
    GameObject* pBackground = GameObjectFactory::CreateBackgroundSprite(std::string("assets/space.png"), TopLeftPosition, m_ChunkSize);
    pBackground->SetTemporaryState(true);
    
    for(int i = 0; i < MaxAsteroidRandItems; i++)
    {
        GameObjectFactory::CreateAsteroid(GetRandomChunkPositionFromChunk(Quadrant), static_cast<float>(rand() % 360), static_cast<float>(rand() % 10));
    }
    
    for(int i = 0; i < (int)EWorldObjectType::MaxItem; i++)
    {
        std::pair<std::pair<int,int>, EWorldObjectType> world_info_idx(Quadrant->GetIndex(), (EWorldObjectType)i);
        auto it_world_info = m_WorldInfo[world_info_idx].begin();
        while(it_world_info != m_WorldInfo[world_info_idx].end())
        {
            switch ((EWorldObjectType)i) {
                case EWorldObjectType::Planet:
                    GameObjectFactory::CreatePlanet(it_world_info->GetPosition());
                    break;
                case EWorldObjectType::SpaceStation:
                    GameObjectFactory::CreateSpaceStation(it_world_info->GetPosition());
                    break;
                default:
                    break;
            }
            it_world_info++;
        }
    }
}

Quadrant* WorldManager::GetQuadrant(std::pair<int,int> QuadrantIndex)
{
    auto it = m_Quadrants.find(QuadrantIndex);
    if(it == m_Quadrants.end()) return nullptr;
    return it->second;
}

std::pair<int,int> WorldManager::GetQuadrantIndexAtPos(sf::Vector2f TopLeftPosition)
{
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    int dYIndex = static_cast<int>(floor(TopLeftPosition.y / ChunkSize.y));
    int dXIndex = static_cast<int>(floor(TopLeftPosition.x / ChunkSize.x));
    return std::pair<int,int>(dXIndex, dYIndex);
}

sf::Vector2f WorldManager::GetQuadrantCorrectedPos(sf::Vector2f Position)
{
    sf::Vector2f ChunkSize = WorldManager::GetInstance().m_ChunkSize;
    int dYIndex = static_cast<int>(floor(Position.y / ChunkSize.y));
    int dXIndex = static_cast<int>(floor(Position.x / ChunkSize.x));
    return sf::Vector2f(dXIndex * ChunkSize.x, dYIndex * ChunkSize.y);
}

void WorldManager::Draw(sf::RenderWindow *pWindow)
{
    // DEBUG Purpose: Zeige die Quadranten.
    
    auto it = m_Quadrants.begin();
    while(it != m_Quadrants.end())
    {
        if(it->second != nullptr)
        {
            if(it->second->GetFreezedState())
            {
                ++it;
                continue;
            }
            sf::RectangleShape shape;
            sf::Color color(255, 128, 0, 128);
            sf::Color color_visit(0, 0, 255, 128);
            sf::Color color_look_back(0, 255, 0, 128);
            shape.setSize(WorldManager::GetInstance().m_ChunkSize);
            shape.setPosition(it->second->GetTopLeftPosition());
            switch(it->second->m_bCurrentlyVisited)
            {
                case 0:
                    shape.setFillColor(color);
                    break;
                case 1:
                    shape.setFillColor(color_visit);
                    break;
                case 2:
                    shape.setFillColor(color_look_back);
                    break;
            }
            shape.setFillColor((it->second->m_bCurrentlyVisited ? color_visit : color));
            pWindow->draw(shape);
        }
        ++it;
    }
}

void WorldManager::RegisterEventObserver(IQuadrantObserver* pObserver)
{
    m_Observers.push_back(pObserver);
}

void WorldManager::UnregisterEventObserver(IQuadrantObserver* pObserver)
{
    for(unsigned int i = 0; i < m_Observers.size(); i++)
    {
        if(m_Observers[i] != pObserver) continue;
        m_Observers.erase(m_Observers.begin() + i);
        break;
    }
}

void WorldManager::Clear()
{
    auto it = m_Quadrants.begin();
    while(it != m_Quadrants.end())
    {
        delete(it->second);
        it++;
    }
    m_Quadrants.clear();
    m_Observers.clear();
    m_Observers.shrink_to_fit();
    
    auto it_world_info = m_WorldInfo.begin();
    while(it_world_info != m_WorldInfo.end())
    {
        it_world_info->second.clear();
        it_world_info->second.shrink_to_fit();
        it_world_info++;
    }
    m_WorldInfo.clear();
}

char WorldManager::GetChunkDepth()
{
    return m_iChunkDepth;
}

void WorldManager::GenerateWorld()
{
    if(m_WorldInfo.size() > 0)
    {
        m_WorldInfo.clear();
    }
    
    std::vector<LongRect> Spaces;
    Spaces.push_back(LongRect(std::numeric_limits<int>::min() + 1l, std::numeric_limits<int>::min() + 1l, std::numeric_limits<int>::max() * 2l - 1l, std::numeric_limits<int>::max() * 2l - 1l));
    std::map<EWorldObjectType, unsigned long> ObjectsSize;
    ObjectsSize[EWorldObjectType::Planet] = 10000000000ul;
    ObjectsSize[EWorldObjectType::SpaceStation] = 100000000ul;
    
    EWorldObjectType eTryingToCreate = EWorldObjectType::SpaceStation;
    int iRandX, iRandY;
    long iSize = ObjectsSize[eTryingToCreate];
    bool bFirstIteration = true;
    
    const std::vector<std::string> PlanetRes;
    const std::vector<std::string> SpaceStationRes;
    // const std::vector<std::string> BlackHoleRes;
    
    while(!Spaces.empty())
    {
        // Get next space and pop it from the stack.
        LongRect coord = Spaces.back();
        Spaces.pop_back();
        
        // Calculate a random position for current space.
        if(bFirstIteration)
        {
            iRandX = -250;
            iRandY = -250;
            bFirstIteration = false;
        }
        else
        {
            iRandX = static_cast<int>(coord.m_Left + static_cast<long>(rand()) % coord.m_Width);
            iRandY = static_cast<int>(coord.m_Top + static_cast<long>(rand()) % coord.m_Height);
        }
        
        // Insert Object into m_WorldInfo
        std::pair<int, int> quadrant_idx = GetQuadrantIndexAtPos(GetQuadrantCorrectedPos(sf::Vector2f(static_cast<float>(iRandX), static_cast<float>(iRandY))));
        std::pair<std::pair<int, int>, EWorldObjectType> worldinfo_idx(quadrant_idx, eTryingToCreate);
        m_WorldInfo[worldinfo_idx].push_back(WorldObjectInformation(eTryingToCreate, sf::Vector2f(static_cast<float>(iRandX), static_cast<float>(iRandY)), iSize));
        
        // Build Spaces for top & bottom & left & right
        LongRect LeftRectangle(coord.m_Left, coord.m_Top, (iRandX - coord.m_Left), coord.m_Height);
        LongRect RightRectangle((iRandX + iSize), coord.m_Top, (coord.m_Width - LeftRectangle.m_Width - iSize), coord.m_Height);
        LongRect TopRectangle(coord.m_Left, coord.m_Top, coord.m_Width, (iRandY - coord.m_Top));
        LongRect BottomRectangle(coord.m_Left, (iRandY + iSize), coord.m_Width, (coord.m_Height - TopRectangle.m_Height - iSize));
        
        // Decide wether left & right or top & bottom is bigger.
        long AreaFromLeftAndRight = (LeftRectangle.m_Width * LeftRectangle.m_Height + RightRectangle.m_Width * RightRectangle.m_Height);
        long AreaFromTopAndBottom = (TopRectangle.m_Width * TopRectangle.m_Height + BottomRectangle.m_Width * BottomRectangle.m_Height);
        if(AreaFromLeftAndRight > AreaFromTopAndBottom)
        {
            // left & right area is bigger.
            // so resize the area from top & bottom
            TopRectangle.m_Left += LeftRectangle.m_Width;
            TopRectangle.m_Width -= (LeftRectangle.m_Width + RightRectangle.m_Width);
            BottomRectangle.m_Left = TopRectangle.m_Left;
            BottomRectangle.m_Width = TopRectangle.m_Width;
        }
        else
        {
            // top & bottom area is bigger.
            // so resize the area from left & right
            LeftRectangle.m_Top += TopRectangle.m_Height;
            LeftRectangle.m_Height -= (TopRectangle.m_Height + BottomRectangle.m_Height);
            RightRectangle.m_Top = LeftRectangle.m_Top;
            RightRectangle.m_Height = LeftRectangle.m_Height;
        }
        
        // set size for next element
        eTryingToCreate = (EWorldObjectType)(rand() % (int)EWorldObjectType::MaxItem);
        iSize = ObjectsSize[eTryingToCreate];
        
        // push the 4 spaces to stack.
        // but only, if next size fits into area.
        if(TopRectangle.m_Width > 0 && TopRectangle.m_Height > 0 && TopRectangle.m_Width * TopRectangle.m_Height >= iSize * iSize)
        {
            Spaces.push_back(TopRectangle);
        }
        if(RightRectangle.m_Width > 0 && RightRectangle.m_Height > 0 && RightRectangle.m_Width * RightRectangle.m_Height >= iSize * iSize)
        {
            Spaces.push_back(RightRectangle);
        }
        if(BottomRectangle.m_Width > 0 && BottomRectangle.m_Height > 0 && BottomRectangle.m_Width * BottomRectangle.m_Height >= iSize * iSize)
        {
            Spaces.push_back(BottomRectangle);
        }
        if(LeftRectangle.m_Width > 0 && LeftRectangle.m_Height > 0 && LeftRectangle.m_Width * LeftRectangle.m_Height >= iSize * iSize)
        {
            Spaces.push_back(LeftRectangle);
        }
    }
    // std::cout << "[WorldManager]: Generated " << m_WorldInfo[EWorldObjectType::Planet].size() << " Planets and " << m_WorldInfo[EWorldObjectType::SpaceStation].size() << " SpaceStations." << std::endl;
}

void WorldManager::LoadGame(std::string strPath)
{
    
}

void WorldManager::SaveGame(std::string strPath)
{
    auto pXMLVisitor = new XMLSerializeNodeVisitor(strPath);
    auto game_objects = ObjectManager::GetInstance().GetActiveGameObjects();
    auto it_game_objects = game_objects.begin();
    while(it_game_objects != game_objects.end())
    {
        if((*it_game_objects) == nullptr || (*it_game_objects)->GetTemporaryState())
        {
            it_game_objects++;
            continue;
        }
        SerializeNode* pRootNode = (*it_game_objects)->Serialize();
        pRootNode->Accept(pXMLVisitor);
        delete pRootNode;
        it_game_objects++;
    }
    delete pXMLVisitor;
}