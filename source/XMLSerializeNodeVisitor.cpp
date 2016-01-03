/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "XMLSerializeNodeVisitor.h"
#include "SerializeNode.h"

XMLSerializeNodeVisitor::XMLSerializeNodeVisitor(std::string strPath)
: m_iCurrentDepth(1)
{
    m_File.open(strPath);
    if(!m_File.is_open())
    {
        throw std::runtime_error("Could not open file at given path.");
    }
    m_File << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    m_File << "<savegame>\n";
}

XMLSerializeNodeVisitor::~XMLSerializeNodeVisitor()
{
    m_File << "</savegame>\n";
    m_File.flush();
    m_File.close();
}

void XMLSerializeNodeVisitor::Visit(SerializeNode* pNode)
{
    if(pNode->GetType() == ESerializeNodeType::Property)
    {
        for (unsigned int i = 0; i < m_iCurrentDepth; i++) { m_File << "\t"; }
        m_File << "<" << pNode->GetName();
        if(pNode->GetValue().length() > 0)
        {
            m_File << " value=\"" << pNode->GetValue() << "\"";
        }
        m_File << " />\n";
    }
    else
    {
        for (unsigned int i = 0; i < m_iCurrentDepth; i++) { m_File << "\t"; }
        m_File << "<" << pNode->GetName();
        if(pNode->GetValue().length() > 0)
        {
            m_File << " value=\"" << pNode->GetValue() << "\"";
        }
        m_File << ">\n";
        m_iCurrentDepth++;
        auto elements = pNode->GetChildren();
        auto it = elements.begin();
        while(it != elements.end())
        {
            it->second->Accept(this);
            it++;
        }
        m_iCurrentDepth--;
        for (unsigned int i = 0; i < m_iCurrentDepth; i++) { m_File << "\t"; }
        m_File << "</" << pNode->GetName() << ">\n";
    }
}