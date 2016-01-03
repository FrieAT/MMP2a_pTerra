/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include <string>
#include <fstream>

#include "INodeVisitor.h"

class XMLSerializeNodeVisitor : public INodeVisitor
{
public:
    XMLSerializeNodeVisitor(std::string strPath);
    ~XMLSerializeNodeVisitor();
    void Visit(SerializeNode* pNode);
private:
    unsigned int m_iCurrentDepth;
    std::ofstream m_File;
};