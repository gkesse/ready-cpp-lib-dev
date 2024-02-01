//===============================================
#ifndef _GFile_
#define _GFile_
//===============================================
#include "GObject.h"
//===============================================
class GFile {
public:
    enum class Mode {
        FILE_MODE_UNKNOWN
        , FILE_MODE_READ_TEXT
        , FILE_MODE_READ_BIN
        , FILE_MODE_WRITE_TEXT
        , FILE_MODE_WRITE_BIN
        , FILE_MODE_APPEND_TEXT
    };

public:
    GFile();
    GFile(const GString& _fullname, const Mode& _mode);
    GFile(const GFile& _file);
    ~GFile();
    void setFullname(const GString& _fullname);
    void setMode(const Mode& _mode);
    bool existFile() const;
    bool writeData(const GString& _data);
    GString readData() const;
    GString readBin() const;
    GFile& operator=(const GFile& _file);

private:
    GString m_fullname;
    Mode m_mode;
};
//==============================================
#endif
//==============================================
