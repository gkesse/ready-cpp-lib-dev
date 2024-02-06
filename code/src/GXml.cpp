//===============================================
#include "GXml.h"
#include "GDebug.h"
//===============================================
GXml::GXml() {
    m_doc = 0;
    m_node = 0;
    m_doc2 = 0;
    m_node2 = 0;
}
//===============================================
GXml::GXml(xmlDocPtr _doc2, xmlNodePtr _node2, xmlNodePtr _node) {
    m_doc = 0;
    m_node = _node;
    m_doc2 = _doc2;
    m_node2 = _node2;
}
//===============================================
GXml::GXml(const GXml& _xml) {
    *this = _xml;
}
//===============================================
GXml::~GXml() {
    clear();
}
//===============================================
void GXml::clear() {
    if(m_doc) xmlFreeDoc(m_doc);
    m_doc = 0;
    m_node = 0;
    m_node2 = 0;
}
//===============================================
bool GXml::createDoc() {
    clear();
    m_doc = xmlNewDoc(BAD_CAST("1.0"));
    if(!m_doc) {
        slog(eGERR, "La création du document XML a échoué.");
        return false;
    }
    m_node = xmlNewNode(NULL, BAD_CAST("rdv"));
    if(!m_node) {
        slog(eGERR, "La création du noeud racine a échoué."
                    "|doc=%p", m_doc);
        return false;
    }
    xmlDocSetRootElement(m_doc, m_node);
    m_doc2 = m_doc;
    m_node2 = m_node;
    return true;
}
//===============================================
bool GXml::loadXml(const GString& _data) {
    clear();
    m_doc = xmlParseDoc(BAD_CAST(_data.c_str()));
    if(!m_doc) {
        slog(eGERR, "Le chargement du document XML a échoué.");
        return false;
    }
    m_node = xmlDocGetRootElement(m_doc);
    if(!m_node) {
        slog(eGERR, "Le chargement du noeud racine a échoué."
                    "|doc=%p", m_doc);
        return false;
    }
    m_doc2 = m_doc;
    m_node2 = m_node;
    return true;
}
//===============================================
bool GXml::loadNode(const GString& _data) {
    if(!m_node) return false;
    if(_data.isEmpty()) return false;
    xmlNodePtr lNodes;
    xmlParseInNodeContext(m_node, _data.c_str(), _data.size(), 0, &lNodes);
    xmlNodePtr lNode = lNodes->children;
    if(!lNode) {
        slog(eGERR, "Le chargement du noeud XML a échoué."
                    "|doc=%p"
                    "|node=%s", m_doc, (char*)m_node->name);
        return false;
    }
    while(lNode) {
        xmlAddChild(m_node, xmlCopyNode(lNode, 1));
        lNode = lNode->next;
    }
    xmlFreeNode(lNodes);
    return true;
}
//===============================================
void GXml::setValue(const GString& _value) {
    if(!m_node) return;
    xmlNodeSetContent(m_node, BAD_CAST(_value.c_str()));
}
//===============================================
GXml GXml::addObj(const GString& _name) {
    if(!m_node) return GXml(m_doc2, m_node2, 0);
    xmlNodePtr lNode = xmlNewNode(NULL, BAD_CAST(_name.c_str()));
    xmlAddChild(m_node, lNode);
    return GXml(m_doc2, m_node2, lNode);
}
//===============================================
GXml GXml::addNode(const GString& _path, const GString& _value) {
    if(!m_node) return GXml(m_doc2, m_node2, 0);
    if(_path.isEmpty()) return GXml(m_doc2, m_node2, 0);

    GString lPath;
    GXml lNode = *this;

    if(_path[0] == '/') lPath += "/";
    int lCount = _path.countSep("/");

    for(int i = 0; i < lCount; i++) {
        GString lPathI = _path.extractSep("/", i);
        if(i != 0) lPath += "/";
        lPath += lPathI;
        if(!existNode(lPath)) {
            lNode = lNode.addObj(lPathI);
        }
        else {
            lNode = getNode(lPath);
        }
    }

    if(!_value.isEmpty()) {
        xmlNodeSetContent(lNode.m_node, BAD_CAST(_value.c_str()));
    }
    return lNode ;
}
//===============================================
void GXml::addData(const GString& _name, const GString& _value) {
    if(!m_node) return;
    xmlNodePtr lNode = xmlNewNode(NULL, BAD_CAST(_name.c_str()));
    xmlNodeSetContent(lNode, BAD_CAST(_value.c_str()));
    xmlAddChild(m_node, lNode);
}
//===============================================
bool GXml::existNode(const GString& _path) const {
    if(!m_node) return false;
    return (countNode(_path) != 0);
}
//===============================================
int GXml::countNode(const GString& _path) const {
    if(!m_doc2) return 0;
    xmlXPathContextPtr lXPathC = xmlXPathNewContext(m_doc2);
    if(!lXPathC) return 0;
    xmlNodePtr lRoot = m_node;
    if(_path[0] == '/') lRoot = m_node2;
    xmlXPathObjectPtr lXPathO = xmlXPathNodeEval(lRoot, BAD_CAST(_path.c_str()), lXPathC);
    if(!lXPathO) return 0;
    xmlXPathFreeContext(lXPathC);
    int lCount = 0;
    if(lXPathO->nodesetval) {
        lCount = lXPathO->nodesetval->nodeNr;
    }
    xmlXPathFreeObject(lXPathO);
    return lCount;
}
//===============================================
GXml GXml::getNode(const GString& _path) const {
    if(!m_doc2) return GXml(m_doc2, m_node2, 0);
    xmlXPathContextPtr lXPathC = xmlXPathNewContext(m_doc2);
    if(!lXPathC) return GXml(m_doc2, m_node2, 0);
    xmlNodePtr lRoot = m_node;
    if(_path[0] == '/') lRoot = m_node2;
    xmlXPathObjectPtr lXPathO = xmlXPathNodeEval(lRoot, BAD_CAST(_path.c_str()), lXPathC);
    if(!lXPathO) return GXml(m_doc2, m_node2, 0);
    xmlXPathFreeContext(lXPathC);
    xmlNodePtr lNode = 0;
    if(lXPathO->nodesetval) {
        if(lXPathO->nodesetval->nodeNr) {
            lNode = lXPathO->nodesetval->nodeTab[0];
        }
    }
    xmlXPathFreeObject(lXPathO);
    return GXml(m_doc2, m_node2, lNode);
}
//===============================================
GString GXml::getValue() const {
    if(!m_node) return "";
    GString lValue = (char*)xmlNodeGetContent(m_node);
    return lValue;
}
//===============================================
GString GXml::toString() const {
    if(!m_doc) return "";
    xmlChar* lBuffer = NULL;
    int lSize;
    xmlDocDumpFormatMemoryEnc(m_doc, &lBuffer, &lSize, "UTF-8", 4);
    GString lData((char*)lBuffer, lSize);
    xmlFree(lBuffer);
    return lData;
}
//===============================================
GString GXml::toNode() const {
    if(!m_doc2 || !m_node) return "";
    GString lData;
    xmlBufferPtr lBuffer = xmlBufferCreate();
    xmlNodeDump(lBuffer, m_doc2, m_node, 0, 1);
    lData = (char*)lBuffer->content;
    xmlBufferFree(lBuffer);
    return lData;
}
//===============================================
GXml& GXml::operator=(const GXml& _xml) {
    m_doc = 0;
    m_node = _xml.m_node;
    m_doc2 = _xml.m_doc2;
    m_node2 = _xml.m_node2;
    return *this;
}
//===============================================
std::ostream& operator<<(std::ostream& _os, const GXml& _xml) {
    _os << _xml.toString();
    return _os;
}
//===============================================
