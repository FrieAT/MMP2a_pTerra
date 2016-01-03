/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "SerializeNode.h"

SerializeNode::SerializeNode(std::string strName, ESerializeNodeType eNodeType, std::string strValue)
: m_strName(strName)
, m_eNodeType(eNodeType)
, m_strValue(strValue)
{
    
}

SerializeNode::~SerializeNode()
{
    auto it = m_Elements.begin();
    while(it != m_Elements.end())
    {
        delete(it->second);
        it++;
    }
    m_Elements.clear();
}

void SerializeNode::AddElement(SerializeNode *pNode)
{
    if(m_eNodeType == ESerializeNodeType::Property)
    {
        throw std::runtime_error("SerializeNode´s from type Property may not allowed to have Elements.");
    }
    auto it = m_Elements.find(pNode->m_strName);
    if(it != m_Elements.end())
    {
        throw std::runtime_error("Key already used, use a other key or remove old value.");
    }
    m_Elements[pNode->m_strName] = pNode;
}

void SerializeNode::RemoveElement(SerializeNode *pNode)
{
    if(m_eNodeType == ESerializeNodeType::Property)
    {
        throw std::runtime_error("SerializeNode´s from type Property may not allowed to have Elements.");
    }
    auto it = m_Elements.begin();
    while(it != m_Elements.end())
    {
        if(it->second == pNode)
        {
            delete(it->second);
            m_Elements.erase(it);
            break;
        }
        it++;
    }
}