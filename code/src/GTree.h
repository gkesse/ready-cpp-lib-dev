//===============================================
#ifndef _GTree_
#define _GTree_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GTree {
public:
    enum class Type {
        TREE_TYPE_UNKNOWN
        , TREE_TYPE_ROOT
        , TREE_TYPE_ELEMENT
    };

public:
    class GNode {
    public:
        enum class Type {
            NODE_TYPE_UNKNOWN
            , NODE_TYPE_ROOT
            , NODE_TYPE_ELEMENT
        };

    public:
        GNode();
        GNode(GNode* _node);
        GNode(const GNode& _node);
        ~GNode();
        void clear();
        void createNode();
        void loadNode(const GString& _data);
        void setParent(const GString& _parent);
        void setChild(const GString& _child);
        void setValue(const GString& _value);
        GNode appendChild();
        int countNode(const GString& _parent) const;
        GString getParent() const;
        GString getChild() const;
        GString getValue() const;
        GNode getFirst() const;
        GNode getNode(const GString& _parent, int _index) const;
        GString toString() const;
        GNode& operator=(const GNode& _node);

    private:
        GNode* m_root;
        GNode* m_node;
        GNode* m_next;
        GString m_parent;
        GString m_child;
        GString m_value;
        Type m_type;
    };

public:
    GTree();
    GTree(GTree* _node);
    GTree(const GTree& _tree);
    virtual ~GTree();
    void clear();
    void createTree();
    void loadTree(const GString& _tree);
    void loadNode(const GTree::GNode& _root, const GString& _parent);
    GTree appendChild(const GString& _value);
    GTree getChild(int _index) const;
    void setValue(const GString& _value);
    int countChild() const;
    int countNode(const GString& _data, const GString& _node) const;
    int size() const;
    GString getValue() const;
    GString toPrint() const;
    GString toNode(int _index = 0) const;
    GString toString() const;
    GTree& operator=(const GTree& _tree);

private:
    GTree* m_root;
    GTree* m_parent;
    GTree* m_node;
    GTree* m_next;
    GString m_value;
    Type m_type;
};
//===============================================
#endif
//===============================================
