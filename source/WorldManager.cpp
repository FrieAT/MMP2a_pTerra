/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include <math.h>
#include <stack>
#include <fstream>
#include <sstream>
#include <cfloat>

#include "WorldManager.h"
#include "ObjectManager.h"
#include "GameObjectFactory.h"
#include "LongRect.h"
#include "XMLWriteVisitor.h"
#include "XMLReadVisitor.h"
#include "rapidxml/rapidxml.hpp"
#include "ClassRegistry.h"

WorldManager::WorldManager(sf::Vector2f ChunkSize, unsigned long MaxRandomCoordinates, char iChunkDepth)
: m_ChunkSize(ChunkSize)
, m_MaxRandomCoordinates(MaxRandomCoordinates)
, m_iChunkDepth(iChunkDepth)
{
    m_iSeed = static_cast<int>(time(NULL));
    srand(m_iSeed);
    
    for(unsigned long i = 0; i < m_MaxRandomCoordinates; i++)
    {
        float x = static_cast<float>(rand() % static_cast<int>(m_ChunkSize.x));
        float y = static_cast<float>(rand() % static_cast<int>(m_ChunkSize.y));
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

void WorldManager::AddQuadrant(Quadrant *Quadrant, bool bIgnoreGenerationBehavior)
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
    
    // This Background for example may be allowed to create everytime, if its needed. Cuz it isn´t saved up in a savegame
    // See setting the TemporaryState to true.
    GameObject* pBackground = GameObjectFactory::CreateBackgroundSprite(std::string("assets/lilee/BG.png"), TopLeftPosition, m_ChunkSize);
    pBackground->SetTemporaryState(true);
    
    // Only generate dynamic things, if it is allowed to (not allowed, if loading from a savegame)
    if(!bIgnoreGenerationBehavior)
    {
        const int MaxAsteroidRandItems = 1;
        
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
                    default: // yes and ignore Terra too, Terra should be only on need created.
                        break;
                }
                it_world_info++;
            }
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
    /*
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
     */
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
    
    if(m_RandomCoordinates.size() > 0)
    {
        m_RandomCoordinates.clear();
    }
    
    for(unsigned long i = 0; i < m_MaxRandomCoordinates; i++)
    {
        float x = static_cast<float>(rand() % static_cast<int>(m_ChunkSize.x));
        float y = static_cast<float>(rand() % static_cast<int>(m_ChunkSize.y));
        m_RandomCoordinates.push_back(sf::Vector2f(x, y));
    }
    
    std::vector<LongRect> Spaces;
    // Spaces.push_back(LongRect(std::numeric_limits<int>::min() + 1l, std::numeric_limits<int>::min() + 1l, std::numeric_limits<int>::max() * 2l - 1l, std::numeric_limits<int>::max() * 2l - 1l));
    // Spaces.push_back(LongRect((std::numeric_limits<int>::min()) / 128, (std::numeric_limits<int>::min()) / 128, (std::numeric_limits<int>::max()) / 64, (std::numeric_limits<int>::max()) / 64));
    Spaces.push_back(LongRect(-600000, -600000, 1200000, 1200000)); // Above tries were a childish thought.
    std::map<EWorldObjectType, int> ObjectsSize;
    ObjectsSize[EWorldObjectType::Planet] = 700;
    ObjectsSize[EWorldObjectType::SpaceStation] = 500;
    ObjectsSize[EWorldObjectType::Terra] = 30000;
    
    int iMaxWorldObjects = ((int)EWorldObjectType::MaxItem - 1);
    
    EWorldObjectType eTryingToCreate = EWorldObjectType::Terra;
    int iRandX, iRandY;
    int iSize = ObjectsSize[eTryingToCreate];
    
    while(!Spaces.empty())
    {
        // Get next space and pop it from the stack.
        LongRect coord = Spaces.back();
        Spaces.pop_back();
        
        if(coord.m_Width <= iSize || coord.m_Height <= iSize)
        {
            continue;
        }
        
        int iRandWidth = static_cast<int>(((rand() % 100) / 100.f) * (coord.m_Width - iSize));
        int iRandHeight = static_cast<int>(((rand() % 100) / 100.f) * (coord.m_Height - iSize));
        iRandX = coord.m_Left + iSize + iRandWidth;
        iRandY = coord.m_Top + iSize + iRandHeight;
        
        // Insert Object into m_WorldInfo
        std::pair<int, int> quadrant_idx = GetQuadrantIndexAtPos(GetQuadrantCorrectedPos(sf::Vector2f(static_cast<float>(iRandX), static_cast<float>(iRandY))));
        std::pair<std::pair<int, int>, EWorldObjectType> worldinfo_idx(quadrant_idx, eTryingToCreate);
        sf::Vector2f CreatePosition(static_cast<float>(iRandX), static_cast<float>(iRandY));
        m_WorldInfo[worldinfo_idx].push_back(WorldObjectInformation(eTryingToCreate, CreatePosition, iSize));
        
        // Build Spaces for top & bottom & left & right
        LongRect LeftRectangle(coord.m_Left, coord.m_Top, (iRandX - coord.m_Left), coord.m_Height);
        LongRect RightRectangle((iRandX + iSize), coord.m_Top, (coord.m_Width - LeftRectangle.m_Width - iSize), coord.m_Height);
        LongRect TopRectangle(coord.m_Left, coord.m_Top, coord.m_Width, (iRandY - coord.m_Top));
        LongRect BottomRectangle(coord.m_Left, (iRandY + iSize), coord.m_Width, (coord.m_Height - TopRectangle.m_Height - iSize));
        
        // Decide wether left & right or top & bottom is bigger.
        long AreaFromLeftAndRight = (LeftRectangle.m_Width + LeftRectangle.m_Height + RightRectangle.m_Width + RightRectangle.m_Height);
        long AreaFromTopAndBottom = (TopRectangle.m_Width + TopRectangle.m_Height + BottomRectangle.m_Width + BottomRectangle.m_Height);
        if(AreaFromLeftAndRight > AreaFromTopAndBottom)
        {
            // NOTE: this is deprecated, as the width here gets always to iSize and won´t be further used.
            // left & right area is bigger.
            // so resize the area from top & bottom
            /*
            TopRectangle.m_Left += LeftRectangle.m_Width;
            TopRectangle.m_Width -= (LeftRectangle.m_Width + RightRectangle.m_Width);
            BottomRectangle.m_Left = TopRectangle.m_Left;
            BottomRectangle.m_Width = TopRectangle.m_Width;
            */
            // push the 2 spaces to stack.
            // but only, if next size fits into area.
            if(RightRectangle.m_Width > 0 && RightRectangle.m_Height > 0 && RightRectangle.m_Width > iSize && RightRectangle.m_Height > iSize)
            {
                Spaces.push_back(RightRectangle);
            }
            if(LeftRectangle.m_Width > 0 && LeftRectangle.m_Height > 0 && LeftRectangle.m_Width > iSize && LeftRectangle.m_Height > iSize)
            {
                Spaces.push_back(LeftRectangle);
            }
        }
        else
        {
            // NOTE: this is deprecated, as the height here gets always to iSize and won´t be further used.
            // top & bottom area is bigger.
            // so resize the area from left & right
            /*
            LeftRectangle.m_Top += TopRectangle.m_Height;
            LeftRectangle.m_Height -= (TopRectangle.m_Height + BottomRectangle.m_Height);
            RightRectangle.m_Top = LeftRectangle.m_Top;
            RightRectangle.m_Height = LeftRectangle.m_Height;
            */
            // push the 2 spaces to stack.
            // but only, if next size fits into area.
            if(TopRectangle.m_Width > 0 && TopRectangle.m_Height > 0 && TopRectangle.m_Width > iSize && TopRectangle.m_Height > iSize)
            {
                Spaces.push_back(TopRectangle);
            }
            if(BottomRectangle.m_Width > 0 && BottomRectangle.m_Height > 0 && BottomRectangle.m_Width > iSize && BottomRectangle.m_Height > iSize)
            {
                Spaces.push_back(BottomRectangle);
            }
        }
        
        // set size for next element
        eTryingToCreate = (EWorldObjectType)(rand() % iMaxWorldObjects);
        iSize = ObjectsSize[eTryingToCreate];
    }
    std::cout << "Finished :D" << std::endl;
    // std::cout << "[WorldManager]: Generated " << m_WorldInfo[EWorldObjectType::Planet].size() << " Planets and " << m_WorldInfo[EWorldObjectType::SpaceStation].size() << " SpaceStations." << std::endl;
}

void WorldManager::LoadGame(std::string strPath)
{
    rapidxml::xml_document<> doc;
    std::ifstream file(strPath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content(buffer.str());
    file.close();
    
    doc.parse<0>(&content[0]);
    
    rapidxml::xml_node<>* pRoot = doc.first_node("savegame");
    m_iSeed = atoi(pRoot->first_attribute("seed")->value());
    
    rapidxml::xml_node<>* pMapnode = pRoot->first_node("GameObject");
    while(pMapnode)
    {
        SerializeNode* pGameObjectNode = new SerializeNode(std::string(pMapnode->name()), ESerializeNodeType::Class, std::string(pMapnode->first_attribute("value")->value()));
        pGameObjectNode->Accept(new XMLReadVisitor(pMapnode));
        
        GameObject* pCreatedGameObject = GameObject::Deserialize(pGameObjectNode);
        
        // Check if given GameObject has a IPosition to create a Quadrant
        // Reason: Everywhere a Asteroid is already generated or something else, the player was already
        //          so we just refresh by automation all quadrants that were be visited already.
        IPosition* pPositionComponent = static_cast<IPosition*>(pCreatedGameObject->GetComponent(EComponentType::Position));
        if(pPositionComponent != nullptr)
        {
            sf::Vector2f TopLeftPosition = GetQuadrantCorrectedPos(pPositionComponent->GetPosition());
            if(GetQuadrant(GetQuadrantIndexAtPos(TopLeftPosition)) == nullptr)
            {
                // Add quadrant but ignore please.. really please the world generation for dynamic things.
                AddQuadrant(new Quadrant(TopLeftPosition), true);
            }
        }
        
        pMapnode = pMapnode->next_sibling();
    }
    
    doc.clear();
}

void WorldManager::SaveGame(std::string strPath)
{
    auto pXMLVisitor = new XMLWriteVisitor(strPath, m_iSeed);
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

sf::Vector2f WorldManager::GetNextNearestObjectPos(sf::Vector2f Position, EWorldObjectType eType)
{
    sf::Vector2f NearestPos(FLT_MAX, FLT_MAX);
    
    auto it = m_WorldInfo.begin();
    while(it != m_WorldInfo.end())
    {
        // If otherwise then Null-Type, then skip all other Object-Types.
        if(eType != EWorldObjectType::Null && it->first.second != eType)
        {
            it++;
            continue;
        }
        auto it_objects = it->second.begin();
        while(it_objects != it->second.end())
        {
            sf::Vector2f Difference = it_objects->GetPosition() - Position;
            
            float fQuadrLength = NearestPos.x * NearestPos.x + NearestPos.y * NearestPos.y;
            float fOtherQuadrLength = Difference.x * Difference.x + Difference.y * Difference.y;
            
            if(fOtherQuadrLength >= 3000.f && fOtherQuadrLength < fQuadrLength)
            {
                NearestPos = it_objects->GetPosition();
            }
            
            it_objects++;
        }
        it++;
    }
    
    return NearestPos;
}