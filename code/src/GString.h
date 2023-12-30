//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
//===============================================
class GString {
public:
    GString();
    GString(const char* _data);
    GString(const GString& _data);
    ~GString();
    void clear();
    void create(const char* _data, int _size);
    const char* c_str() const;
    char* data();
    int size() const;
    bool isEmpty() const;
    void print() const;

private:
    int m_size;
    char* m_data;
};
//===============================================
#endif
//===============================================
