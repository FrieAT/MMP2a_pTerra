/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "INodeVisitor.h"
#include "rapidxml/rapidxml.hpp"

class XMLReadVisitor : public INodeVisitor
{
public:
    XMLReadVisitor(rapidxml::xml_node<>* pGameObjectNode);
    ~XMLReadVisitor();
    void Visit(SerializeNode* pNode);
private:
    unsigned int m_iCurrentDepth;
    rapidxml::xml_document<> m_File;
    rapidxml::xml_node<>* m_pCurrentNode;
};