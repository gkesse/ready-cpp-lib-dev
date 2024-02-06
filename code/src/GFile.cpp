//===============================================
#include "GFile.h"
//===============================================
GFile::GFile()
: GObject() {
    m_mode = Mode::FILE_MODE_UNKNOWN;
}
//===============================================
GFile::GFile(const GString& _fullname, const Mode& _mode) {
    m_fullname = _fullname;
    m_mode = _mode;
}
//===============================================
GFile::GFile(const GFile& _file) {
    *this = _file;
}
//===============================================
GFile::~GFile() {

}
//===============================================
void GFile::setFullname(const GString& _fullname) {
    m_fullname = _fullname;
}
//===============================================
void GFile::setMode(const Mode& _mode) {
    m_mode = _mode;
}
//===============================================
bool GFile::existFile() const {
    if(m_fullname == "") return false;
    std::ifstream lFile(m_fullname.c_str());
    return lFile.good();
}
//===============================================
bool GFile::writeData(const GString& _data) {
    if(m_fullname == "") return false;
    if(m_mode == Mode::FILE_MODE_WRITE_TEXT) {
        std::ofstream lFile(m_fullname.c_str());
        if(!lFile) {
            slog(eGERR, "L'ouverture du fichier a échoué."
                        "|adresse_ip=%s"
                        "|port=%d"
                        "|process=%d"
                        "|filename=%s"
                        "|mode=%d"
                        "|data=%s", m_addressIP.c_str(), m_port, m_pid, m_fullname.c_str(), m_mode, _data.c_str());
            return false;
        }
        lFile << _data.c_str();
    }
    else if(m_mode == Mode::FILE_MODE_APPEND_TEXT) {
        std::ofstream lFile(m_fullname.c_str(), std::ios::out | std::ios::app);
        if(!lFile) {
            slog(eGERR, "L'ouverture du fichier a échoué."
                        "|adresse_ip=%s"
                        "|port=%d"
                        "|process=%d"
                        "|filename=%s"
                        "|mode=%d"
                        "|data=%s", m_addressIP.c_str(), m_port, m_pid, m_fullname.c_str(), m_mode, _data.c_str());
            return false;
        }
        lFile << _data.c_str();
    }
    else if(m_mode == Mode::FILE_MODE_WRITE_BIN) {
        std::ofstream lFile(m_fullname.c_str(), std::ios::out | std::ios::binary);
        if(!lFile) {
            slog(eGERR, "L'ouverture du fichier a échoué."
                        "|adresse_ip=%s"
                        "|port=%d"
                        "|process=%d"
                        "|filename=%s"
                        "|mode=%d"
                        "|data=%s", m_addressIP.c_str(), m_port, m_pid, m_fullname.c_str(), m_mode, _data.c_str());
            return false;
        }
        lFile.write(_data.c_str(), _data.size());
    }
    else {
        slog(eGERR, "Le mode d'ouverture du fichier est inconnu."
                    "|adresse_ip=%s"
                    "|port=%d"
                    "|process=%d"
                    "|filename=%s"
                    "|mode=%d"
                    "|data=%s", m_addressIP.c_str(), m_port, m_pid, m_fullname.c_str(), m_mode, _data.c_str());
        return false;
    }
    return true;
}
//===============================================
GString GFile::readData() const {
    if(m_fullname == "") return "";
    if(m_mode == Mode::FILE_MODE_READ_TEXT) {
        std::ifstream lFile(m_fullname.c_str());
        if(!lFile) {
            slog(eGERR, "L'ouverture du fichier a échoué."
                        "|adresse_ip=%s"
                        "|port=%d"
                        "|process=%d"
                        "|filename=%s"
                        "|mode=%d", m_addressIP.c_str(), m_port, m_pid, m_fullname.c_str(), m_mode);
            return "";
        }
        std::stringstream lBuffer;
        lBuffer << lFile.rdbuf();
        return lBuffer.str();
    }
    else if(m_mode == Mode::FILE_MODE_READ_BIN) {
        std::ifstream lFile(m_fullname.c_str(), std::ios::in | std::ios::binary);
        if(!lFile) {
            slog(eGERR, "L'ouverture du fichier a échoué."
                        "|adresse_ip=%s"
                        "|port=%d"
                        "|process=%d"
                        "|filename=%s"
                        "|mode=%d", m_addressIP.c_str(), m_port, m_pid, m_fullname.c_str(), m_mode);
            return "";
        }
        std::vector<char> lData = std::vector<char>(std::istreambuf_iterator<char>(lFile), std::istreambuf_iterator<char>());
        return lData;
    }
    else {
        slog(eGERR, "Le mode d'ouverture du fichier est inconnu."
                    "|adresse_ip=%s"
                    "|port=%d"
                    "|process=%d"
                    "|filename=%s"
                    "|mode=%d", m_addressIP.c_str(), m_port, m_pid, m_fullname.c_str(), m_mode);
    }
    return "";
}
//===============================================
GFile& GFile::operator=(const GFile& _file) {
    m_fullname = _file.m_fullname;
    m_mode = _file.m_mode;
    return *this;
}
//===============================================
