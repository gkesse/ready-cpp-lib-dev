//===============================================
#ifndef _GCsv_
#define _GCsv_
//===============================================
#include "GDebug.h"
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
    void loadCsv(const GString& _csv);
    GCsv addRow();
    GCsv appendRow();
    GCsv addCol(const GString& _value);
    GCsv appendCol(const GString& _value);
    void setValue(const GString& _value);
    GCsv getRow(int _row) const;
    GCsv getCol(int _col) const;
    GCsv getCol(int _row, int _col) const;
    int countRows() const;
    int countCols() const;
    int size() const;
    GString toRow() const;
    GString toCol() const;
    GString toString() const;

    GCsv& operator=(const GCsv& _csv);

private:
    GCsv* m_root;
    GCsv* m_node;
    GCsv* m_next;
    Type m_type;
    GString m_value;
    GDebug slog;
};
//===============================================
#endif
//===============================================
