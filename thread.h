#ifndef THREAD_H
#define THREAD_H
#include <QtWidgets>
#include <QThread>

#include "sondes.h"
#include "gainable.h"
#include "relais.h"
#include "vitesseventilateur.h"

class Thread: public QThread
{
	Q_OBJECT
	
public:
    Thread();
    
    bool departGainable = true;
    
    QLCDNumber *m_affTemp1;
    QLCDNumber *m_affTemp2;
    QLCDNumber *m_affTemp3;
    QLCDNumber *m_affTemp4;
    QLCDNumber *m_affTemp5;
    
    QLabel *m_label;
    QLabel *m_labelGifChauffe;
    QLabel *m_labelGifFroid;
    QLabel *m_labelGifDegivrage;
    QLabel *m_labelGifEgouttage;
    QLabel *m_labelGifVentExt;
    QLabel *m_labelGifVentInt;
    QLabel *m_labelGifVitesse1Ext;
    QLabel *m_labelGifVitesse2Ext;
    QLabel *m_labelGifVitesse1Int;
    QLabel *m_labelGifVitesse4Int;
    
    QMovie *m_gifChauffe;
    QMovie *m_gifFroid;
    QMovie *m_gifDegivrage;
    QMovie *m_gifEgouttage;
    QMovie *m_gifVentExt;
    QMovie *m_gifVentInt;
    QMovie *m_gifVitesse1Ext;
    QMovie *m_gifVitesse2Ext;
    QMovie *m_gifVitesse1Int;
    QMovie *m_gifVitesse4Int;
    
    void afficheLabel();
    void afficheGifChauffe();
    void afficheGifFroid();
    void afficheGifDegivrage();
    void afficheGifEgouttage();
    void afficheGifVentExt();
    void afficheGifVentInt();
    void afficheGifVitesse1VentExt();
    void afficheGifVitesse2VentExt();
    void afficheGifVitesse1VentInt();
    void afficheGifVitesse4VentInt();
    
    void affichageFroid();
    void affichageChauffage();
    
    void effaceGifs();
    
private:
    Sondes *m_threadSondes;
    
    Gainable *m_threadGainable;
    
    Relais *m_threadRelais;
    
    VitesseVentil *m_threadVitesseVentil;
    
    void vitesseInt();

    void run();
    void stop();
};

#endif // THREAD_H
