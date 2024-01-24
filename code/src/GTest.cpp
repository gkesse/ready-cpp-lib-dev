//===============================================
#include "GTest.h"
#include "GXml.h"
#include "GLog.h"
#include "GJson.h"
#include "GCsv.h"
#include "GTree.h"
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
        m_logs.addError("La méthode est obligatoire.");
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
    else if(lMethod == "json") {
        runJson(_argc, _argv);
    }
    else if(lMethod == "csv") {
        runCsv(_argc, _argv);
    }
    else if(lMethod == "tree") {
        runTree(_argc, _argv);
    }
    else {
        m_logs.addError("La méthode est inconnue.");
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

    GString(GString("Bonjour tout le monde").startsWith("Bonjour")).print();
    GString(GString("Bonjour tout le monde").startsWith("monde")).print();
    GString(GString("Bonjour tout le monde").endsWith("Bonjour")).print();
    GString(GString("Bonjour tout le monde").endsWith("monde")).print();

    GString("Bonjour Content-Length: 1234\r\n").extract("Content-Length:", "\r\n").print();
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
void GTest::runJson(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);

    GJson lDom, lNode, lNode2, lDom2;
    lDom.toString().print();

    lDom.createObj();
    lDom.toString().print();

    lDom.createArr();
    lDom.toString().print();

    lDom.createObj();
    lDom.addData("type", "error");
    lDom.addData("side", "server");
    lDom.addData("msg", "Le module est inconnu.");
    lDom.toString().print();

    lDom.createArr();
    lDom.addData("type");
    lDom.addData("side");
    lDom.addData("msg");
    lDom.toString().print();

    lDom.createObj();
    lNode = lDom.addObj("map");
    lNode.addData("type", "error");
    lNode.addData("side", "server");
    lNode.addData("msg", "Le module est inconnu.");
    lDom.toString().print();

    lDom.createObj();
    lNode = lDom.addArr("map");
    lNode2 = lNode.addObj();
    lNode2.addData("type", "error");
    lNode2.addData("side", "server");
    lNode2.addData("msg", "Le module est inconnu.");
    lNode2 = lNode.addObj();
    lNode2.addData("type", "error");
    lNode2.addData("side", "server");
    lNode2.addData("msg", "Le module est inconnu (2).");
    lNode2.toNode().print();
    lDom.toString().print();

    lDom.createArr();
    lNode = lDom.addObj();
    lNode.addData("type", "error");
    lNode.addData("side", "server");
    lNode.addData("msg", "Le module est inconnu.");
    lNode = lDom.addObj();
    lNode.addData("type", "error");
    lNode.addData("side", "server");
    lNode.addData("msg", "Le module est inconnu.");
    lDom.toString().print();

    lDom2.loadJson(lDom.toString());
    lDom.toString().print();

    GLog lLog;
    lLog.addError("voici mon erreur.");
    lLog.addLog("voici mon log.");
    lLog.addData("voici ma donnée.");
    lLog.serialize().print();

    GCode lCode;
    lCode.loadXml(lLog.serialize());
    lCode.toJson().print();

    GJson lJson;
    lJson.loadJson(lCode.toJson());
    lJson.toCode().print();
}
//===============================================
void GTest::runCsv(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);

    GCsv lCsv, lCsv2, lNode;
    lCsv.createCsv();
    lNode = lCsv.appendRow();
    lNode.appendCol("A11"); lNode.appendCol("A12"); lNode.appendCol("A13"); lNode.appendCol("A14");
    lNode = lCsv.appendRow();
    lNode.appendCol("A21"); lNode.appendCol("A22"); lNode.appendCol("A23"); lNode.appendCol("A24");
    lNode = lCsv.appendRow();
    lNode.appendCol("A31"); lNode.appendCol("A32"); lNode.appendCol("A33"); lNode.appendCol("A34");
    lNode = lCsv.appendRow();
    lNode.appendCol("A41"); lNode.appendCol("A42"); lNode.appendCol("A43"); lNode.appendCol("A44");
    lNode = lCsv.appendRow();
    lNode.appendCol("A51"); lNode.appendCol("A52"); lNode.appendCol("A53"); lNode.appendCol("A54");
    lCsv.toString().print();
    GString(lCsv.countRows()).print();
    GString(lCsv.countCols()).print();
    GString(lCsv.size()).print();

    lCsv2.loadCsv(lCsv.toString());
    lCsv2.toString().print();
    GString(lCsv2.countRows()).print();
    GString(lCsv2.countCols()).print();
    GString(lCsv2.size()).print();

    lCsv2.getCol(2, 1).setValue("M32");
    lNode = lCsv2.getRow(2);
    lNode = lNode.addRow();
    lNode.addCol("B01").addCol("B02").addCol("B03").addCol("B04");
    lNode = lNode.addRow();
    lNode.addCol("C01").addCol("C02").addCol("C03").addCol("C04");
    lCsv2.toString().print();
    GString(lCsv2.countRows()).print();
    GString(lCsv2.countCols()).print();
    GString(lCsv2.size()).print();

    lCsv2.getRow(2).toRow().print();
    lCsv2.getCol(2, 1).toCol().print();
}
//===============================================
void GTest::runTree(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);

    GTree lTree, lTree2, lNode, lNode2;
    lTree.createTree();
    lNode = lTree.appendChild("A1");
    lNode.appendChild("B1");
    lNode.appendChild("B2");
    lNode2 = lNode.appendChild("B3");
    lNode2.appendChild("C1");
    lNode2.appendChild("C2");
    lNode2.appendChild("C3");
    lNode2.appendChild("C4");
    lNode2.appendChild("C5");
    lNode.appendChild("B4");
    lNode.appendChild("B5");
    lTree.appendChild("A2");
    lTree.appendChild("A3");
    lTree.appendChild("A4");
    lTree.appendChild("A5");
    lTree.toString().print();
    lTree.toPrint().print();

    lTree2.loadTree(lTree.toString());
    lTree2.toPrint().print();
}
//===============================================
