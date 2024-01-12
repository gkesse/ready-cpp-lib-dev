//===============================================
#include "GTest.h"
#include "GXml.h"
#include "GLog.h"
//===============================================
GTest::GTest()
: GObject() {

}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
    GString lMethod = "";
    if(_argc > 2) lMethod = _argv[2];

    if(lMethod == "") {
        printf("La méthode est obligatoire.\n");
    }
    else if(lMethod == "string") {
        runString(_argc, _argv);
    }
    else if(lMethod == "xml") {
        runXml(_argc, _argv);
    }
    else if(lMethod == "code") {
        runCode(_argc, _argv);
    }
    else if(lMethod == "logs") {
        runLogs(_argc, _argv);
    }
    else {
        printf("La méthode est inconnue.\n");
    }
}
//===============================================
void GTest::runString(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);

    GString lData;
    lData.print();

    GString lData2("Bonjour tout le monde.");
    lData2.print();

    GString lData3 = "Bonjour tout le monde (2).";
    lData3.print();

    GString lData4 = GString("Bonjour tout le monde (3).");
    lData4.print();

    lData = lData2;
    lData.print();

    if(lData == lData2) {
        printf("Les valeurs sont identiques.\n");
    }

    lData = "Bonjour tout le monde (4).";
    lData.print();

    if(lData != lData2) {
        printf("Les valeurs sont différentes.\n");
    }

    GString lData5 = 'A';
    lData5.print();

    GString lData6 = 10000;
    lData6.print();

    GString lData7 = 3.14;
    lData7.print();

    if(GString("cat") < GString("categorie")) {
        printf("(cat < categorie) est vrai.\n");
    }
    if(!(GString("cat") < GString("cat"))) {
        printf("(cat < cat) est faux.\n");
    }
    if(GString("cat") <= GString("cat")) {
        printf("(cat <= cat) est vrai.\n");
    }
    if(!(GString("cat") <= GString("cas"))) {
        printf("(cat <= cas) est faux.\n");
    }

    lData = "Bonjour tout le monde : ";
    lData += 2024;
    lData.print();

    lData = "Bonjour tout le monde : ";
    lData += GString() + 2024 + " - " + 'P' + 3.14;
    lData.print();

    GString lData8 = "Un_SEP_Deux_SEP_Trois";
    std::vector<GString> lSplit = lData8.split("_SEP_");
    for(std::vector<GString>::iterator it = lSplit.begin(); it != lSplit.end(); it++) {
        it->print();
    }

    sformat("Liste: %s = %f", "Pi", 3.14).print();
}
//===============================================
void GTest::runXml(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);

    GXml lXml;
    lXml.toString().print();

    lXml.createDoc();
    lXml.toString().print();

    GXml lObj = lXml.addObj("datas").addObj("data");
    lXml.toString().print();

    lObj.addData("code", "logs");
    lObj.addData("type", "error");
    lObj.addData("side", "server");
    lObj.addData("msg", "Le module est inconnu.");
    lXml.toString().print();
    lObj.toNode().print();

    lObj = lObj.addNode("map/data");
    lObj.addData("code", "logs");
    lObj.addData("type", "error");
    lObj.addData("side", "server");
    lObj.addData("msg", "Le module est inconnu.");

    lObj = lXml.addNode("/rdv/datas");
    lObj = lObj.addObj("data");
    lObj.addData("code", "page");
    lObj.addData("title", "admin");
    lObj.addData("path", "/home/admin");

    lXml.toNode().print();
}
//===============================================
void GTest::runCode(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);

    GCode lDom;

    lDom.createDoc();
    lDom.createDatas();
    lDom.createDatas();

    lDom.createCode("logs");
    lDom.createCode("logs");

    lDom.addData("logs", "type", "log");
    lDom.addData("logs", "type", "error");
    lDom.addData("logs", "side", "server");
    lDom.addData("logs", "msg", "Le module est obligatoire.");

    lDom.toString().print();
}
//===============================================
void GTest::runLogs(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);

    GLog lLog;
    lLog.serialize().print();

    lLog.addError("voici mon erreur.");
    lLog.addLog("voici mon log.");
    lLog.addData("voici ma donnée.");
    lLog.serialize().print();

    m_logs.addLogs(lLog);
}
//===============================================
