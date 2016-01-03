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
        delete(*it);
        it++;
    }
    m_Elements.clear();
    m_Elements.shrink_to_fit();
}

void SerializeNode::AddElement(SerializeNode *pNode)
{
    if(m_eNodeType == ESerializeNodeType::Property)
    {
        throw std::runtime_error("SerializeNode´s from type Property may not allowed to have Elements.");
    }
    m_Elements.push_back(pNode);
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
        if((*it) == pNode)
        {
            delete((*it));
            m_Elements.erase(it);
            break;
        }
        it++;
    }
}