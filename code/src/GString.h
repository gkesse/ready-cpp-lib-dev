//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
#include "GConstant.h"
//===============================================
#define GSTRING         GString::Instance()
#define sformat(...)    GSTRING->getFormat(__VA_ARGS__)
//===============================================
class GString {
public:
    GString();
    GString(bool _data);
    GString(char _data);
    GString(int _data);
    GString(long _data);
    GString(double _data);
    GString(char* _data, int _size);
    GString(uchar* _data, int _size);
    GString(const char* _data);
    GString(const std::string& _data);
    GString(const std::vector<char>& _data);
    GString(const std::vector<uchar>& _data);
    GString(const GString& _data);
    ~GString();

    static GString* Instance();
    void clear();
    void create(const char* _data, int _size);
    const char* c_str() const;
    char*& c_str();
    const uchar* uc_str() const;
    uchar*& uc_str();
    int size() const;
    bool isEmpty() const;
    bool createPath(mode_t _mode) const;
    char first() const;
    char back() const;
    void pop();
    int indexOf(const GString& _sep, int _pos = 0) const;
    int count(const GString& _sep) const;
    int countSep(const GString& _sep) const;
    bool startsWith(const GString& _data) const;
    bool endsWith(const GString& _data) const;
    bool toBool() const;
    char toChar() const;
    int toInt() const;
    double toDouble() const;
    GString toUpper() const;
    GString toLower() const;
    GString substr(int _pos, int _size = -1) const;
    GString extract(const GString& _sep, int _index = 0) const;
    GString extract(const GString& _sep1, const GString& _sep2, int _pos = 0) const;
    GString extractSep(const GString& _sep, int _index = 0) const;
    GString extractEnd(const GString& _sep, int _index = 0) const;
    GString toBase64() const;
    GString fromBase64() const;
    GString trim() const;
    GString ltrim() const;
    GString rtrim() const;
    GString getFormat(const char* _format, ...) const;
    GString getFilepath() const;
    GString getFilename() const;
    GString getBasename() const;
    GString getExtension() const;
    GString getMimeType() const;
    GString replaceAll(const GString& _from, const GString& _to) const;
    void print() const;

    GString& operator=(bool _data);
    GString& operator=(char _data);
    GString& operator=(int _data);
    GString& operator=(long _data);
    GString& operator=(double _data);
    GString& operator=(const char* _data);
    GString& operator=(const std::string& _data);
    GString& operator=(const std::vector<char>& _data);
    GString& operator=(const std::vector<uchar>& _data);
    GString& operator=(const GString& _data);

    GString& operator+=(bool _data);
    GString& operator+=(char _data);
    GString& operator+=(int _data);
    GString& operator+=(long _data);
    GString& operator+=(double _data);
    GString& operator+=(const char* _data);
    GString& operator+=(const std::string& _data);
    GString& operator+=(const std::vector<char>& _data);
    GString& operator+=(const std::vector<uchar>& _data);
    GString& operator+=(const GString& _data);

    bool operator==(bool _data) const;
    bool operator==(char _data) const;
    bool operator==(int _data) const;
    bool operator==(long _data) const;
    bool operator==(double _data) const;
    bool operator==(const char* _data) const;
    bool operator==(const std::string& _data) const;
    bool operator==(const std::vector<char>& _data) const;
    bool operator==(const std::vector<uchar>& _data) const;
    bool operator==(const GString& _data) const;

    bool operator!=(bool _data) const;
    bool operator!=(char _data) const;
    bool operator!=(int _data) const;
    bool operator!=(long _data) const;
    bool operator!=(double _data) const;
    bool operator!=(const char* _data) const;
    bool operator!=(const std::string& _data) const;
    bool operator!=(const std::vector<char>& _data) const;
    bool operator!=(const std::vector<uchar>& _data) const;
    bool operator!=(const GString& _data) const;

    bool operator<(bool _data) const;
    bool operator<(char _data) const;
    bool operator<(int _data) const;
    bool operator<(long _data) const;
    bool operator<(double _data) const;
    bool operator<(const char* _data) const;
    bool operator<(const std::string& _data) const;
    bool operator<(const std::vector<char>& _data) const;
    bool operator<(const std::vector<uchar>& _data) const;
    bool operator<(const GString& _data) const;

    bool operator<=(bool _data) const;
    bool operator<=(char _data) const;
    bool operator<=(int _data) const;
    bool operator<=(long _data) const;
    bool operator<=(double _data) const;
    bool operator<=(const char* _data) const;
    bool operator<=(const std::string& _data) const;
    bool operator<=(const std::vector<char>& _data) const;
    bool operator<=(const std::vector<uchar>& _data) const;
    bool operator<=(const GString& _data) const;

    bool operator>(bool _data) const;
    bool operator>(char _data) const;
    bool operator>(int _data) const;
    bool operator>(long _data) const;
    bool operator>(double _data) const;
    bool operator>(const char* _data) const;
    bool operator>(const std::string& _data) const;
    bool operator>(const std::vector<char>& _data) const;
    bool operator>(const std::vector<uchar>& _data) const;
    bool operator>(const GString& _data) const;

    bool operator>=(bool _data) const;
    bool operator>=(char _data) const;
    bool operator>=(int _data) const;
    bool operator>=(long _data) const;
    bool operator>=(double _data) const;
    bool operator>=(const char* _data) const;
    bool operator>=(const std::string& _data) const;
    bool operator>=(const std::vector<char>& _data) const;
    bool operator>=(const std::vector<uchar>& _data) const;
    bool operator>=(const GString& _data) const;

    char& operator[](int _index);
    const char& operator[](int _index) const;

    friend GString operator+(const GString& _data1,  bool _data2);
    friend GString operator+(const GString& _data1, char _data2);
    friend GString operator+(const GString& _data1, int _data2);
    friend GString operator+(const GString& _data1, long _data2);
    friend GString operator+(const GString& _data1, double _data2);
    friend GString operator+(const GString& _data1, const char* _data2);
    friend GString operator+(const GString& _data1, const std::string& _data2);
    friend GString operator+(const GString& _data1, const std::vector<char>& _data2);
    friend GString operator+(const GString& _data1, const std::vector<uchar>& _data2);
    friend GString operator+(const GString& _data1, const GString& _data2);

    friend std::ostream& operator<<(std::ostream& _os, const GString& _data);

private:
    static GString* m_instance;

protected:
    int m_size;
    char* m_data;
};
//===============================================
#endif
//===============================================
