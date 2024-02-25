//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GObject.h"
//===============================================
class GTest : public GObject {
public:
    GTest();
    ~GTest();
    void run(int _argc, char** _argv);
    void runString(int _argc, char** _argv);
    void runXml(int _argc, char** _argv);
    void runCode(int _argc, char** _argv);
    void runLogs(int _argc, char** _argv);
    void runJson(int _argc, char** _argv);
    void runCsv(int _argc, char** _argv);
    void runTree(int _argc, char** _argv);
    void runDebug(int _argc, char** _argv);
    void runMap(int _argc, char** _argv);
    void runResult(int _argc, char** _argv);
    void runMySQL(int _argc, char** _argv);
    void runRegex(int _argc, char** _argv);
    void runRegex2(const GString& _sql, ...);
};
//===============================================
#endif
//===============================================
