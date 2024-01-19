//===============================================
// GTree
//===============================================
#include "GTree.h"
#include "GException.h"
//===============================================
GTree::GTree() {
    m_root = 0;
    m_parent = 0;
    m_node = 0;
    m_next = 0;
    m_type = Type::TREE_TYPE_UNKNOWN;
}
//===============================================
GTree::GTree(GTree* _node) {
    m_root = 0;
    m_parent = _node->m_parent;
    m_node = _node;
    m_next = 0;
    m_type = _node->m_type;
}
//===============================================
GTree::GTree(const GTree& _tree) {
    *this = _tree;
}
//===============================================
GTree::~GTree() {
    clear();
}
//===============================================
void GTree::clear() {
    if(m_root) {
        GTree* lNode = m_root;
        while(lNode) {
            GTree* lPrev = lNode;
            lNode = lNode->m_next;
            delete lNode;
        }
    }
}
//===============================================
void GTree::createTree() {
    clear();
    m_root = new GTree;
    m_root->m_type = Type::TREE_TYPE_ROOT;
    m_node = m_root;
}
//===============================================
void GTree::loadTree(const GString& _tree) {
    if(_tree.isEmpty()) return;
    createTree();
    GTree::GNode lRoot;
    lRoot.loadNode(_tree);
    GString lParent = lRoot.getFirst().getParent();
    loadNode(lRoot, lParent);
}
//===============================================
void GTree::loadNode(const GTree::GNode& _root, const GString& _parent) {
    if(_parent.isEmpty()) return;
    int lCount = _root.countNode(_parent);
    for(int i = 0; i < lCount; i++) {
        GTree::GNode lChild = _root.getNode(_parent, i);
        GTree lNode = appendChild(lChild.getValue());
        lNode.loadNode(_root, lChild.getChild());
    }
}
//===============================================
GTree GTree::appendChild(const GString& _value) {
    if(!m_node) return GTree();
    GTree* lNode = new GTree;
    lNode->m_type = Type::TREE_TYPE_ELEMENT;
    lNode->m_parent = m_node;
    lNode->m_value = _value;
    GTree* lNode2 = m_node;
    while(lNode2->m_next) {
        lNode2 = lNode2->m_next;
    }
    lNode2->m_next = lNode;
    return GTree(lNode);
}
//===============================================
GTree GTree::getChild(int _index) const {
    if(!m_node) return GTree();
    GTree* lNode = m_node->m_next;
    int lCount = 0;
    while(lNode) {
        if(lNode->m_parent == m_node) {
            if(lCount == _index) break;
            lCount++;
        }
        lNode = lNode->m_next;
    }
    return GTree(lNode);
}
//===============================================
void GTree::setValue(const GString& _value) {
    if(!m_node) return;
    if(m_node->m_type == Type::TREE_TYPE_ROOT) eThrow("Impossible de modifier la valeur d'un élément ROOT.");
    m_node->m_value = _value;
}
//===============================================
int GTree::countChild() const {
    if(!m_node) return 0;
    GTree* lNode = m_node->m_next;
    int lCount = 0;
    while(lNode) {
        if(lNode->m_parent == m_node) lCount++;
        lNode = lNode->m_next;
    }
    return lCount;
}
//===============================================
int GTree::countNode(const GString& _data, const GString& _node) const {
    if(_data.isEmpty()) return 0;
    int lCount = _data.count("\n");
    int lSize = 0;
    for(int i = 0; i < lCount; i++) {
        GString lData = _data.extract("\n", i);
        GString lNode = lData.extract(";", 0);
        if(lNode == _node) lSize++;
    }
    return lSize;
}
//===============================================
int GTree::size() const {
    if(!m_node) return 0;
    if(m_node->m_type != Type::TREE_TYPE_ROOT) eThrow("Impossible de compter le nombre d'éléments à partir d'un élément non ROOT.");
    GTree* lNode = m_node->m_next;
    int lCount = 0;
    while(lNode) {
        lCount++;
        lNode = lNode->m_next;
    }
    return lCount;
}
//===============================================
GString GTree::getValue() const {
    if(!m_node) return "";
    return m_node->m_value;
}
//===============================================
GString GTree::toPrint() const {
    return toNode();
}
//===============================================
GString GTree::toNode(int _index) const {
    if(!m_node) return "";
    GString lData;
    int lCount = countChild();
    for(int i = 0; i < lCount; i++) {
        GTree lNode = getChild(i);
        for(int i = 0; i < _index; i++) {
            lData += "    ";
        }
        lData += "|---";
        lData += sformat("%s\n", lNode.getValue().c_str());
        lData += lNode.toNode(_index + 1);
    }
    return lData;
}
//===============================================
GString GTree::toString() const {
    if(!m_node) return "";
    GString lData;
    int lCount = countChild();
    for(int i = 0; i < lCount; i++) {
        GTree lNode = getChild(i);
        lData += sformat("%X;%X;%s\n", m_node, lNode.m_node, lNode.getValue().c_str());
        lData += lNode.toString();
    }
    return lData;
}
//===============================================
GTree& GTree::operator=(const GTree& _tree) {
    m_root = 0;
    m_parent = _tree.m_parent;
    m_node = _tree.m_node;
    m_next = _tree.m_next;
    m_type = _tree.m_type;
    return *this;
}
//===============================================
// GTree::GNode
//===============================================
GTree::GNode::GNode() {
    m_root = 0;
    m_node = 0;
    m_next = 0;
    m_type = Type::NODE_TYPE_UNKNOWN;
}
//===============================================
GTree::GNode::GNode(GNode* _node) {
    m_root = 0;
    m_node = _node;
    m_next = 0;
    m_type = _node->m_type;
}
//===============================================
GTree::GNode::GNode(const GNode& _node) {
    *this = _node;
}
//===============================================
GTree::GNode::~GNode() {
    clear();
}
//===============================================
void GTree::GNode::clear() {
    if(m_root) {
        GNode* lNode = m_root;
        while(lNode) {
            GNode* lPrev = lNode;
            lNode = lNode->m_next;
            delete lNode;
        }
    }
}
//===============================================
void GTree::GNode::createNode() {
    m_root = new GTree::GNode;
    m_root->m_type = Type::NODE_TYPE_ROOT;
    m_node = m_root;
}
//===============================================
void GTree::GNode::loadNode(const GString& _data) {
    if(_data.isEmpty()) return;
    createNode();
    int lCount = _data.count("\n");
    for(int i = 0; i < lCount; i++) {
        GString lData = _data.extract("\n", i);
        GTree::GNode lNode = appendChild();
        lNode.setParent(lData.extract(";", 0));
        lNode.setChild(lData.extract(";", 1));
        lNode.setValue(lData.extract(";", 2));
    }
}
//===============================================
void GTree::GNode::setParent(const GString& _parent) {
    if(!m_node) return;
    m_node->m_parent = _parent;
}
//===============================================
void GTree::GNode::setChild(const GString& _child) {
    if(!m_node) return;
    m_node->m_child = _child;
}
//===============================================
void GTree::GNode::setValue(const GString& _value) {
    if(!m_node) return;
    m_node->m_value = _value;
}
//===============================================
GTree::GNode GTree::GNode::appendChild() {
    if(!m_node) return GTree::GNode();
    GTree::GNode* lNode = new GTree::GNode;
    lNode->m_type = Type::NODE_TYPE_ELEMENT;
    GTree::GNode* lNode2 = m_node;
    while(lNode2->m_next) {
        lNode2 = lNode2->m_next;
    }
    lNode2->m_next = lNode;
    return GTree::GNode(lNode);
}
//===============================================
int GTree::GNode::countNode(const GString& _parent) const {
    if(!m_node) return 0;
    if(m_node->m_type != Type::NODE_TYPE_ROOT) eThrow("Impossible de compter le nombre d'éléments à partir d'un élément non ROOT.");
    GTree::GNode* lNode = m_node->m_next;
    int lCount = 0;
    while(lNode) {
        if(lNode->m_type == Type::NODE_TYPE_ELEMENT) {
            if(lNode->m_parent == _parent) lCount++;
        }
        lNode = lNode->m_next;
    }
    return lCount;
}
//===============================================
GString GTree::GNode::getParent() const {
    if(!m_node) return "";
    return m_node->m_parent;
}
//===============================================
GString GTree::GNode::getChild() const {
    if(!m_node) return "";
    return m_node->m_child;
}
//===============================================
GString GTree::GNode::getValue() const {
    if(!m_node) return "";
    return m_node->m_value;
}
//===============================================
GTree::GNode GTree::GNode::getFirst() const {
    if(!m_node) return GTree::GNode();
    if(m_node->m_type != Type::NODE_TYPE_ROOT) eThrow("Impossible de récupérer le premier élément à partir d'un élément non ROOT.");
    return GTree::GNode(m_node->m_next);
}
//===============================================
GTree::GNode GTree::GNode::getNode(const GString& _parent, int _index) const {
    if(!m_node) return GTree::GNode();
    if(m_node->m_type != Type::NODE_TYPE_ROOT) eThrow("Impossible de compter le nombre d'éléments à partir d'un élément non ROOT.");
    GTree::GNode* lNode = m_node->m_next;
    int lCount = 0;
    while(lNode) {
        if(lNode->m_type == Type::NODE_TYPE_ELEMENT) {
            if(lNode->m_parent == _parent) {
                if(lCount == _index) break;
                lCount++;
            }
        }
        lNode = lNode->m_next;
    }
    return GTree::GNode(lNode);
}
//===============================================
GString GTree::GNode::toString() const {
    if(!m_node) return "";
    if(m_node->m_type != Type::NODE_TYPE_ROOT) eThrow("Impossible de récupérer la chaîne à partir d'un élément non ROOT.");
    GTree::GNode* lNode = m_node->m_next;
    GString lData;
    while(lNode) {
        lData += sformat("=>%s;%s;%s\n", lNode->m_parent.c_str(), lNode->m_child.c_str(), lNode->m_value.c_str());
        lNode = lNode->m_next;
    }
    return lData;
}
//===============================================
GTree::GNode& GTree::GNode::operator=(const GNode& _node) {
    m_root = 0;
    m_node = _node.m_node;
    m_next = _node.m_next;
    m_parent = _node.m_parent;
    m_child = _node.m_child;
    m_value = _node.m_value;
    m_type = _node.m_type;
    return *this;
}
//===============================================
