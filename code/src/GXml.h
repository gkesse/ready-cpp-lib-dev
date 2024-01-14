//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GXml {
public:
    GXml();
    GXml(xmlDocPtr _doc2, xmlNodePtr _node2, xmlNodePtr _node);
    GXml(const GXml& _xml);
    virtual ~GXml();
    void clear();
    bool createDoc();
    bool loadXml(const GString& _data);
    bool loadNode(const GString& _data);
    void setValue(const GString& _value);
    GXml addObj(const GString& _name);
    GXml addNode(const GString& _path, const GString& _value = "");
    void addData(const GString& _name, const GString& _value);
    bool existNode(const GString& _path) const;
    int countNode(const GString& _path) const;
    GXml getNode(const GString& _path) const;
    GString getValue() const;
    GString toString() const;
    GString toNode() const;

    GXml& operator=(const GXml& _xml);

    friend std::ostream& operator<<(std::ostream& _os, const GXml& _xml);

protected:
    xmlDocPtr m_doc;
    xmlDocPtr m_doc2;
    xmlNodePtr m_node;
    xmlNodePtr m_node2;
};
//===============================================
#endif
//===============================================
