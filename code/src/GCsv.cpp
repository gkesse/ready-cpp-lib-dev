//===============================================
#include "GCsv.h"
#include "GException.h"
//===============================================
GCsv::GCsv() {
    m_root = 0;
    m_node = 0;
    m_next = 0;
    m_type = Type::CSV_TYPE_UNKNOWN;
}
//===============================================
GCsv::GCsv(GCsv* _node) {
    m_root = 0;
    m_node = _node;
    m_next = 0;
    m_type = _node->m_type;
}
//===============================================
GCsv::GCsv(const GCsv& _csv) {
    m_root = 0;
    m_node = _csv.m_node;
    m_next = _csv.m_next;
    m_type = _csv.m_type;
}
//===============================================
GCsv::~GCsv() {
    clear();
}
//===============================================
void GCsv::clear() {
    if(m_root) {
        delete m_root;
    }
}
//===============================================
void GCsv::create() {
    clear();
    m_root = new GCsv;
    m_root->m_type = Type::CSV_TYPE_ROOT;
    m_node = m_root;
}
//===============================================
GCsv GCsv::addRow() {
    if(!m_node) return GCsv();
    if(m_node->m_type == Type::CSV_TYPE_COL) eThrow("Le type est invalide");
    GCsv* lNode = new GCsv;
    lNode->m_type = Type::CSV_TYPE_ROW;
    GCsv* lNext = m_node;
    bool isRow = false;
    if(!lNext->m_next) {
        lNext->m_next = lNode;
    }
    else {
        if(lNext->m_type == Type::CSV_TYPE_ROOT) {
            lNext = lNext->m_next;
        }
        while(1) {
            if(!lNext) break;
            if(!lNext->m_next) break;
            if(lNext->m_next->m_type == Type::CSV_TYPE_ROW) {
                GCsv* lNext2 = lNext->m_next;
                lNext->m_next = lNode;
                lNode->m_next = lNext2;
                isRow = true;
                break;
            }
            lNext = lNext->m_next;
        }
        if(!isRow) lNext->m_next = lNode;
    }
    return GCsv(lNode);
}
//===============================================
GCsv GCsv::addCol(const GString& _value) {
    if(!m_node) return GCsv();
    GCsv* lNode = new GCsv;
    lNode->m_type = Type::CSV_TYPE_COL;
    lNode->m_value = _value;
    m_node->m_next = lNode;
    return GCsv(lNode);
}
//===============================================
int GCsv::size() const {
    return 0;
}
//===============================================
GString GCsv::toString() const {
    if(!m_node) return "";
    GCsv* lNode = m_node;
    GString lData;
    bool isRow = false;
    bool isCol = false;
    while(lNode) {
        if(lNode->m_type == Type::CSV_TYPE_ROW) {
            if(isRow) lData += "\n";
            isRow = true;
            isCol = false;
        }
        if(lNode->m_type == Type::CSV_TYPE_COL) {
            if(isCol) lData += ";";
            lData += lNode->m_value;
            isCol = true;
        }
        lNode = lNode->m_next;
    }
    return lData;
}
//===============================================
GCsv& GCsv::operator=(const GCsv& _csv) {
    m_root = 0;
    m_node = _csv.m_node;
    m_next = _csv.m_next;
    m_type = _csv.m_type;
    return *this;
}
//===============================================
