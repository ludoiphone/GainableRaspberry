#ifndef VITESSEVENTILATEUR_HPP
#define VITESSEVENTILATEUR_HPP
#include <QtWidgets>

#include "sondes.h"
#include "configini.h"

class VitesseVentil: public QWidget
{
    Q_OBJECT

public:
    VitesseVentil();
    
    bool tempVitIntCa = false;
    bool tempVitExtFr = false;
    bool tempVitIntFr = false;
    bool tempVitExtCh = false;
    bool tempVitIntCh = false;
    
    void hysteresisTempVitesseIntCa();
    void hysteresisTempVitesseExtFroid();
    void hysteresisTempVitesseIntFroid();
    void hysteresisTempVitesseIntChauf();
    void hysteresisTempVitesseExtChauf();

private:
    Sondes *m_sondesVitesses;
    
    Setting *m_vitesseCons;

    double hysteresis = 0.5;
    double hysteresis1 = 1.0;
    double hysteresisVentExtFr = 3;
};

#endif // VITESSEVENTILATEUR_HPP
