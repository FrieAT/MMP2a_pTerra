/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "stdafx.h"

#include "XMLReadVisitor.h"
#include "SerializeNode.h"

XMLReadVisitor::XMLReadVisitor(rapidxml::xml_node<>* pGameObjectNode)
{
    m_pCurrentNode = pGameObjectNode;
    
    /*
    while(game_object)
    {
        
        game_object = game_object->next_sibling();
    }
    */
}

XMLReadVisitor::~XMLReadVisitor()
{
    m_File.clear();
}

void XMLReadVisitor::Visit(SerializeNode* pNode)
{
    rapidxml::xml_node<>* pChildNode = m_pCurrentNode->first_node();
    while(pChildNode)
    {
        std::string strName = std::string(pChildNode->name());
        ESerializeNodeType eNodeType = static_cast<ESerializeNodeType>(atoi(pChildNode->first_attribute("type")->value()));
        std::string strValue;
        if(eNodeType == ESerializeNodeType::Property)
        {
            strValue = std::string(pChildNode->first_attribute("value")->value());
        }
        
        SerializeNode* pChild = new SerializeNode(strName, eNodeType, strValue);
        
        if(eNodeType != ESerializeNodeType::Property)
        {
            m_pCurrentNode = pChildNode;
            pChild->Accept(this);
        }
        
        pNode->AddElement(pChild);
        
        pChildNode = pChildNode->next_sibling();
    }
}