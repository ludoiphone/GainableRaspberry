#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>

#include "thread.h"
#include "gainable.h"
#include "dispcons.h"

class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    Thread *m_threadMainwindow;
    
    Gainable *m_machineEtat;
    
    DispCons *m_afficheCons;
    
    QWidget *m_window;
    
    void afficheConsignes();
    void stopGainable();
    void reStartGainable();

    QGroupBox *m_disp1; //temp
    QGroupBox *m_disp2; //tempUnitExt
    QGroupBox *m_disp3; //tempEcExt
    QGroupBox *m_disp4; //tempUnitInt
    QGroupBox *m_disp5; //tempEcInt
    
    
    QPushButton *m_marche;
    QPushButton *m_consigne;
    QPushButton *m_stop;
};
#endif // MAINWINDOW_H
