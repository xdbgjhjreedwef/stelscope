#include "mainwindow.h"
#include "chartview.h"

#include "StelApp.hpp"
#include <StelIniParser.hpp>
#include <StelFileMgr.hpp>
#include <StelLogger.hpp>

#include <StelObjectMgr.hpp>
#include <StelCore.hpp>

#include <chrono>
#include <thread>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::MainWindow)
    , chartView(new ChartView)
{
    QPixmap p = QPixmap(":target.png");
    QCursor c = QCursor(p, p.size().rwidth()/2, p.size().rheight()/2);
    setCursor(c);
    //TODO: load stars tycho2fit || stellarium minimal
    //TODO: in separete thread(s)
    //TODOL: do not redraw, if motion < 1 pixel (0.5 pixel?)
    //TODO: move stars using sys time
    //TODO: Sun, Moon, planets
    //TODO: update star cat to date/location
    //TODO: polar to square coords (or "inflated" square)
    //TODO: telnet
    //TODO: usb serial
    //TODO: polar to gcode; adjusted to steps/mm
    //TODO: propagator(test neptune?)
    //TODO: qchart callout
    //TODO: homing to Polar star
    setMinimumSize(480,480);
    setCentralWidget(chartView);



    StelFileMgr::init();

    StelLogger::init(StelFileMgr::getUserDir()+"/log.txt");
//    QString argStr;
//    QStringList argList;
//    for (int i=0; i<argc; ++i)
//    {
//        argList << argv[i];
//        argStr += QString("%1 ").arg(argv[i]);
//    }
//    StelLogger::writeLog(argStr);
    //TODO: fileMgr must find this?
    ///FIXME: bad user dir
    QSettings* confSettings = new QSettings(StelFileMgr::getUserDir()+"/config.ini", StelIniFormat);

    StelApp *stelApp = new StelApp();
    stelApp->init(confSettings);
    //TODO: check if exists file

    //FIXME: ugly loading process
    //NOTE: needs time to init
    qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        qDebug()<<"--------settings------:"<<confSettings->fileName()<<StelFileMgr::getUserDir();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    StelCore *core = stelApp->getCore();
    StelObjectMgr* mgr =  reinterpret_cast<StelObjectMgr*>(stelApp->getModule("StelObjectMgr"));

    StelObjectP polarisPname = mgr->searchByName("Polaris");

    QString polarisCoord = "not found";
    //FIXME: update call
    //core->update(0.);
    if(!polarisPname.isNull())
    {
        polarisCoord =
        QString::number(polarisPname->getAltAzPosAuto(core).longitude()*180/M_PI)
                .append(":")
                .append(QString::number(polarisPname->getAltAzPosAuto(core).latitude()*180/M_PI))
                .append(":::")
                .append(QString::number(polarisPname->getJ2000EquatorialPos(core).latitude()*180/M_PI))
                .append(":")
                .append(QString::number(polarisPname->getJ2000EquatorialPos(core).longitude()*180/M_PI));
      //  core->getRefraction();
         QMap <QString,QVariant> pMap = polarisPname->getInfoMap(core);
       // qDebug()<<pMap;
         QPointF polarisPoint(180.-polarisPname->getAltAzPosAuto(core).longitude()*180/M_PI,
                                 90-polarisPname->getAltAzPosAuto(core).latitude()*180/M_PI);
    }
     qDebug()<<"searchByName Polaris:"<<polarisPname->getEnglishName()<<"@"<<polarisCoord;





    QString hip11767 = !mgr->searchByName("HIP 11767").isNull() ? mgr->searchByName("HIP 11767")->getEnglishName() :
                                                            "not found";
    qDebug()<<"searchByName HIP 11767:"<<hip11767;
    //qDebug()<<core->getCurrentLocation().latitude<<core->getCurrentLocation().longitude;

    for(auto i=0;i<1;i++)
    {
     std::this_thread::sleep_for(std::chrono::milliseconds(10));
    QList<QPair<float,QPointF>> starsList;
    QList<StelObjectP> altAzP =  mgr->altAzFind(StelApp::getInstance().getCore(),90,0,
                                                25,4);

    foreach(auto i,altAzP)
    {
        QPointF iPoint(abs(180-i->getAltAzPosAuto(core).longitude()*180/M_PI),
                                i->getAltAzPosAuto(core).latitude()*180/M_PI);
        float magC = abs(27-i->getVMagnitudeWithExtinction(core))/5;
        float mag = (i->getVMagnitudeWithExtinction(core));
        if(mag<0. || i->getEnglishName()=="HIP 11767")
           qDebug()<<"type:"<<i->getType()<<"mag:"<<mag<<"Name:"<<i->getEnglishName()<<
                  "@"<<iPoint.x()<<":"<<iPoint.y()<<magC;
        QPair<float,QPointF> pair = {magC,iPoint};
        starsList.append(pair);
    }
    chartView->addPoints(starsList);
//    QDateTime qdt;
//    double JD =
//    qdt.date().toJulianDay()+static_cast<double>(1./(24*60*60*1000))*QTime(0, 0, 0, 0).msecsTo(qdt.time())-0.5;
    core->setJD(core->getJD()+1);
    core->update(0.);
    }
 //   QString altAzSearch = !altAzP.isNull() ? altAzP->getEnglishName() : "altAz search is null" ;

 //   qDebug()<<altAzSearch;
    qDebug()<<"===========================current pos"<<core->getCurrentLocation().latitude<<
              core->getCurrentLocation().longitude<<core->getCurrentLocation().altitude;
    qDebug()<<core->getLocalSiderealTime();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//    if(!mgr->searchByName("Polaris").isNull())
//    {polarisCoord =
//        QString::number(mgr->searchByName("Polaris")->getAltAF
//                .append(QString::number(mgr->searchByName("Polaris")->getAltAzPosAuto(core).latitude()*180/M_PI))
//    .append("");}
    qDebug()<<"is in real time"<<core->getIsTimeNow();

    qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
}

MainWindow::~MainWindow()
{
    //delete ui;
}

