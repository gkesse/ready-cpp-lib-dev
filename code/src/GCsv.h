//===============================================
#ifndef _GCsv_
#define _GCsv_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GCsv {
public:
    enum class Type {
        CSV_TYPE_UNKNOWN
        , CSV_TYPE_ROOT
        , CSV_TYPE_ROW
        , CSV_TYPE_COL
    };

public:
    GCsv();
    GCsv(GCsv* _node);
    GCsv(const GCsv& _csv);
    virtual ~GCsv();
    void clear();
    void createCsv();
    GCsv addRow();
    GCsv appendRow();
    GCsv addCol(const GString& _value);
    GCsv appendCol(const GString& _value);
    int countRows() const;
    GString toString() const;

    GCsv& operator=(const GCsv& _csv);

private:
    std::vector<GCsv*> m_map;
    GCsv* m_root;
    GCsv* m_node;
    GCsv* m_next;
    Type m_type;
    GString m_value;
};
//===============================================
#endif
//===============================================
