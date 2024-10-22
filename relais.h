#ifndef RELAIS_H
#define RELAIS_H
#include <QtWidgets>

#include "vitesseventilateur.h"

class Relais: public QWidget
{
    Q_OBJECT
	
public:
    Relais();
    
    bool forceVentIntDegFr = false;
    
    void activeRelaiEteHiver();
    void activeRelaiV4V();
    void activeRelaiComp();
    void desactiveRelaiEteHiver();
    void activeRelaisVentilationInt();
    void activeRelaisVentFroid();
    void activeRelaisVentExtChauffage();
    void desactiveRelaisVentIntCh();
    void activeRelaisVitesseVentIntChauffage();
    void activeRelaisVentExtCanicule();
    void activeRelaisVentIntCanicule();
    void activeRelaisVentEgouttageFr();
    void activeRelaisVentEgouttageCh();
    void desactiveTousRelais();
    
    void testRelais();

private:
    VitesseVentil *m_vitesseHyst;
    
    void desactiveRelaiV4V();
    void desactiveRelaiComp();
};

#endif
