//===============================================
#include "GMap.h"
//===============================================
GMap::GMap() {
    m_root = 0;
    m_node = 0;
    m_next = 0;
    m_type = Type::MAP_TYPE_UNKNOWN;
    m_size = 0;
}
//===============================================
GMap::GMap(GMap* _node) {
    m_root = 0;
    m_node = _node;
    m_next = 0;
    m_type = _node->m_type;
    m_size = 0;
}
//===============================================
GMap::GMap(const GMap& _map) {
    *this = _map;
}
//===============================================
GMap::~GMap() {
    clear();
}
//===============================================
void GMap::clear() {
    if(m_root) {
        GMap* lNode = m_root;
        while(lNode) {
            GMap* lPrev = lNode;
            lNode = lNode->m_next;
            delete lNode;
        }
        m_root = 0;
    }
    m_node = 0;
    m_next = 0;
    m_type = Type::MAP_TYPE_UNKNOWN;
    m_size = 0;
}
//===============================================
void GMap::createMap() {
    clear();
    m_root = new GMap;
    m_root->m_type = Type::MAP_TYPE_ROOT;
    m_node = m_root;
}
//===============================================
void GMap::loadMap(const GString& _data, const GString& _sepMap, const GString& _sepData) {
    if(_data.isEmpty()) return;
    if(!m_node) {
        slog(eGERR, "Le noeud courant n'est pas initialisé."
                    "|sep_map=%s"
                    "|sep_data=%s"
                    "|data=%s", _sepMap.c_str(), _sepData.c_str(), _data.c_str());
        return;
    }
    int lCount = _data.count(_sepMap);
    for(int i = 0; i < lCount; i++) {
        GString lData = _data.extract(_sepMap, i);
        GString lKey = lData.extract(_sepData);
        GString lValue = lData.extractEnd(_sepData);
        addData(lKey, lValue);
    }
}
//===============================================
void GMap::loadMap(const GMap& _map) {
    if(!m_node) {
        slog(eGERR, "Le noeud courant n'est pas initialisé.");
        return;
    }
    GMap* lNode = _map.m_node;
    while(lNode) {
        if(lNode->m_type == Type::MAP_TYPE_ELEMENT) {
            addData(lNode->m_key, lNode->m_value);
        }
        lNode = lNode->m_next;
    }
}
//===============================================
GMap GMap::addData(const GString& _key, const GString& _value) {
    if(!m_node) {
        slog(eGERR, "Le noeud courant n'est pas initialisé.");
        return GMap();
    }

    GMap* lNode = m_node;
    GMap* lPrev = lNode;
    while(lNode) {
        if(lNode->m_type == Type::MAP_TYPE_ELEMENT) {
            if(lNode->m_key == _key) {
                lNode->m_value = _value;
                return GMap(lNode);
            }
        }
        lPrev = lNode;
        lNode = lNode->m_next;
    }

    GMap* lNew = new GMap;
    lNew->m_type = Type::MAP_TYPE_ELEMENT;
    lNew->m_key = _key;
    lNew->m_value = _value;

    m_size++;
    lPrev->m_next = lNew;
    return GMap(lNew);
}
//===============================================
GString GMap::getData(const GString& _key) const {
    if(!m_node) {
        slog(eGERR, "Le noeud courant n'est pas initialisé.");
        return "";
    }
    GMap* lNode = m_node;
    while(lNode) {
        if(lNode->m_type == Type::MAP_TYPE_ELEMENT) {
            if(lNode->m_key == _key) return lNode->m_value;
        }
        lNode = lNode->m_next;
    }
    return "";
}
//===============================================
GMapKV GMap::getData(int _index) const {
    GMapKV lMapKV;
    if(!m_node) {
        slog(eGERR, "Le noeud courant n'est pas initialisé.");
        return lMapKV;
    }
    GMap* lNode = m_node;
    int lCount = 0;
    while(lNode) {
        if(lNode->m_type == Type::MAP_TYPE_ELEMENT) {
            if(lCount == _index) {
                lMapKV.m_key = lNode->m_key;
                lMapKV.m_value = lNode->m_value;
                return lMapKV;
            }
            lCount++;
        }
        lNode = lNode->m_next;
    }
    return lMapKV;
}
//===============================================
int GMap::size() const {
    return m_size;
}
//===============================================
bool GMap::isKey(const GString& _key) const {
    if(!m_node) {
        slog(eGERR, "Le noeud courant n'est pas initialisé."
                    "|key=%s", _key.c_str());
        return false;
    }

    GMap* lNode = m_node;
    while(lNode) {
        if(lNode->m_type == Type::MAP_TYPE_ELEMENT) {
            if(lNode->m_key == _key) return true;
        }
        lNode = lNode->m_next;
    }

    return false;
}
//===============================================
GString GMap::toString() const {
    if(!m_node) {
        slog(eGERR, "Le noeud courant n'est pas initialisé.");
        return "";
    }
    GString lData;
    GMap* lNode = m_node;
    while(lNode) {
        if(lNode->m_type == Type::MAP_TYPE_ELEMENT) {
            if(!lData.isEmpty()) lData += "\n";
            lData += sformat("%s=%s", lNode->m_key.c_str(), lNode->m_value.c_str());
        }
        lNode = lNode->m_next;
    }
    return lData;
}
//===============================================
GMap& GMap::operator=(const GMap& _map) {
    m_root = 0;
    m_node = _map.m_node;
    m_next = _map.m_next;
    m_type = _map.m_type;
    return *this;
}
//===============================================
