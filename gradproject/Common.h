#ifndef COMMON_H
#define COMMON_H

#include "sstream"
#include "vector"
#include "queue"
#include "stdlib.h"
#include "time.h"
#include <QRandomGenerator>
#include <QString>
#include <QProcess>
#include <QDebug>
#include "fstream"
#include <QPixmap>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>
#include <synchapi.h>
#include <QMessageBox>
#include "algorithm"
#include "iostream"
#include "utility"

const QString SavePicturePathConst = "D:/GradProject/Picture/" ;
const QString SaveDotPathConst = "D:/GradProject/Dot/" ;
const QString DotExeConst = "C:/Program Files/Graphviz/bin/dot.exe" ;
const QString NeatoExeConst = "C:/Program Files/Graphviz/bin/neato.exe" ;
const QString OpenPictureExe = "C:/Program Files/WPSPhoto/wpsphoto+.exe" ;
const QString SaveProblemPath = "D:/GradProject/Problem/" ;
const QString SaveAnswerPath = "D:/GradProject/Answer/" ;


inline void Save_File(QString DotName = "graph" , QString FileName = "Tree"){
    Sleep(200);
    QProcess* process = new QProcess();
    if(FileName != "Graph") {
        process->startDetached(DotExeConst,
        QStringList() << "-Tpng" << SaveDotPathConst + DotName +".dot" << "-o" << SavePicturePathConst + FileName + ".png");
    }else {
        process->startDetached(NeatoExeConst,
        QStringList() << "-Tpng" << SaveDotPathConst + DotName +".dot" << "-o" << SavePicturePathConst + FileName + ".png");
    }
    /*
    process->waitForReadyRead(100);
    qDebug() << process->arguments();
    qDebug() << process->readAll();
    qDebug() << process->exitCode();
    */
}

inline void Open_Picture(QString PngName ) {
    Sleep(200);
    QProcess* process = new QProcess();
    process->startDetached(OpenPictureExe,
                     QStringList() << "\"" + SavePicturePathConst + PngName + ".png\"");
}
#endif // COMMON_H
