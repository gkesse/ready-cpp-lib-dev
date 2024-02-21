//===============================================
#include "GString.h"
//===============================================
GString* GString::m_instance = 0;
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
GString::GString(const std::vector<char>& _data) {
    m_data = 0;
    create(_data.data(), _data.size());
}
//===============================================
GString::GString(const std::vector<uchar>& _data) {
    m_data = 0;
    create((char*)_data.data(), _data.size());
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
GString* GString::Instance() {
    if(m_instance == 0) {
        m_instance = new GString;
    }
    return m_instance;
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
bool GString::createPath(mode_t _mode) const {
    if(isEmpty()) return false;
    int lCount = count("/") + 1;
    GString lPath;
    bool isPath = false;
    if(m_data[0] == '/') lPath = "/";
    for(int i = 0; i < lCount; i++) {
        GString lPathI = extract("/", i);
        if(lPathI.isEmpty()) continue;
        if(isPath) lPath += "/";
        lPath += lPathI;
        isPath = true;
        struct stat lStat;
        if(!stat(lPath.c_str(), &lStat) && (lStat.st_mode & S_IFDIR)) continue;
        if(mkdir(lPath.c_str(), _mode) == -1) return false;
    }
    return true;
}
//===============================================
char GString::first() const {
    if(isEmpty()) return 0;
    return m_data[0];
}
//===============================================
char GString::back() const {
    if(isEmpty()) return 0;
    std::string lData(m_data, m_size);
    return lData.back();
}
//===============================================
void GString::pop() {
    if(isEmpty()) return;
    std::string lData(m_data, m_size);
    lData.pop_back();
    *this = lData;
}
//===============================================
int GString::indexOf(const GString& _sep, int _pos) const {
    if(isEmpty()) return -1;
    std::string lData(m_data, m_size);
    int lPos = lData.find(_sep.c_str(), _pos);
    return lPos;
}
//===============================================
int GString::count(const GString& _sep) const {
    if(isEmpty()) return 0;
    int lCount = 0;
    int lPos = 0;
    while(1) {
        int lPos2 = indexOf(_sep, lPos);
        if(lPos2 == -1) break;
        lCount++;
        lPos = lPos2 + _sep.size();
    }
    return lCount + 1;
}
//===============================================
int GString::countSep(const GString& _sep) const {
    GString lData = *this;
    char* lToken = strtok(lData.m_data , _sep.c_str());
    int lCount = 0;

    while(lToken) {
        lCount++;
        lToken = strtok(0, _sep.c_str());
    }

    return lCount;
}
//===============================================
bool GString::startsWith(const GString& _data) const {
    if(isEmpty()) return false;
    if(size() < _data.size()) return false;
    return (substr(0, _data.size()) == _data);
}
//===============================================
bool GString::endsWith(const GString& _data) const {
    if(isEmpty()) return false;
    if(size() < _data.size()) return false;
    return (substr(size() - _data.size(), _data.size()) == _data);
}
//===============================================
bool GString::toBool() const {
    if(isEmpty()) return false;
    return (*this == "1");
}
//===============================================
char GString::toChar() const {
    if(isEmpty()) return 0;
    return m_data[0];
}
//===============================================
int GString::toInt() const {
    if(isEmpty()) return 0;
    int lData = 0;
    try {
        lData = std::stoi(m_data);
    }
    catch(const std::exception& e) {
        lData = 0;
    }
    return lData;
}
//===============================================
double GString::toDouble() const {
    if(isEmpty()) return 0;
    double lData = 0;
    try {
        lData = std::stod(m_data);
    }
    catch(const std::exception& e) {
        lData = 0;
    }
    return lData;
}
//===============================================
GString GString::toUpper() const {
    std::string lData(m_data, m_size);
    std::transform(lData.begin(), lData.end(), lData.begin(), ::toupper);
    return lData;
}
//===============================================
GString GString::toLower() const {
    std::string lData(m_data, m_size);
    std::transform(lData.begin(), lData.end(), lData.begin(), ::tolower);
    return lData;
}
//===============================================
GString GString::substr(int _pos, int _size) const {
    if(isEmpty()) return "";
    std::string lData(m_data, m_size);
    return lData.substr(_pos, _size);
}
//===============================================
GString GString::extract(const GString& _sep, int _index) const {
    int lPos = 0;
    int lCount = 0;
    while(1) {
        int lPos2 = indexOf(_sep, lPos);
        if(lPos2 == -1) {
            int lSize = size() - lPos;
            return substr(lPos, lSize);
        }
        if(lCount == _index) {
            int lSize = lPos2 - lPos;
            return substr(lPos, lSize);
        }
        lPos = lPos2 + _sep.size();
        lCount++;
    }
    return "";
}
//===============================================
GString GString::extract(const GString& _sep1, const GString& _sep2, int _pos) const {
    int lPos = indexOf(_sep1, _pos);
    if(lPos == -1) {
        return "";
    }
    lPos += _sep1.size();
    int lPos2 = indexOf(_sep2, lPos);
    if(lPos2 == -1) {
        return "";
    }
    int lSize = lPos2 - lPos;
    return substr(lPos, lSize);
}
//===============================================
GString GString::extractSep(const GString& _sep, int _index) const {
    GString lData = *this;
    char* lToken = strtok(lData.m_data , _sep.c_str());
    int lCount = 0;

    while(lToken) {
        if(lCount == _index) return lToken;
        lToken = strtok(0, _sep.c_str());
        lCount++;
    }

    return "";
}
//===============================================
GString GString::extractEnd(const GString& _sep, int _index) const {
    int lPos = 0;
    int lCount = 0;
    while(1) {
        int lPos2 = indexOf(_sep, lPos);
        if(lPos2 == -1) {
            int lSize = size() - lPos;
            return substr(lPos, lSize);
        }
        if(lCount == _index) {
            lPos = lPos2 + _sep.size();
            return substr(lPos);
        }
        lPos = lPos2 + _sep.size();
        lCount++;
    }
    return "";
}
//===============================================
GString GString::toBase64() const {
    return Base64::encode((uchar*)m_data, m_size);
}
//===============================================
GString GString::fromBase64() const {
    return Base64::decode(m_data);
}
//===============================================
GString GString::trim() const {
    return ltrim().rtrim();
}
//===============================================
GString GString::ltrim() const {
    if(isEmpty()) return "";
    std::string lData(m_data, m_size);
    lData.erase(lData.begin(), std::find_if(lData.begin(), lData.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return lData;
}
//===============================================
GString GString::rtrim() const {
    if(isEmpty()) return "";
    std::string lData(m_data, m_size);
    lData.erase(std::find_if(lData.rbegin(), lData.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), lData.end());
    return lData;
}
//===============================================
GString GString::getFormat(const char* _format, ...) const {
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lData = new char[lSize + 1];
    vsnprintf(lData, lSize + 1, _format, lArgs);
    va_end(lArgs);
    GString lString(lData, lSize);
    delete[] lData;
    return lString;
}
//===============================================
GString GString::getFilepath() const {
    if(isEmpty()) return "";
    std::string lPath(m_data, m_size);
    size_t lFound = lPath.find_last_of("/\\");
    if(lFound == std::string::npos) return *this;
    return lPath.substr(0, lFound);
}
//===============================================
GString GString::getFilename() const {
    if(isEmpty()) return "";
    std::string lPath(m_data, m_size);
    size_t lFound = lPath.find_last_of("/\\");
    if(lFound == std::string::npos) return *this;
    return lPath.substr(lFound + 1);
}
//===============================================
GString GString::getBasename() const {
    if(isEmpty()) return "";
    GString lFilename = getFilename();
    std::string lPath(lFilename.m_data, lFilename.m_size);
    size_t lFound = lPath.find_last_of(".");
    if(lFound == std::string::npos) return *this;
    return lPath.substr(0, lFound);
}
//===============================================
GString GString::getExtension() const {
    if(isEmpty()) return "";
    GString lFilename = getFilename();
    std::string lPath(lFilename.m_data, lFilename.m_size);
    size_t lFound = lPath.find_last_of(".");
    if(lFound == std::string::npos) return "";
    return lPath.substr(lFound + 1);
}
//===============================================
GString GString::replaceAll(const GString& _from, const GString& _to) const {
    if(isEmpty()) return "";
    std::string lData(m_data, m_size);
    size_t start_pos = 0;
    while((start_pos = lData.find(_from.c_str(), start_pos)) != std::string::npos) {
        lData.replace(start_pos, _from.size(), _to.c_str());
        start_pos += _to.size();
    }
    return lData;
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
GString& GString::operator=(const std::vector<char>& _data) {
    create(_data.data(), _data.size());
    return *this;
}
//===============================================
GString& GString::operator=(const std::vector<uchar>& _data) {
    create((char*)_data.data(), _data.size());
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
GString& GString::operator+=(const std::vector<char>& _data) {
    *this += GString(_data);
    return *this;
}
//===============================================
GString& GString::operator+=(const std::vector<uchar>& _data) {
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
bool GString::operator==(const std::vector<char>& _data) const {
    return (*this == GString(_data));
}
//===============================================
bool GString::operator==(const std::vector<uchar>& _data) const {
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
bool GString::operator!=(const std::vector<char>& _data) const {
    return !(*this == _data);
}
//===============================================
bool GString::operator!=(const std::vector<uchar>& _data) const {
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
bool GString::operator<(const std::vector<char>& _data) const {
    return (*this < GString(_data));
}
//===============================================
bool GString::operator<(const std::vector<uchar>& _data) const {
    return (*this < GString(_data));
}
//===============================================
bool GString::operator<(const std::string& _data) const {
    return (*this < GString(_data));
}
//===============================================
bool GString::operator<(const GString& _data) const {
    if(isEmpty()) return true;
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
bool GString::operator<=(const std::vector<char>& _data) const {
    return (*this <= GString(_data));
}
//===============================================
bool GString::operator<=(const std::vector<uchar>& _data) const {
    return (*this <= GString(_data));
}
//===============================================
bool GString::operator<=(const std::string& _data) const {
    return (*this <= GString(_data));
}
//===============================================
bool GString::operator<=(const GString& _data) const {
    if(isEmpty()) return true;
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
bool GString::operator>(const std::vector<char>& _data) const {
    return (*this > _data);
}
//===============================================
bool GString::operator>(const std::vector<uchar>& _data) const {
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
bool GString::operator>=(const std::vector<char>& _data) const {
    return (*this >= _data);
}
//===============================================
bool GString::operator>=(const std::vector<uchar>& _data) const {
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
GString operator+(const GString& _data1, const std::vector<char>& _data2) {
    GString lData(_data1);
    lData += _data2;
    return lData;
}
//===============================================
GString operator+(const GString& _data1, const std::vector<uchar>& _data2) {
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
