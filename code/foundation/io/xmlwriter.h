#pragma once
#ifndef IO_XMLWRITER_H
#define IO_XMLWRITER_H
//------------------------------------------------------------------------------
/**
    @class IO::XmlWriter
  
    Write XML-formatted data to a stream.
    
    (C) 2006 Radon Labs GmbH
*/    
#include "io/streamwriter.h"
#include "tinyxml/tinyxml.h"

//------------------------------------------------------------------------------
namespace IO
{
class XmlWriter : public IO::StreamWriter
{
    __DeclareClass(XmlWriter);
public:
    /// constructor
    XmlWriter();
    /// destructor
    virtual ~XmlWriter();
    /// begin writing the stream
    virtual bool Open();
    /// end writing the stream
    virtual void Close();

    /// begin a new node under the current node
    bool BeginNode(const Util::String& nodeName);
    /// end current node, set current node to parent
    void EndNode();
    /// write content text
    void WriteContent(const Util::String& text);

    /// set string attribute on current node
    void SetString(const Util::String& name, const Util::String& value);
    /// set bool attribute on current node
    void SetBool(const Util::String& name, bool value);
    /// set int attribute on current node
    void SetInt(const Util::String& name, int value);
    /// set float attribute on current node
    void SetFloat(const Util::String& name, float value);
    /// set float4 attribute on current node
    void SetFloat4(const Util::String& name, const Math::float4& value);
    /// set matrix44 attribute on current node
    void SetMatrix44(const Util::String& name, const Math::matrix44& value);

private:
    TiXmlDocument* xmlDocument;
    TiXmlElement* curNode;
};

} // namespace IO
//------------------------------------------------------------------------------
#endif

