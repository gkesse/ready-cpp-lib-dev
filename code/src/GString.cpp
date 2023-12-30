//===============================================
#include "GString.h"
//===============================================
GString::GString() {
    m_data = 0;
    create(0, 0);
}
//===============================================
GString::GString(const char* _data) {
    m_data = 0;
    create(_data, strlen(_data));
}
//===============================================
GString::GString(const GString& _data) {
    m_data = 0;
    create(_data.m_data, _data.m_size);
}
//===============================================
GString::~GString() {
    clear();
}
//===============================================
void GString::clear() {
    if(m_data) delete[] m_data;
    m_data = 0;
    m_size = 0;
}
//===============================================
void GString::create(const char* _data, int _size) {
    clear();
    if(_size < 0) _size = 0;
    m_data = new char[_size + 1];
    m_data[_size] = '\0';
    memcpy(m_data, _data, _size);
    m_size = _size;
}
//===============================================
const char* GString::c_str() const {
    return m_data;
}
//===============================================
char* GString::data() {
    return m_data;
}
//===============================================
int GString::size() const {
    return m_size;
}
//===============================================
bool GString::isEmpty() const {
    return (m_size == 0 || m_data == 0);
}
//===============================================
void GString::print() const {
    printf("%s\n", m_data);
}
//===============================================
