#include "thread.h"

Thread::Thread()
{
	qDebug() << "Thread";
	
	m_threadSondes = new Sondes();
	
	m_threadGainable = new Gainable();
	
	m_threadRelais = new Relais();
	
	m_threadVitesseVentil = new VitesseVentil();
}

void Thread::afficheLabel()
{
    m_label ->setPixmap(QPixmap("/home/ludo/Qt/test/build/images/abigael.jpg"));
    m_label ->show();
    
    /*if (m_threadGainable ->modeFroid == true && a == 0) {
	for (a = 0; a < 1; a = a++) {
	    m_label ->setPixmap(QPixmap("/home/ludo/Qt/test/build/images/froid.jpg"));
	    m_label ->show();
	    a = 1;
	}
    } else if (m_threadGainable ->modeChauffage == true && a == 0) {
	for (a = 0; a < 1; a = a++) {
	    m_label ->setPixmap(QPixmap("/home/ludo/Qt/test/build/images/chauffage.jpg"));
	    m_label ->show();
	    a = 1;
	}
    } else if (m_threadGainable ->modeCanicule == true && a == 0) {
	for (a = 0; a < 1; a = a++) {
	    m_label ->setPixmap(QPixmap("/home/ludo/Qt/test/build/images/canicule.jpg"));
	    m_label ->show();
	    a = 1;
	}
    } else if (a == 0) {*/
	
    //}
}

void Thread::afficheGifVentInt()
{
    m_labelGifVentInt ->setGeometry(1105,845,200,200);
    m_gifVentInt = new QMovie("/home/ludo/Qt/test/build/gif/ventilateurInt.gif");
    m_labelGifVentInt ->hide();
    m_labelGifVentInt ->setMovie(m_gifVentInt);
    m_gifVentInt ->start();
}

void Thread::afficheGifVentExt()
{
    m_labelGifVentExt ->setGeometry(910,830,200,200);
    m_gifVentExt = new QMovie("/home/ludo/Qt/test/build/gif/ventilateurExt.gif");
    m_labelGifVentExt ->hide();
    m_labelGifVentExt ->setMovie(m_gifVentExt);
    m_gifVentExt ->start();
}

void Thread::afficheGifChauffe()
{
    m_labelGifChauffe ->setGeometry(1220,840,200,200);
    m_gifChauffe = new QMovie("/home/ludo/Qt/test/build/gif/chauffage.gif");
    m_labelGifChauffe ->hide();
    m_labelGifChauffe ->setMovie(m_gifChauffe);
    m_gifChauffe ->start();
}

void Thread::afficheGifFroid()
{
    m_labelGifFroid ->setGeometry(1210,845,200,200);
    m_gifFroid = new QMovie("/home/ludo/Qt/test/build/gif/froid.gif");
    m_labelGifFroid ->hide();
    m_labelGifFroid ->setMovie(m_gifFroid);
    m_gifFroid ->start();
}

void Thread::afficheGifDegivrage()
{
    m_labelGifDegivrage ->setGeometry(1220,850,200,200);
    m_gifDegivrage = new QMovie("/home/ludo/Qt/test/build/gif/degivrage.gif");
    m_labelGifDegivrage ->hide();
    m_labelGifDegivrage ->setMovie(m_gifDegivrage);
    m_gifDegivrage ->start();
}

void Thread::afficheGifEgouttage()
{
    m_labelGifEgouttage ->setGeometry(1120,820,200,200);
    m_gifEgouttage = new QMovie("/home/ludo/Qt/test/build/gif/egouttage.gif");
    m_labelGifEgouttage ->hide();
    m_labelGifEgouttage ->setMovie(m_gifEgouttage);
    m_gifEgouttage ->start();
}

void Thread::afficheGifVitesse1VentExt()
{
    m_labelGifVitesse1Ext ->setGeometry(860,900,60,60);
    m_gifVitesse1Ext = new QMovie("/home/ludo/Qt/test/build/gif/vitesse1.gif");
    m_labelGifVitesse1Ext ->hide();
    m_labelGifVitesse1Ext ->setMovie(m_gifVitesse1Ext);
    m_gifVitesse1Ext ->start();
}

void Thread::afficheGifVitesse2VentExt()
{
    m_labelGifVitesse2Ext ->setGeometry(860,900,60,60);
    m_gifVitesse2Ext = new QMovie("/home/ludo/Qt/test/build/gif/vitesse2.gif");
    m_labelGifVitesse2Ext ->hide();
    m_labelGifVitesse2Ext ->setMovie(m_gifVitesse2Ext);
    m_gifVitesse2Ext ->start();
}

void Thread::afficheGifVitesse1VentInt()
{
    m_labelGifVitesse1Int ->setGeometry(1040,900,60,60);
    m_gifVitesse1Int = new QMovie("/home/ludo/Qt/test/build/gif/vitesse1.gif");
    m_labelGifVitesse1Int ->hide();
    m_labelGifVitesse1Int ->setMovie(m_gifVitesse1Int);
    m_gifVitesse1Int ->start();
}

void Thread::afficheGifVitesse4VentInt()
{
    m_labelGifVitesse4Int ->setGeometry(1040,900,60,60);
    m_gifVitesse4Int = new QMovie("/home/ludo/Qt/test/build/gif/vitesse4.gif");
    m_labelGifVitesse4Int ->hide();
    m_labelGifVitesse4Int ->setMovie(m_gifVitesse4Int);
    m_gifVitesse4Int ->start();
}

void Thread::effaceGifs()
{
    m_labelGifVentInt ->hide();
    m_labelGifVentExt ->hide();
    m_labelGifVitesse1Int ->hide();
    m_labelGifVitesse4Int ->hide();
    m_labelGifVitesse1Ext ->hide();
    m_labelGifVitesse2Ext ->hide();
    m_labelGifFroid ->hide();
    m_labelGifChauffe ->hide();
}

void Thread::affichageFroid()
{
    m_label ->setPixmap(QPixmap("/home/ludo/Qt/test/build/images/froid.jpg"));
    m_label ->show();
    
    if (m_threadGainable ->gifVentilInt == true) {
	m_threadVitesseVentil ->hysteresisTempVitesseIntFroid();
	m_labelGifVentInt ->show();
	if (m_threadVitesseVentil ->tempVitIntFr == true) {
	    m_labelGifVitesse1Int ->hide();
	    m_labelGifVitesse4Int ->show();
	} else {
	    m_labelGifVitesse4Int ->hide();
	    m_labelGifVitesse1Int ->show();
	}
    } else {
	m_labelGifVitesse1Int ->hide();
	m_labelGifVitesse4Int ->hide();
	m_labelGifVentInt ->hide();
    }
    if (m_threadGainable ->gifVentilExt == true) {
	m_threadVitesseVentil ->hysteresisTempVitesseExtFroid();
	m_labelGifVentExt ->show();
	if (m_threadVitesseVentil ->tempVitExtFr == true) {
	    m_labelGifVitesse1Ext ->hide();
	    m_labelGifVitesse2Ext ->show();
	} else {
	    m_labelGifVitesse2Ext ->hide();
	    m_labelGifVitesse1Ext ->show();
	}
    } else {
	m_labelGifVitesse1Ext ->hide();
	m_labelGifVitesse2Ext ->hide();
	m_labelGifVentExt ->hide();
    }
    if (m_threadGainable ->gifFroid == true) {
	m_labelGifFroid ->show();
    } else {
	m_labelGifFroid ->hide();
    }
}

void Thread::affichageChauffage()
{
    m_label ->setPixmap(QPixmap("/home/ludo/Qt/test/build/images/chauffage.jpg"));
    m_label ->show();
    
    if (m_threadGainable ->gifVentilInt == true) {
	m_threadVitesseVentil ->hysteresisTempVitesseIntChauf();
	m_labelGifVentInt ->show();
	if (m_threadVitesseVentil ->tempVitIntCh == true) {
	    m_labelGifVitesse1Int ->hide();
	    m_labelGifVitesse4Int ->show();
	} else {
	    m_labelGifVitesse4Int ->hide();
	    m_labelGifVitesse1Int ->show();
	}
    } else {
	m_labelGifVitesse1Int ->hide();
	m_labelGifVitesse4Int ->hide();
	m_labelGifVentInt ->hide();
    }
    if (m_threadGainable ->gifVentilExt == true) {
	m_threadVitesseVentil ->hysteresisTempVitesseExtChauf();
	m_labelGifVentExt ->show();
	if (m_threadVitesseVentil ->tempVitExtCh == true) {
	    m_labelGifVitesse2Ext ->hide();
	    m_labelGifVitesse1Ext ->show();
	} else {
	    m_labelGifVitesse1Ext ->hide();
	    m_labelGifVitesse2Ext ->show();
	}
    } else {
	m_labelGifVitesse1Ext ->hide();
	m_labelGifVitesse2Ext ->hide();
	m_labelGifVentExt ->hide();
    }
    if (m_threadGainable ->gifChauffage == true) {
	m_labelGifChauffe ->show();
    } else {
	m_labelGifChauffe ->hide();
    }
}

void Thread::run()
{
    while (1) {
	
	qDebug() << "run thread";
	
	qDebug() << "modeFroid" << m_threadGainable ->modeFroid;
	qDebug() << "modeChauffage" << m_threadGainable ->modeChauffage;
	
	m_threadSondes ->lectureSondes();
	m_threadSondes ->lectureConsigneIntCa();
	
	m_affTemp1 ->display(m_threadSondes ->tempExtLue);
	m_affTemp2 ->display(m_threadSondes ->tempUnitExtLue);
	m_affTemp3 ->display(m_threadSondes ->tempEchExtLue);
	m_affTemp4 ->display(m_threadSondes ->tempUnitIntLue);
	m_affTemp5 ->display(m_threadSondes ->tempEchIntLue);
	
	if (departGainable == true) {
	    m_threadGainable ->gainable();
	    if (m_threadGainable ->modeFroid == true) {
		affichageFroid();
	    } else if (m_threadGainable ->modeChauffage == true) {
		affichageChauffage();
	    } else {
		effaceGifs();
		afficheLabel();
	    }
	} else {
	    stop();
	}
	    
	/*	    
	if (m_threadGainable ->gifDegivrage == true) {
	    m_labelGifDegivrage ->show();
	} else {
	    m_labelGifDegivrage ->hide();
	}
	    
	if (m_threadGainable ->gifEgouttage == true) {
	    m_labelGifEgouttage ->show();
	} else {
	    m_labelGifEgouttage ->hide();
	    m_labelGifEgouttage ->hide();
	}*/
    }
}

void Thread::stop()
{
    qDebug() << "stop";
    
    effaceGifs();
    afficheLabel();
    m_labelGifChauffe ->hide();
    m_labelGifDegivrage ->hide();
    m_labelGifEgouttage ->hide();
    
    m_threadRelais ->desactiveRelaiEteHiver();
    m_threadRelais ->desactiveTousRelais();
    m_threadGainable ->autoModeEteHiver();
}
