//===============================================
#include "GCsv.h"
#include "GDebug.h"
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
    *this = _csv;
}
//===============================================
GCsv::~GCsv() {
    clear();
}
//===============================================
void GCsv::clear() {
    if(m_root) {
        GCsv* lNode = m_root;
        while(lNode) {
            GCsv* lPrev = lNode;
            lNode = lNode->m_next;
            delete lPrev;
        }
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
void GCsv::loadCsv(const GString& _csv) {
    if(_csv.isEmpty()) return;
    createCsv();
    std::istringstream lStream(_csv.c_str());
    std::string lToken, lToken2;
    while(std::getline(lStream, lToken, '\n')) {
        std::istringstream lStream2(lToken);
        GCsv lNode = appendRow();
        while(std::getline(lStream2, lToken2, ';')) {
            lNode.appendCol(lToken2);
        }
    }
}
//===============================================
GCsv GCsv::addRow() {
    if(!m_node) return GCsv();
    if(m_node->m_type == Type::CSV_TYPE_COL) {
        slog(eGERR, "Un élément COL ne peut pas ajouter un élément ROW."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d", m_root, m_node, m_type);
        return GCsv();
    }
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
    if(m_node->m_type != Type::CSV_TYPE_ROOT) {
        slog(eGERR, "Un élément non ROOT ne peut pas ajouter un élément ROW."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d", m_root, m_node, m_type);
        return GCsv();
    }
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
    if(m_node->m_type == Type::CSV_TYPE_ROOT) {
        slog(eGERR, "Un élément ROOT ne peut pas ajouter un élément COL."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d", m_root, m_node, m_type);
        return GCsv();
    }
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
    if(m_node->m_type != Type::CSV_TYPE_ROW) {
        slog(eGERR, "Un élément non ROW ne peut pas ajouter un élément COL."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d", m_root, m_node, m_type);
        return GCsv();
    }
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
void GCsv::setValue(const GString& _value) {
    if(!m_node) return;
    if(m_node->m_type != Type::CSV_TYPE_COL) {
        slog(eGERR, "Un élément non COL ne possède pas de valeur."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d"
                    "|valeur=%s", m_root, m_node, m_type, _value.c_str());
        return;
    }
    m_node->m_value = _value;
}
//===============================================
GCsv GCsv::getRow(int _row) const {
    if(!m_node) return GCsv();
    if(m_node->m_type != Type::CSV_TYPE_ROOT) {
        slog(eGERR, "Un élément non ROOT ne peut pas récupérer un élément ROW."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d"
                    "|row=%d", m_root, m_node, m_type, _row);
        return GCsv();
    }
    GCsv* lNode = m_node;
    int lRow = 0;
    while(lNode) {
        if(lNode->m_type == Type::CSV_TYPE_ROW) {
            if(lRow == _row) break;
            lRow++;
        }
        lNode = lNode->m_next;
    }
    return GCsv(lNode);
}
//===============================================
GCsv GCsv::getCol(int _col) const {
    if(!m_node) return GCsv();
    if(m_node->m_type != Type::CSV_TYPE_ROW) {
        slog(eGERR, "Un élément non ROW ne peut pas récupérer un élément COL."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d"
                    "|col=%d", m_root, m_node, m_type, _col);
        return GCsv();
    }
    GCsv* lNode = m_node->m_next;
    int lCol = 0;
    while(lNode) {
        if(lNode->m_type == Type::CSV_TYPE_ROW) break;
        if(lNode->m_type == Type::CSV_TYPE_COL) {
            if(lCol == _col) break;
            lCol++;
        }
        lNode = lNode->m_next;
    }
    return GCsv(lNode);
}
//===============================================
GCsv GCsv::getCol(int _row, int _col) const {
    if(!m_node) return GCsv();
    if(m_node->m_type != Type::CSV_TYPE_ROOT) {
        slog(eGERR, "Un élément non ROOT ne peut pas récupérer un élément COL."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d"
                    "|row=%s"
                    "|col=%d", m_root, m_node, m_type, _row, _col);
        return GCsv();
    }
    return getRow(_row).getCol(_col);
}
//===============================================
int GCsv::countRows() const {
    if(!m_node) return 0;
    if(m_node->m_type != Type::CSV_TYPE_ROOT) {
        slog(eGERR, "Un élément non ROOT ne peut pas compter le nombre de lignes."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d", m_root, m_node, m_type);
        return 0;
    }
    GCsv* lNode = m_node;
    int lCount = 0;
    while(lNode) {
        if(lNode->m_type == Type::CSV_TYPE_ROW) lCount++;
        lNode = lNode->m_next;
    }
    return lCount;
}
//===============================================
int GCsv::countCols() const {
    if(!m_node) return 0;
    if(m_node->m_type != Type::CSV_TYPE_ROOT) {
        slog(eGERR, "Un élément non ROOT ne peut pas compter le nombre de colonnes."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d", m_root, m_node, m_type);
        return 0;
    }
    if(!m_node->m_next) return 0;
    if(m_node->m_next->m_type != Type::CSV_TYPE_ROW) {
        slog(eGERR, "Un élément ROOT ne peut pas être suivi par un élément ROW."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d", m_root, m_node, m_type);
        return 0;
    }
    GCsv* lNode = m_node->m_next->m_next;
    int lCount = 0;
    while(lNode) {
        if(lNode->m_type == Type::CSV_TYPE_ROW) break;
        if(lNode->m_type == Type::CSV_TYPE_COL) lCount++;
        lNode = lNode->m_next;
    }
    return lCount;
}
//===============================================
int GCsv::size() const {
    if(!m_node) return 0;
    if(m_node->m_type != Type::CSV_TYPE_ROOT) {
        slog(eGERR, "Un élément non ROOT ne peut pas compter le nombre d'éléments."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d", m_root, m_node, m_type);
        return 0;
    }
    GCsv* lNode = m_node;
    int lCount = 0;
    while(lNode) {
        if(lNode->m_type == Type::CSV_TYPE_COL) lCount++;
        lNode = lNode->m_next;
    }
    return lCount;
}
//===============================================
GString GCsv::toRow() const {
    if(!m_node) return "";
    if(m_node->m_type != Type::CSV_TYPE_ROW) {
        slog(eGERR, "Un élément non ROW ne peut pas récupérer une ligne de données."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d", m_root, m_node, m_type);
        return "";
    }
    GCsv* lNode = m_node->m_next;
    GString lData;
    bool isCol = false;
    while(lNode) {
        if(lNode->m_type == Type::CSV_TYPE_ROW) break;
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
GString GCsv::toCol() const {
    if(!m_node) return "";
    if(m_node->m_type != Type::CSV_TYPE_COL) {
        slog(eGERR, "Un élément non COL ne possède pas de valeur."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d", m_root, m_node, m_type);
        return "";
    }
    return m_node->m_value;
}
//===============================================
GString GCsv::toString() const {
    if(!m_node) return "";
    if(m_node->m_type != Type::CSV_TYPE_ROOT) {
        slog(eGERR, "Un élément non ROOT ne peut pas récupérer les données CSV."
                    "|root=%p"
                    "|node=%p"
                    "|type=%d", m_root, m_node, m_type);
        return "";
    }
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
