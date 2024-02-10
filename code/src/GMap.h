//===============================================
#ifndef _GMap_
#define _GMap_
//===============================================
#include "GString.h"
//===============================================
class GMap {
public:
    enum class Type {
        MAP_TYPE_UNKNOWN
        , MAP_TYPE_ROOT
        , MAP_TYPE_ELEMENT
    };

public:
    GMap();
    GMap(GMap* _node);
    GMap(const GMap& _map);
    virtual ~GMap();
    void clear();
    void createMap();
    void loadMap(const GString& _data, const GString& _sepMap = "&", const GString& _sepData = "=");
    void loadMap(const GMap& _map);
    GMap addData(const GString& _key, const GString& _value);
    GString getData(const GString& _key) const;
    int size() const;
    GString toString() const;
    GMap& operator=(const GMap& _map);

private:
    GMap* m_root;
    GMap* m_node;
    GMap* m_next;
    GString m_key;
    GString m_value;
    Type m_type;
    int m_size;
};
//===============================================
#endif
//===============================================
