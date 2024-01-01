//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
//===============================================
class GString {
public:
    GString();
    GString(bool _data);
    GString(char _data);
    GString(int _data);
    GString(double _data);
    GString(char* _data, int _size);
    GString(const char* _data);
    GString(const std::string& _data);
    GString(const GString& _data);
    ~GString();

    void clear();
    void create(const char* _data, int _size);
    const char* c_str() const;
    char*& data();
    int size() const;
    bool isEmpty() const;
    void print() const;

    GString& operator=(bool _data);
    GString& operator=(char _data);
    GString& operator=(int _data);
    GString& operator=(double _data);
    GString& operator=(const char* _data);
    GString& operator=(const std::string& _data);
    GString& operator=(const GString& _data);

    GString& operator+=(bool _data);
    GString& operator+=(char _data);
    GString& operator+=(int _data);
    GString& operator+=(double _data);
    GString& operator+=(const char* _data);
    GString& operator+=(const std::string& _data);
    GString& operator+=(const GString& _data);

    bool operator==(bool _data) const;
    bool operator==(char _data) const;
    bool operator==(int _data) const;
    bool operator==(double _data) const;
    bool operator==(const char* _data) const;
    bool operator==(const std::string& _data) const;
    bool operator==(const GString& _data) const;

    bool operator!=(bool _data) const;
    bool operator!=(char _data) const;
    bool operator!=(int _data) const;
    bool operator!=(double _data) const;
    bool operator!=(const char* _data) const;
    bool operator!=(const std::string& _data) const;
    bool operator!=(const GString& _data) const;

    bool operator<(bool _data) const;
    bool operator<(char _data) const;
    bool operator<(int _data) const;
    bool operator<(double _data) const;
    bool operator<(const char* _data) const;
    bool operator<(const std::string& _data) const;
    bool operator<(const GString& _data) const;

    bool operator<=(bool _data) const;
    bool operator<=(char _data) const;
    bool operator<=(int _data) const;
    bool operator<=(double _data) const;
    bool operator<=(const char* _data) const;
    bool operator<=(const std::string& _data) const;
    bool operator<=(const GString& _data) const;

    bool operator>(bool _data) const;
    bool operator>(char _data) const;
    bool operator>(int _data) const;
    bool operator>(double _data) const;
    bool operator>(const char* _data) const;
    bool operator>(const std::string& _data) const;
    bool operator>(const GString& _data) const;

    bool operator>=(bool _data) const;
    bool operator>=(char _data) const;
    bool operator>=(int _data) const;
    bool operator>=(double _data) const;
    bool operator>=(const char* _data) const;
    bool operator>=(const std::string& _data) const;
    bool operator>=(const GString& _data) const;

    char& operator[](int _index);
    const char& operator[](int _index) const;

    friend GString operator+(const GString& _data1,  bool _data2);
    friend GString operator+(const GString& _data1, char _data2);
    friend GString operator+(const GString& _data1, int _data2);
    friend GString operator+(const GString& _data1, double _data2);
    friend GString operator+(const GString& _data1, const char* _data2);
    friend GString operator+(const GString& _data1, const std::string& _data2);
    friend GString operator+(const GString& _data1, const GString& _data2);

    friend std::ostream& operator<<(std::ostream& _os, const GString& _data);

private:
    int m_size;
    char* m_data;
};
//===============================================
#endif
//===============================================
