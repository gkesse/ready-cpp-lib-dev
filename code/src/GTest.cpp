//===============================================
#include "GTest.h"
#include "GXml.h"
#include "GLog.h"
#include "GJson.h"
#include "GCsv.h"
#include "GTree.h"
#include "GDebug.h"
#include "GMap.h"
#include "GMySQL.h"
#include "GRegex.h"
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
        slog(eGERR, "La méthode est obligatoire."
                    "|module=test");
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
    else if(lMethod == "debug") {
        runDebug(_argc, _argv);
    }
    else if(lMethod == "map") {
        runMap(_argc, _argv);
    }
    else if(lMethod == "result") {
        runResult(_argc, _argv);
    }
    else if(lMethod == "mysql") {
        runMySQL(_argc, _argv);
    }
    else if(lMethod == "regex") {
        runRegex(_argc, _argv);
    }
    else {
        slog(eGERR, "La méthode est inconnue."
                    "|module=test"
                    "|method=%s", lMethod.c_str());
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

    GString lData8 = "Un/Deux\\Trois\\Quatre";
    int lCount = lData8.countSep("/\\");
    for(int i = 0; i < lCount; i++) {
        lData8.extractSep("/\\", i).print();
    }

    sformat("Liste: %s = %f", "Pi", 3.14).print();

    GString(GString("Bonjour tout le monde").startsWith("Bonjour")).print();
    GString(GString("Bonjour tout le monde").startsWith("monde")).print();
    GString(GString("Bonjour tout le monde").endsWith("Bonjour")).print();
    GString(GString("Bonjour tout le monde").endsWith("monde")).print();

    GString("Bonjour Content-Length: 1234\r\n").extract("Content-Length:", "\r\n").print();
    GString("Un:-:Deux:-:Trois:-:Quatre").extractEnd(":-:", 1).print();

    GString("select * from user where _id = :id and _id > :id").replaceAll(":id", 1000).print();
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
    lLog.addInfo("voici mon log.");
    lLog.addData("voici ma donnée.");
    lLog.serialize().print();
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
    lLog.addInfo("voici mon log.");
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
void GTest::runDebug(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);
    GDebug lDebug;
    slog(eGINF, "Bonjour tout le monde");
}
//===============================================
void GTest::runMap(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);
    GMap lMap;
    lMap.createMap();

    lMap.addData("email", "kesse@gmail.com");
    lMap.addData("password", "123456");
    lMap.addData("newsletter", "on");
    lMap.addData("password", "000123");
    lMap.toString().print();
    GString(lMap.size()).print();

    lMap.getData("email").print();
    lMap.getData("password").print();
    lMap.getData("newsletter").print();

    GString(lMap.size()).print();

    GMap lMap2;
    lMap2.createMap();
    lMap2.loadMap(lMap);
    lMap2.addData("date", "10-02-2024");
    lMap2.toString().print();
}
//===============================================
void GTest::runResult(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);
    GString lData = "<result>OK</result>";
    GXml lDom;
    lDom.loadNode(lData);
    lDom.getNode("/result").getValue().print();
}
//===============================================
void GTest::runMySQL(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);
    GMySQL lMySQL;
    lMySQL.readData(""
            " select User from mysql.user "
            "").print();

    lMySQL.readData(""
            " select User from mysql.user "
            " where User = #(user)s "
            "", "user", "admins").print();

    lMySQL.readData("select uuid() as _uuid").print();

    suuid().print();
}
//===============================================
void GTest::runRegex(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);
    {
        GRegex lRegex = "Harry Botter - The robot who lived.";

        GString(lRegex.countMatch("[^\\s]+")).print();
    }
    {
        GRegex lRegex = ""
                " select * from _table"
                " where _id = #(id)i "
                " and _name = #(name)s "
                " and _pass = #(pass)b "
                "";

        GString(lRegex.countMatch("#\\([A-Za-z]+\\)[a-z]")).print();
    }
    {
        GRegex lRegex = ""
                " select * from _table"
                " where _id = #(id)i "
                " and _name = #(name)s "
                " and _pass = #(pass)b "
                "";

        lRegex.replaceMatch("#\\([A-Za-z]+\\)[a-z]", "?").print();
    }
    {
        GRegex lRegex = ""
                " select * from _table"
                " where _id = #(id)i "
                " and _name = #(name)s "
                " and _pass = #(pass)b "
                "";

        lRegex.searchMatch("(#\\([A-Za-z]+\\)[a-z])", 0, 0).print();
        lRegex.searchMatch("(#\\([A-Za-z]+\\)[a-z])", 1, 0).print();
        lRegex.searchMatch("(#\\([A-Za-z]+\\)[a-z])", 2, 0).print();
    }
    {
        GRegex lRegex = ""
                " select * from _table"
                " where _id = #(id)i "
                " and _name = #(name)s "
                " and _pass = #(pass)b "
                "";

        lRegex.searchMatch("#\\(([A-Za-z]+)\\)([a-z])", 0, 0).print();
        lRegex.searchMatch("#\\(([A-Za-z]+)\\)([a-z])", 0, 1).print();
        lRegex.searchMatch("#\\(([A-Za-z]+)\\)([a-z])", 0, 2).print();
        lRegex.searchMatch("#\\(([A-Za-z]+)\\)([a-z])", 1, 0).print();
        lRegex.searchMatch("#\\(([A-Za-z]+)\\)([a-z])", 1, 1).print();
        lRegex.searchMatch("#\\(([A-Za-z]+)\\)([a-z])", 1, 2).print();
        lRegex.searchMatch("#\\(([A-Za-z]+)\\)([a-z])", 2, 0).print();
        lRegex.searchMatch("#\\(([A-Za-z]+)\\)([a-z])", 2, 1).print();
        lRegex.searchMatch("#\\(([A-Za-z]+)\\)([a-z])", 2, 2).print();
    }
    {
        GRegex lRegex = ""
                " select * from _table"
                " where _id = #(id)i "
                " and _name = #(name)s "
                " and _pass = #(pass)b "
                " and _userId = #(id)ia "
                " and _country = #(name)sb"
                "";

        int lCount = lRegex.countMatch("#\\([A-Za-z]+\\)[a-z]");
        GMap lNameTypes;
        lNameTypes.createMap();

        if(lCount) {
            for(int i = 0; i < lCount; i++) {
                GString lPattern = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 0);
                GString lName = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 1);
                GString lType = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 2);

                if((lType != "i") && (lType != "int") &&
                   (lType != "ui") && (lType != "uint") &&
                   (lType != "ii") && (lType != "bigint") &&
                   (lType != "s") && (lType != "string") &&
                   (lType != "d") && (lType != "double") &&
                   (lType != "b") && (lType != "bool") &&
                   (lType != "bb") && (lType != "blob") &&
                   (lType != "dt") && (lType != "datetime")) {
                    slog(eGERR, "Le type du paramètre est inconnu."
                                "|pattern=%s"
                                "|name=%s"
                                "|type=%s", lPattern.c_str(), lName.c_str(), lType.c_str());
                }
                else {
                    slog(eGINF, "Analyse de la requête."
                                "|pattern=%s"
                                "|name=%s"
                                "|type=%s", lPattern.c_str(), lName.c_str(), lType.c_str());
                }
                lNameTypes.addData(lName, lType);
            }

            int lCount2 = lNameTypes.size();

            slog(eGINF, "Le nombre de noms de paramètres."
                        "|count=%d", lCount2);

            for(int i = 0; i < lCount2; i++) {
                GMapKV lMapKV = lNameTypes.getData(i);
                slog(eGINF, "La liste des types de paramètres."
                            "|name=%s"
                            "|type=%s", lMapKV.m_key.c_str(), lMapKV.m_value.c_str());
            }
        }
        {
            runRegex2(""
                    " select * from _table"
                    " where _id = #(id)i "
                    " and _name = #(name)s "
                    " and _pass = #(pass)s "
                    " and _userId = #(id)i "
                    " and _country = #(name)s"
                    "", "id", 1000
                    , "name", "kessege"
                    , "pass", "123456");
        }
    }
}
//===============================================
void GTest::runRegex2(const GString& _sql, ...) {
    if(_sql.isEmpty()) return;
    GRegex lRegex = _sql;
    int lCount = lRegex.countMatch("#\\([A-Za-z]+\\)[a-z]");
    GMap lTypes, lPatterns, lValues;
    std::vector<GString> lParams;

    lTypes.createMap();
    lPatterns.createMap();
    lValues.createMap();

    for(int i = 0; i < lCount; i++) {
        GString lPattern = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 0);
        GString lName = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 1);
        GString lType = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 2);

        if((lType != "b") && (lType != "bool") &&
           (lType != "i") && (lType != "int") &&
           (lType != "ii") && (lType != "bigint") &&
           (lType != "s") && (lType != "string") &&
           (lType != "d") && (lType != "double") &&
           (lType != "bb") && (lType != "blob") &&
           (lType != "dt") && (lType != "datetime")) {
            slog(eGERR, "Le type de paramètre est inconnu."
                        "|pattern=%s"
                        "|name=%s"
                        "|type=%s"
                        "|sql=%s", lPattern.c_str(), lName.c_str(), lType.c_str(), _sql.c_str());
            return;
        }

        lTypes.addData(lName, lType);
        lPatterns.addData(lPattern, lName);
        lParams.push_back(lPattern);
    }

    if(lTypes.size() != lPatterns.size()) {
        slog(eGERR, "Les nombres de paramètres et de patterns sont différents."
                    "|pattern=%d"
                    "|name=%d"
                    "|sql=%s", lPatterns.size(), lTypes.size(), _sql.c_str());
        return;
    }

    va_list lArgs;
    va_start(lArgs, _sql);

    for(int i = 0; i < lTypes.size(); i++) {
        GString lName = (const char*)va_arg(lArgs, const char*);
        if(!lTypes.isKey(lName)) {
            slog(eGERR, "Le nom de paramètre est inconnu."
                        "|name=%s"
                        "|sql=%s", lName.c_str(), _sql.c_str());
            return;
        }
        GString lType = lTypes.getData(lName);
        GString lValue;

        if((lType == "b") || (lType == "bool")) {
            lValue = (bool)va_arg(lArgs, int);
        }
        else if((lType == "i") || (lType == "int")) {
            lValue = (int)va_arg(lArgs, int);
        }
        else if((lType == "ii") || (lType == "bigint")) {
            lValue = (long)va_arg(lArgs, long);
        }
        else if((lType == "d") || (lType == "double")) {
            lValue = (double)va_arg(lArgs, double);
        }
        else if((lType == "s") || (lType == "string")) {
            lValue = (const char*)va_arg(lArgs, const char*);
        }
        else if((lType == "bb") && (lType == "blob")) {
            lValue = (const char*)va_arg(lArgs, const char*);
        }
        else if((lType == "dt") && (lType == "datetime")) {
            lValue = (const char*)va_arg(lArgs, const char*);
        }
        else {
            slog(eGERR, "Le type de paramètre est inconnu."
                        "|name=%s"
                        "|type=%s"
                        "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
            return;
        }

        lValues.addData(lName, lValue);
    }

    va_end(lArgs);

    GString lSql = lRegex.replaceMatch("#\\([A-Za-z]+\\)[a-z]", "?");

    slog(eGOFF, "La requête sql a été transformée."
                "|size=%d"
                "|sql=%s", lParams.size(), lSql.c_str());

    GString lSqlText = lRegex;

    for(int i = 0; i < lPatterns.size(); i++) {
        GMapKV lMapKV = lPatterns.getData(i);
        GString lPattern = lMapKV.m_key;
        GString lName = lMapKV.m_value;
        GString lValue = lValues.getData(lName);
        GString lType = lTypes.getData(lName);

        if((lType == "s") || (lType == "string")) {
            lValue = sformat("'%s'", lValue.c_str());
        }

        lSqlText = lSqlText.replaceAll(lPattern, lValue);
    }

    slog(eGOFF, "La requête sql a été traduite."
                "|size=%d"
                "|sql=%s", lParams.size(), lSqlText.c_str());

    for(int i = 0; i < lParams.size(); i++) {
        GString lPattern = lParams.at(i);
        GString lName = lPatterns.getData(lPattern);
        GString lValue = lValues.getData(lName);
        GString lType = lTypes.getData(lName);

        slog(eGOFF, "La requête sql a été analysée."
                    "|index=%d"
                    "|pattern=%s"
                    "|name=%s"
                    "|type=%s"
                    "|value=%s", i, lPattern.c_str(), lName.c_str(), lType.c_str(), lValue.c_str());

    }
}
//===============================================
