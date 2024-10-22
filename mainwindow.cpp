#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QWidget (parent)
{
    qDebug() << "mainwindow";
    
    m_threadMainwindow = new Thread();
    
    m_machineEtat = new Gainable();
    
    m_afficheCons = new DispCons();

    m_window =new QWidget;
    m_window ->setFixedSize(1920,1080);
    m_window ->setWindowTitle("Gainable");
    adjustSize();
    
    m_threadMainwindow ->m_label = new QLabel(m_window);
    m_threadMainwindow ->afficheLabel();
    
    m_threadMainwindow ->m_labelGifChauffe = new QLabel(m_window);
    m_threadMainwindow ->afficheGifChauffe();
    
    m_threadMainwindow ->m_labelGifFroid = new QLabel(m_window);
    m_threadMainwindow ->afficheGifFroid();
    
    m_threadMainwindow ->m_labelGifVentExt = new QLabel(m_window);
    m_threadMainwindow ->afficheGifVentExt();
    
    m_threadMainwindow ->m_labelGifVentInt = new QLabel(m_window);
    m_threadMainwindow ->afficheGifVentInt();
    
    m_threadMainwindow ->m_labelGifDegivrage = new QLabel(m_window);
    m_threadMainwindow ->afficheGifDegivrage();
    
    m_threadMainwindow ->m_labelGifEgouttage = new QLabel(m_window);
    m_threadMainwindow ->afficheGifEgouttage();
    
    m_threadMainwindow ->m_labelGifVitesse1Ext = new QLabel(m_window);
    m_threadMainwindow ->afficheGifVitesse1VentExt();
    
    m_threadMainwindow ->m_labelGifVitesse2Ext = new QLabel(m_window);
    m_threadMainwindow ->afficheGifVitesse2VentExt();
    
    m_threadMainwindow ->m_labelGifVitesse1Int = new QLabel(m_window);
    m_threadMainwindow ->afficheGifVitesse1VentInt();
    
    m_threadMainwindow ->m_labelGifVitesse4Int = new QLabel(m_window);
    m_threadMainwindow ->afficheGifVitesse4VentInt();
    
    m_disp1 = new QGroupBox("Temp°C Ext",m_window);
    m_disp1 ->setStyleSheet("QGroupBox:title {color: orangered;}");
    m_disp1 ->setFont(QFont("Times", 18, QFont::Bold));
    m_disp1 ->setGeometry(200,40,240,120);

    m_disp2 = new QGroupBox("Temp°C UnitExt",m_window);
    m_disp2 ->setStyleSheet("QGroupBox:title {color: orangered;}");
    m_disp2 ->setFont(QFont("Times", 18, QFont::Bold));
    m_disp2 ->setGeometry(520,40,240,120);
    
    m_disp3 = new QGroupBox("Temp°C EcUnitExt",m_window);
    m_disp3 ->setStyleSheet("QGroupBox:title {color: orangered;}");
    m_disp3 ->setFont(QFont("Times", 18, QFont::Bold));
    m_disp3 ->setGeometry(840,40,240,120);

    m_disp4 = new QGroupBox("Temp°C UnitInt",m_window);
    m_disp4 ->setStyleSheet("QGroupBox:title {color: orangered;}");
    m_disp4 ->setFont(QFont("Times", 18, QFont::Bold));
    m_disp4 ->setGeometry(1160,40,240,120);
    
    m_disp5 = new QGroupBox("Temp°C EcUnitInt",m_window);
    m_disp5 ->setStyleSheet("QGroupBox:title {color: orangered;}");
    m_disp5 ->setFont(QFont("Times", 18, QFont::Bold));
    m_disp5 ->setGeometry(1480,40,240,120);

    m_threadMainwindow ->m_affTemp1 = new QLCDNumber(m_disp1);
    m_threadMainwindow ->m_affTemp1 ->setGeometry(0,35,240,80);
	m_threadMainwindow ->m_affTemp1 ->show();
    
    m_threadMainwindow ->m_affTemp2 = new QLCDNumber(m_disp2);
    m_threadMainwindow ->m_affTemp2 ->setGeometry(0,35,240,80);
	m_threadMainwindow ->m_affTemp2 ->show();
    
    m_threadMainwindow ->m_affTemp3 = new QLCDNumber(m_disp3);
    m_threadMainwindow ->m_affTemp3 ->setGeometry(0,35,240,80);
    m_threadMainwindow ->m_affTemp3 ->show();
    
    m_threadMainwindow ->m_affTemp4 = new QLCDNumber(m_disp4);
    m_threadMainwindow ->m_affTemp4 ->setGeometry(0,35,240,80);
    m_threadMainwindow ->m_affTemp4 ->show();
    
    m_threadMainwindow ->m_affTemp5 = new QLCDNumber(m_disp5);
    m_threadMainwindow ->m_affTemp5 ->setGeometry(0,35,240,80);
    m_threadMainwindow ->m_affTemp5 ->show();
    
    m_marche = new QPushButton("Démarrage ??",m_window);
    m_marche ->setGeometry(1080,900,240,95);
    m_marche ->setStyleSheet("font-size: 30px;background-color: lime");
    m_marche ->hide();
    
    m_consigne = new QPushButton("Consignes",m_window);
    m_consigne ->setGeometry(1340,900,240,95);
    m_consigne ->setStyleSheet("font-size: 30px;");
    m_consigne ->show();
    
    m_stop = new QPushButton("Stop ??",m_window);
    m_stop ->setGeometry(1600,900,240,95);
    m_stop ->setStyleSheet("font-size: 30px;background-color: red");
    m_stop ->show();
    
    connect(m_marche,&QPushButton::clicked,m_marche,[this](){reStartGainable();});
    connect(m_consigne,&QPushButton::clicked,m_consigne,[this](){afficheConsignes();});
    connect(m_stop,&QPushButton::clicked,m_stop,[this](){stopGainable();});
    
    m_threadMainwindow ->start();
    
    m_window->show();
}

void MainWindow::afficheConsignes()
{
    m_afficheCons ->afficheDispCons();
}

void MainWindow::stopGainable()
{
    qDebug() << "arret Gainable";
    m_stop ->hide();
    m_marche ->show();
    m_threadMainwindow ->departGainable = false;
}

void MainWindow::reStartGainable()
{
    m_marche ->hide();
    m_stop ->show();
    m_threadMainwindow ->departGainable = true;
    m_machineEtat ->autoModeEteHiver();
}
