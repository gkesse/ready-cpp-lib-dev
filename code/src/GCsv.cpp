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
void GCsv::createCsv() {
    clear();
    m_root = new GCsv;
    m_root->m_type = Type::CSV_TYPE_ROOT;
    m_node = m_root;
}
//===============================================
GCsv GCsv::addRow() {
    if(!m_node) return GCsv();
    if(m_node->m_type == Type::CSV_TYPE_COL) eThrow("Impossible d'ajouter un élément ROW à partir d'un élément COL.");
    GCsv* lNode = new GCsv;
    lNode->m_type = Type::CSV_TYPE_ROW;
    GCsv* lNode2 = m_node;
    bool isRow = false;
    if(!lNode2->m_next) {
        lNode2->m_next = lNode;
    }
    else {
        if(lNode2->m_type == Type::CSV_TYPE_ROOT) {
            lNode2 = lNode2->m_next;
        }
        while(lNode2) {
            if(!lNode2->m_next) break;
            if(lNode2->m_next->m_type == Type::CSV_TYPE_ROW) {
                GCsv* lNext2 = lNode2->m_next;
                lNode2->m_next = lNode;
                lNode->m_next = lNext2;
                isRow = true;
                break;
            }
            lNode2 = lNode2->m_next;
        }
        if(!isRow) lNode2->m_next = lNode;
    }
    return GCsv(lNode);
}
//===============================================
GCsv GCsv::appendRow() {
    if(!m_node) return GCsv();
    if(m_node->m_type != Type::CSV_TYPE_ROOT) eThrow("Impossible d'ajouter un élément ROW à partir d'un élément non ROOT.");
    GCsv* lNode = new GCsv;
    lNode->m_type = Type::CSV_TYPE_ROW;
    GCsv* lNode2 = m_node;
    while(lNode2->m_next) {
        lNode2 = lNode2->m_next;
    }
    lNode2->m_next = lNode;
    return GCsv(lNode);
}
//===============================================
GCsv GCsv::addCol(const GString& _value) {
    if(!m_node) return GCsv();
    if(m_node->m_type == Type::CSV_TYPE_ROOT) eThrow("Impossible d'ajouter un élément COL à partir d'un élément ROOT.");
    GCsv* lNode = new GCsv;
    lNode->m_type = Type::CSV_TYPE_COL;
    lNode->m_value = _value;
    GCsv* lNode2 = m_node;
    bool isCol = false;
    if(!lNode2->m_next) {
        lNode2->m_next = lNode;
    }
    else {
        while(lNode2) {
            if(!lNode2->m_next) break;
            if(lNode2->m_next->m_type == Type::CSV_TYPE_ROW ||
               lNode2->m_next->m_type == Type::CSV_TYPE_COL) {
                GCsv* lNext2 = lNode2->m_next;
                lNode2->m_next = lNode;
                lNode->m_next = lNext2;
                isCol = true;
                break;
            }
            lNode2 = lNode2->m_next;
        }
        if(!isCol) lNode2->m_next = lNode;
    }
    return GCsv(lNode);
}
//===============================================
GCsv GCsv::appendCol(const GString& _value) {
    if(!m_node) return GCsv();
    if(m_node->m_type != Type::CSV_TYPE_ROW) eThrow("Impossible d'ajouter un élément COL à partir d'un élément non ROW.");
    GCsv* lNode = new GCsv;
    lNode->m_type = Type::CSV_TYPE_COL;
    lNode->m_value = _value;
    GCsv* lNode2 = m_node;
    while(lNode2->m_next) {
        if(lNode2->m_next->m_type == Type::CSV_TYPE_ROW) break;
        lNode2 = lNode2->m_next;
    }
    if(!lNode2->m_next) {
        lNode2->m_next = lNode;
    }
    else {
        GCsv* lNode3 = lNode2->m_next;
        lNode2->m_next = lNode;
        lNode->m_next = lNode3;
    }
    return GCsv(lNode);
}
//===============================================
int GCsv::countRows() const {
    if(!m_node) return 0;
    if(m_node->m_type != Type::CSV_TYPE_ROOT) eThrow("Impossible de compter les lignes à partir d'un élément non ROOT.");
    GCsv* lNode = m_node;
    int lCount = 0;
    while(lNode) {
        if(lNode->m_type == Type::CSV_TYPE_ROW) lCount++;
        lNode = lNode->m_next;
    }
    return lCount;
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
