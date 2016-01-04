/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include <string>
#include <fstream>

#include "INodeVisitor.h"

class XMLWriteVisitor : public INodeVisitor
{
public:
    XMLWriteVisitor(std::string strPath, int iSeed = 1);
    ~XMLWriteVisitor();
    void Visit(SerializeNode* pNode);
private:
    unsigned int m_iCurrentDepth;
    std::ofstream m_File;
};