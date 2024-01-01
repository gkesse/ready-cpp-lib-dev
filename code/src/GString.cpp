//===============================================
#include "GString.h"
//===============================================
GString::GString() {
    m_data = 0;
    create(0, 0);
}
//===============================================
GString::GString(bool _data) {
    m_data = 0;
    char lChar = (_data ? '1' : '0');
    create(&lChar, 1);
}
//===============================================
GString::GString(char _data) {
    m_data = 0;
    create(&_data, 1);
}
//===============================================
GString::GString(int _data) {
    m_size = snprintf(0, 0, "%d", _data);
    m_data = new char[m_size + 1];
    snprintf(m_data, m_size + 1, "%d", _data);
}
//===============================================
GString::GString(double _data) {
    m_size = snprintf(0, 0, "%f", _data);
    m_data = new char[m_size + 1];
    snprintf(m_data, m_size + 1, "%f", _data);
}
//===============================================
GString::GString(char* _data, int _size) {
    m_data = 0;
    create(_data, _size);
}
//===============================================
GString::GString(const char* _data) {
    m_data = 0;
    create(_data, strlen(_data));
}
//===============================================
GString::GString(const std::string& _data) {
    m_data = 0;
    create(_data.data(), _data.size());
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
char*& GString::data() {
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
GString& GString::operator=(bool _data) {
    char lChar = (_data ? '1' : '0');
    create(&lChar, 1);
    return *this;
}
//===============================================
GString& GString::operator=(char _data) {
    create(&_data, 1);
    return *this;
}
//===============================================
GString& GString::operator=(const char* _data) {
    create(_data, strlen(_data));
    return *this;
}
//===============================================
GString& GString::operator=(int _data) {
    clear();
    m_size = snprintf(0, 0, "%d", _data);
    m_data = new char[m_size + 1];
    snprintf(m_data, m_size + 1, "%d", _data);
    return *this;
}
//===============================================
GString& GString::operator=(double _data) {
    clear();
    m_size = snprintf(0, 0, "%f", _data);
    m_data = new char[m_size + 1];
    snprintf(m_data, m_size + 1, "%f", _data);
    return *this;
}
//===============================================
GString& GString::operator=(const std::string& _data) {
    create(_data.data(), _data.size());
    return *this;
}
//===============================================
GString& GString::operator=(const GString& _data) {
    create(_data.m_data, _data.m_size);
    return *this;
}
//===============================================
GString& GString::operator+=(bool _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(char _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(int _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(double _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(const char* _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(const std::string& _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(const GString& _data) {
    GString lData = *this;
    m_size = lData.m_size + _data.m_size;
    m_data = new char[m_size + 1];
    m_data[m_size] = '\0';
    memcpy(&m_data[0], lData.m_data, lData.m_size);
    memcpy(&m_data[lData.m_size], _data.m_data, _data.m_size);
    return *this;
}
//===============================================
bool GString::operator==(bool _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(char _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(int _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(double _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(const char* _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(const std::string& _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(const GString& _data) const {
    if(m_size != _data.m_size) return false;
    return (memcmp(m_data, _data.m_data, m_size) == 0);
}
//===============================================
bool GString::operator!=(bool _data) const {
    return !(*this == _data);
}
//===============================================
bool GString::operator!=(char _data) const {
    return !(*this == _data);
}
//===============================================
bool GString::operator!=(int _data) const {
    return !(*this == _data);
}
//===============================================
bool GString::operator!=(const char* _data) const {
    return !(*this == _data);
}
//===============================================
bool GString::operator!=(const std::string& _data) const {
    return !(*this == _data);
}
//===============================================
bool GString::operator!=(const GString& _data) const {
    return !(*this == _data);
}
//===============================================
bool GString::operator<(bool _data) const {
    return (*this < GString(_data));
}
//===============================================
bool GString::operator<(char _data) const {
    return (*this < GString(_data));
}
//===============================================
bool GString::operator<(int _data) const {
    return (*this < GString(_data));
}
//===============================================
bool GString::operator<(double _data) const {
    return (*this < GString(_data));
}
//===============================================
bool GString::operator<(const char* _data) const {
    return (*this < GString(_data));
}
//===============================================
bool GString::operator<(const std::string& _data) const {
    return (*this < GString(_data));
}
//===============================================
bool GString::operator<(const GString& _data) const {
    if(m_size < _data.m_size) {
        return (memcmp(m_data, _data.m_data, m_size) <= 0);
    }
    else if(m_size > _data.m_size) {
        return (memcmp(m_data, _data.m_data, _data.m_size) >= 0);
    }
    return (memcmp(m_data, _data.m_data, m_size) < 0);
}
//===============================================
bool GString::operator<=(bool _data) const {
    return (*this <= GString(_data));
}
//===============================================
bool GString::operator<=(char _data) const {
    return (*this <= GString(_data));
}
//===============================================
bool GString::operator<=(int _data) const {
    return (*this <= GString(_data));
}
//===============================================
bool GString::operator<=(double _data) const {
    return (*this <= GString(_data));
}
//===============================================
bool GString::operator<=(const char* _data) const {
    return (*this <= GString(_data));
}
//===============================================
bool GString::operator<=(const std::string& _data) const {
    return (*this <= GString(_data));
}
//===============================================
bool GString::operator<=(const GString& _data) const {
    if(m_size < _data.m_size) {
        return (memcmp(m_data, _data.m_data, m_size) <= 0);
    }
    else if(m_size > _data.m_size) {
        return (memcmp(m_data, _data.m_data, _data.m_size) >= 0);
    }
    return (memcmp(m_data, _data.m_data, m_size) <= 0);
}
//===============================================
bool GString::operator>(bool _data) const {
    return (*this > _data);
}
//===============================================
bool GString::operator>(char _data) const {
    return (*this > _data);
}
//===============================================
bool GString::operator>(int _data) const {
    return (*this > _data);
}
//===============================================
bool GString::operator>(double _data) const {
    return (*this > _data);
}
//===============================================
bool GString::operator>(const char* _data) const {
    return (*this > _data);
}
//===============================================
bool GString::operator>(const std::string& _data) const {
    return (*this > _data);
}
//===============================================
bool GString::operator>(const GString& _data) const {
    if(m_size < _data.m_size) {
        return (memcmp(m_data, _data.m_data, m_size) >= 0);
    }
    else if(m_size > _data.m_size) {
        return (memcmp(m_data, _data.m_data, _data.m_size) <= 0);
    }
    return (memcmp(m_data, _data.m_data, m_size) > 0);
}
//===============================================
bool GString::operator>=(bool _data) const {
    return (*this >= _data);
}
//===============================================
bool GString::operator>=(char _data) const {
    return (*this >= _data);
}
//===============================================
bool GString::operator>=(int _data) const {
    return (*this >= _data);
}
//===============================================
bool GString::operator>=(double _data) const {
    return (*this >= _data);
}
//===============================================
bool GString::operator>=(const char* _data) const {
    return (*this >= _data);
}
//===============================================
bool GString::operator>=(const std::string& _data) const {
    return (*this >= _data);
}
//===============================================
bool GString::operator>=(const GString& _data) const {
    if(m_size < _data.m_size) {
        return (memcmp(m_data, _data.m_data, m_size) >= 0);
    }
    else if(m_size > _data.m_size) {
        return (memcmp(m_data, _data.m_data, _data.m_size) <= 0);
    }
    return (memcmp(m_data, _data.m_data, m_size) >= 0);
}
//===============================================
char& GString::operator[](int _index) {
    return m_data[_index];
}
//===============================================
const char& GString::operator[](int _index) const {
    return m_data[_index];
}
//===============================================
GString operator+(const GString& _data1, bool _data2) {
    GString lData(_data1);
    lData += _data2;
    return lData;
}
//===============================================
GString operator+(const GString& _data1, char _data2) {
    GString lData(_data1);
    lData += _data2;
    return lData;
}
//===============================================
GString operator+(const GString& _data1, int _data2) {
    GString lData(_data1);
    lData += _data2;
    return lData;
}
//===============================================
GString operator+(const GString& _data1, double _data2) {
    GString lData(_data1);
    lData += _data2;
    return lData;
}
//===============================================
GString operator+(const GString& _data1, const char* _data2) {
    GString lData(_data1);
    lData += _data2;
    return lData;
}
//===============================================
GString operator+(const GString& _data1, const std::string& _data2) {
    GString lData(_data1);
    lData += _data2;
    return lData;
}
//===============================================
GString operator+(const GString& _data1, const GString& _data2) {
    GString lData(_data1);
    lData += _data2;
    return lData;
}
//===============================================
std::ostream& operator<<(std::ostream& _os, const GString& _data) {
    _os << _data.m_data;
    return _os;
}
//===============================================
