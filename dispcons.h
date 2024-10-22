#ifndef DISPCONS_H
#define DISPCONS_H
#include <QtWidgets>

#include "sondes.h"
#include "modifcons.h"
#include "configini.h"

class DispCons: public QWidget
{
    Q_OBJECT

public:
    DispCons(QWidget *parent = nullptr);
    
    void afficheDispCons();

private:
    ModifCons *m_modifCons;
    
    Setting *m_configCons;
    
    Sondes *m_sondesDispCons;
    
    QWidget *m_window1;
    
    QTimer *m_timer2;
    
    void readCons();

    int m_timerReadCons = 1000; // maj ecran dispcons 
    
    QLabel *m_label1;
    
    QGroupBox *m_disp6;
    QLCDNumber *m_affCons1; //hiver/éte
   
    QGroupBox *m_disp7;
    QLCDNumber *m_affCons2; //canicule
    
    QGroupBox *m_disp8; //consigne canicule interieur automatique
    QLCDNumber *m_affCons3;
    
    QGroupBox *m_disp9;
    QLCDNumber *m_affCons4; //delta
    
    QGroupBox *m_disp10;
    QLCDNumber *m_affCons5; //blocChauffage
    
    QGroupBox *m_disp11;
    QLCDNumber *m_affCons6; //mode Degivrage chauffage
    
    QGroupBox *m_disp12;
    QLCDNumber *m_affCons7; //ventExtChauffage
    
    QGroupBox *m_disp13;
    QLCDNumber *m_affCons8; //ventExtFroid
    
    QGroupBox *m_disp14;
    QLCDNumber *m_affCons9; //fin deg chauffage
    
    QGroupBox *m_disp15; //consigne depart chaufage en chauffage
    QLCDNumber *m_affCons10;
    
    QGroupBox *m_disp16;
    QLCDNumber *m_affCons11; //consigne depart froid en chauffage
    
    QGroupBox *m_disp17;
    QLCDNumber *m_affCons12; //consigne vitesse int chauffage
    
    QGroupBox *m_disp18; //consigne depart froid en froid
    QLCDNumber *m_affCons13;
    
    QGroupBox *m_disp19; //consigne depart chaufage en froid
    QLCDNumber *m_affCons14;
    
    QGroupBox *m_disp20;
    QLCDNumber *m_affCons15; //consigne vitesse int froid
    
    QGroupBox *m_disp21; //consigne depart ventil chauffage
    QLCDNumber *m_affCons16;
    
    QGroupBox *m_disp22; //deg froid
    QLCDNumber *m_affCons17;
    
    QGroupBox *m_disp23; //fin deg froid
    QLCDNumber *m_affCons18;
    
    QPushButton *m_modifC;
    QPushButton *m_quitter;
    
    void modifConsignes();
    void closeWindow();
};

#endif // DISPCONS_H
