#include "gainable.h"

#include "gpioPin.hpp"
#include <ctime>

const int thermostats = 17; 
const int capteurFiltre = 27;

Gainable::Gainable()
{
    qDebug() << "Gainable";
    
    pinMode (capteurFiltre, INPUT_PULLUP);
    pinMode (thermostats, INPUT_PULLUP);
    
	time_t secondes = time(NULL);
    time_t rawtime;
    time ( & rawtime);
    qDebug() << ctime ( & rawtime);
    
    m_consignesGainable = new Setting(QString("settings/parametres.ini"), QSettings::IniFormat);
    
    m_sondesGainable = new Sondes();
  
    m_relais = new Relais();
}

void Gainable::autoModeEteHiver()
{
	if (time(NULL) - departAutoMode >= autoMode) {
        etatsGainable = DEPART;
        modeFroid = false;
        modeChauffage = false;
        modeCanicule = false;
        gifVentilExt = false;
        gifVentilInt = false;
        gifFroid = false;
        gifChauffage = false;
        gifDegivrage = false;
        gifEgouttage = false;
    }
}

void Gainable::filtre()
{
	if (nettoyageFiltre >= tempsNettoyageFiltre) {
        qDebug() << "*** !!!Faire Nettoyage du Filtre!!! ***" << nettoyageFiltre;
        if (nettoyageFiltre >= tempsArretProgramme) {
            etatsGainable = FILTRE;
        }
    }
}

void Gainable::gainable()
{
    qDebug() << "gainable";
    
    m_sondesGainable ->lectureSondes();
    
    m_consignesGainable ->lireConsignesGainable();
    
	switch (etatsGainable) {
		
		case DEPART:
		
		qDebug() << "DEPART";

        departAutoMode = time(NULL);
        departTempoVentilation = time(NULL);
        filtre();
        
        if (m_sondesGainable ->tempExtLue < m_consignesGainable ->consigneEteHiver) { // si la temperature ext(nord moyenne regionnale) est inferieur as 13.5°C
            departTempoChauffage = time(NULL);
            m_relais ->activeRelaiEteHiver(); // relai étéHiver
            etatsGainable = COMMANDE_CHAUFFAGE; // mode chauffage
        } else if (m_sondesGainable ->tempExtLue < m_consignesGainable ->consigneCanicule) { // si la temperature ext(nord) est inferieur as 30°C
            canicule = false;
            departTempoFroid = time(NULL);
            m_relais ->desactiveRelaiEteHiver();
            etatsGainable = COMMANDE_FROID; // mode froid
        } else { // si non 
            canicule = true;
            departTempoCanicule = time(NULL);
            etatsGainable = COMMANDE_CANICULE; // mode canicule
        }

        break;
        
        case COMMANDE_FROID:
    
        qDebug() << "COMMANDE_FROID";
        
        if (digitalRead (thermostats) == 0) { // si un des thermostats est a 1 
            modeFroid = true;
            if (time(NULL) - departTempoVentilation >= tempoVentilation) {
                if (time(NULL) - departTempoFroid >= tempoFroid) { // tempo de 3 minutes
                    if (m_sondesGainable ->tempUnitIntLue >= m_consignesGainable ->consigneDepartFroidEnFroid) { // si la temperature unite interieur est supperieur de 23.5°C (reglable) 
                        departTempoV4V = time(NULL); // enregistre temps pour la tempo de la vanne 4 voies
                        etatsGainable = TEMPO_V4V; // passe en prodution de froid
                    } else if (m_sondesGainable ->tempUnitIntLue <= m_consignesGainable ->consigneDepartFroidEnChauffage) { // si non si la temperature unite interieur est inferieur as 22°C
                        departTempoComp = time(NULL); // enregistre temps pour la tempo chauffage
                        m_relais ->activeRelaiEteHiver();//relai étéHiver (mode chauffage)
                        modeFroid = false;
                        modeChauffage = true;
                        etatsGainable = TEMPO_COMPRESSEUR_CHAUFFAGE; // passe en mode chauffage
                    } else if (m_sondesGainable ->tempExtLue >= m_consignesGainable ->consigneCanicule) { // si non //////////////////////////////////////////////////////////////////
                        modeFroid = false;
                        modeCanicule = true;
                        etatsGainable = COMMANDE_CANICULE;
                    } else {
                        departTempoFroid = time(NULL); // enregistre temps pour relancé la tempo froid
                    }
                } else { // si non
                    m_relais ->activeRelaisVentilationInt(); // active les relais ventilateur interieur en grande vitesse
                    gifVentilInt = true;
                    qDebug() << "VENTILATION";
                }
            } else {
                departTempoFroid = time(NULL);
            }
        } else { // si non 
            departTempoVentilation = time(NULL);
            m_relais ->desactiveTousRelais(); // desactive tous les relais
            autoModeEteHiver(); // utilise la fonction auto hiver
        }
        
        break;

        case TEMPO_V4V:
        
        qDebug() << "TEMPO_V4V";
        
        //gifVentilExt = true;

        if (digitalRead (thermostats) == 1) {
            etatsGainable = DEPART;
        } else if (time(NULL) - departTempoV4V >= tempoV4V) {
            departTempoComp = time(NULL);
            m_relais ->activeRelaiV4V();
            //compteurV4V++;
            etatsGainable = TEMPO_COMPRESSEUR_FROID;
        } else {
            m_relais ->activeRelaisVentFroid();
            gifVentilExt = true;
        }
        
        break;

        case TEMPO_COMPRESSEUR_FROID:
        
        qDebug() << "TEMPO_COMPRESSEUR_FROID";

        if (digitalRead (thermostats) == 1) {
            etatsGainable = DEPART;
        } else if (time(NULL) - departTempoComp >= tempoComp) {
            m_relais ->activeRelaiComp();//digitalWrite (relaiComp, LOW);
            departTempoDegFr = time(NULL);
            departChronoFiltre = time(NULL);
            gifFroid = true;
            //compteurComp++;
            etatsGainable = TEMPO_DEGIVRAGE_FROID;
        } else {
            m_relais ->activeRelaisVentFroid();
        }

        break;

        case TEMPO_DEGIVRAGE_FROID:
        
        qDebug() << "TEMPO_DEGIVRAGE_FROID";
    
        if (digitalRead (thermostats) == 1) {
            finChronoFiltre = time(NULL);
            nettoyageFiltre = (finChronoFiltre - departChronoFiltre) + nettoyageFiltre;
            m_relais ->desactiveTousRelais();
            etatsGainable = DEPART;
        } else if (time(NULL) - departTempoDegFr >= tempoDegFr) { // tempo 20 minutes
            if (m_sondesGainable ->tempEchIntLue < m_consignesGainable ->consigneDegFr) { // si temperature echangeur interieur est inferieur as -3°C 
                m_relais ->forceVentIntDegFr = true; // ventilation interieur grande vitesse 
                if (time(NULL) - departTempoTempDegFr >= tempoTempDegFr) { // tempo 2 minutes
                    if (m_sondesGainable ->tempEchIntLue < m_consignesGainable ->consigneDegFr) { // si la temperature echangeur est toujours a -3°C 
                        finChronoFiltre = time(NULL);
                        nettoyageFiltre = (finChronoFiltre - departChronoFiltre) + nettoyageFiltre;
                        m_relais ->forceVentIntDegFr = false;
                        if (canicule == true) {
                            //compteurDegCa++;
                        } else {
                            //compteurDegFr++;
                        }
                        etatsGainable = DEGIVRAGE_FROID; // passe en degivrage
                    }
                } else {
                    m_relais ->activeRelaisVentFroid();
                }
            } else {
                departTempoTempDegFr = time(NULL);
                m_relais ->forceVentIntDegFr = false;
                m_relais ->activeRelaisVentFroid();
            }
        } else {
            departTempoTempDegFr = time(NULL);
            m_relais ->activeRelaisVentFroid();
            qDebug() << "activeRelaisVenFroid";
        }
    
        break;

        case DEGIVRAGE_FROID:
        
        qDebug() << "DEGIVRAGE_FROID";

        if (m_sondesGainable ->tempEchIntLue >= m_consignesGainable ->consigneFinDegFr) {
            departTempoEgouttage = time(NULL);
            if (canicule == true) {
                //compteurEgouttageCa++;
            } else {
                //compteurEgouttageFr++;
            }
            gifDegivrage = false;
            etatsGainable = EGOUTTAGE_FROID;
        } else {
            gifVentilExt = false;
            gifVentilInt = false;
            gifFroid = false;
            gifDegivrage = true;
            m_relais ->desactiveTousRelais();
        }

        break;

        case EGOUTTAGE_FROID:
    
        qDebug() << "EGOUTTAGE_FROID";

        if (time(NULL) - departTempoEgouttage >= tempoEgouttage) {
            departTempoFinEgouttage = time(NULL);
            if (canicule == true) {
                //compteurFinEgouttageCa++;
            } else {
                //compteurFinEgouttageFr++;
             }
             etatsGainable = FIN_EGOUTTAGE_FROID;
        } else {
            gifEgouttage = true;
            m_relais ->activeRelaisVentEgouttageFr();
        }

        break;

        case FIN_EGOUTTAGE_FROID:
        
        qDebug() << "FIN_EGOUTTAGE_FROID";

        if (time(NULL) - departTempoFinEgouttage >= tempoFinEgouttage) {
            gifEgouttage = false;
            etatsGainable = DEPART;
        } else {
            m_relais ->desactiveTousRelais();
        }

        break;

        case COMMANDE_CHAUFFAGE:
        
        qDebug() << "COMMANDE_CHAUFFAGE";

        if (digitalRead (thermostats) == 0) { // si un des thermostat est as 1
            modeChauffage = true;
            if (time(NULL) - departTempoVentilation >= tempoVentilation) {
                if (time(NULL) - departTempoChauffage >= tempoChauffage) { // tempo de 3 minutes
                    if (m_sondesGainable ->tempUnitIntLue <= m_consignesGainable ->consigneDepartChauffageEnChauffage) { // si la temperature unite interieur est inferieur a 22°C
                        if (m_sondesGainable ->tempUnitExtLue <= m_consignesGainable ->consigneBlocChauf) { // si la temperature unite exterieur est inferieur a 11°C
                            departTempoComp = time(NULL);
                            m_relais ->desactiveRelaisVentIntCh();
                            etatsGainable = TEMPO_COMPRESSEUR_CHAUFFAGE; // production de chauffage
                        } else {
                            departTempoChauffage = time(NULL);
                        }
                    } else if (m_sondesGainable ->tempUnitIntLue >= m_consignesGainable ->consigneDepartFroidEnChauffage) { // si non si la temperature unite interieur est superieur a 24°C
                        departTempoFroid = time(NULL); // enregistre temps pour la tempo froid
                        m_relais ->desactiveRelaiEteHiver(); // relai étéHiver mode froid
                        modeChauffage = false;
                        modeFroid = true;
                        etatsGainable = COMMANDE_FROID; // passe en froid///////////////////////////////////////////////////////////////////////
                    } else {
                        departTempoChauffage = time(NULL);
                    }
                } else {
                    m_relais ->activeRelaisVentilationInt(); // active les relais ventilateur interieur en grande vitesse
                    gifVentilInt = true;
                    qDebug() << "VENTILATION";
                }
            } else {
                departTempoChauffage = time(NULL);
            }
        } else {
            departTempoVentilation = time(NULL);
            m_relais ->desactiveTousRelais();
            autoModeEteHiver();
        }

        break;

        case TEMPO_COMPRESSEUR_CHAUFFAGE:
    
        qDebug() << "TEMPO_COMPRESSEUR_CHAUFFAGE";

        if (digitalRead (thermostats) == 1) {
            etatsGainable = DEPART;
        } else if (time(NULL) - departTempoComp >= tempoComp) {
            departChronoFiltre = time(NULL);
            departTempoDegCh = time(NULL);
            //compteurCompCh++;
            etatsGainable = TEMPO_DEGIVRAGE;
         } else {
            m_relais ->activeRelaisVentExtChauffage();
            m_relais ->desactiveRelaisVentIntCh();
            gifVentilExt = true;
            gifVentilInt = false;
        }

        break;

        case TEMPO_DEGIVRAGE:
        
        qDebug() << "TEMPO_DEGIVRAGE";
    
        if (digitalRead (thermostats) == 1) {
            finChronoFiltre = time(NULL);
            nettoyageFiltre = (finChronoFiltre - departChronoFiltre) + nettoyageFiltre;
            etatsGainable = DEPART;
        } else if (time(NULL) - departTempoDegCh >= tempoDegCh) {
            etatsGainable = MODE_DEGIVRAGE;
        } else {
            m_relais ->activeRelaiComp();
            m_relais ->activeRelaisVentExtChauffage();
            gifChauffage = true;
            if (m_sondesGainable ->tempEchIntLue >= m_consignesGainable ->consigneDepartVentIntCh) {
                m_relais ->activeRelaisVitesseVentIntChauffage();
                gifVentilInt = true;
            }
        }
        
        break;

        case MODE_DEGIVRAGE:
        
        qDebug() << "MODE_DEGIVRAGE";
    
        if (m_sondesGainable ->tempUnitExtLue <= m_consignesGainable ->consigneModeDegCh) {
            finChronoFiltre = time(NULL);
            nettoyageFiltre = (finChronoFiltre - departChronoFiltre) + nettoyageFiltre;
            departTempoV4VDegElec = time(NULL);
            //compteurDegElec++;
            etatsGainable = TEMPO_DEG_V4V;
         } else {
            finChronoFiltre = time(NULL);
            nettoyageFiltre = (finChronoFiltre - departChronoFiltre) + nettoyageFiltre;
            departTempoDegNat = time(NULL);
            //compteurDegNat++;
            etatsGainable = DEGIVRAGE_NATUREL;
        }
    
        break;

        case DEGIVRAGE_NATUREL:
    
        qDebug() << "DEGIVRAGE_NATUREL";
    
        if (time(NULL) - departTempoDegNat >= tempoDegNat) {
            departTempoEgouttage = time(NULL);
            //compteurEgouttageNat++;
            gifDegivrage = false;
            etatsGainable = EGOUTTAGE_NATUREL;
        } else {
            gifDegivrage = true;
            m_relais ->desactiveTousRelais();
        }

        break;

        case EGOUTTAGE_NATUREL:
    
        qDebug() << "EGOUTTAGE_NATUREL";

        if (time(NULL) - departTempoEgouttage >= tempoEgouttage) {
            departTempoFinEgouttage = time(NULL);
            //compteurFinEgouttageNat++;
            etatsGainable = FIN_EGOUTTAGE_NATUREL;
        } else {
            gifEgouttage = true;
            m_relais ->activeRelaisVentEgouttageCh();
        }

        break;

        case FIN_EGOUTTAGE_NATUREL:
    
        qDebug() << "FIN_EGOUTTAGE_NATUREL";
    
        if (time(NULL) - departTempoFinEgouttage >= tempoFinEgouttage) {
            gifEgouttage = false;
            etatsGainable = DEPART;
        } else {
            m_relais ->desactiveTousRelais();
        }

        break;

        case TEMPO_DEG_V4V:
        
        qDebug() << "TEMPO_DEG_V4V";
    
        if (time(NULL) - departTempoV4VDegElec >= tempoV4VDegElec) {
            departTempoCompDegElec = time(NULL);
            //compteurV4VDegElec++;
            etatsGainable = TEMPO_DEG_COMPRESSEUR;
        } else {
            gifDegivrage = true;
            m_relais ->desactiveTousRelais();
        }

        break;

        case TEMPO_DEG_COMPRESSEUR:
        
        qDebug() << "TEMPO_DEG_COMPRESSEUR";
    
        if (time(NULL) - departTempoCompDegElec >= tempoCompDegElec) {
            departTempoTempDegElec = time(NULL);
            //compteurCompDegElec++;
            etatsGainable = DEGIVRAGE_ELECTRIC;
        } else {
            m_relais ->activeRelaiV4V();
        }

        break;

        case DEGIVRAGE_ELECTRIC:
    
        qDebug() << "DEGIVRAGE_ELECTRIC";
    
        if (m_sondesGainable ->tempEchExtLue >= m_consignesGainable ->consigneFinDegCh) {
            departTempoEgouttage = time(NULL);
            //compteurEgouttageCh++;
            //compteurFinDegTemperature++;
            gifDegivrage = false;
            etatsGainable = EGOUTTAGE_CHAUFFAGE;
        } else if (time(NULL) - departTempoTempDegElec >= tempoTempDegElec) {
            departTempoEgouttage = time(NULL);
            //compteurEgouttageCh++;
            //compteurFinDegTemps++;
            gifDegivrage = false;
            etatsGainable = EGOUTTAGE_CHAUFFAGE;
        } else {
            gifDegivrage = true;
            m_relais ->activeRelaiComp();
        }

        break;

        case EGOUTTAGE_CHAUFFAGE:
    
        qDebug() << "EGOUTTAGE_CHAUFFAGE";
    
        if (time(NULL) - departTempoEgouttage >= tempoEgouttage) {
            departTempoFinEgouttage = time(NULL);
            //compteurFinEgouttageCh++;
            etatsGainable = FIN_EGOUTTAGE_CHAUFFAGE;
        } else {
            gifEgouttage = true;
            m_relais ->desactiveTousRelais();
        }
        break;

        case FIN_EGOUTTAGE_CHAUFFAGE:
    
        qDebug() << "FIN_EGOUTTAGE_CHAUFFAGE";
    
        if (time(NULL) - departTempoFinEgouttage >= tempoFinEgouttage) {
            m_relais ->desactiveTousRelais();
            gifEgouttage = false;
            etatsGainable = DEPART;
        } else {
            m_relais ->activeRelaisVentEgouttageCh();
        }

        break;

        case COMMANDE_CANICULE:
    
        qDebug() << "COMMANDE_CANICULE";
    
        if (digitalRead (thermostats) == 0) {
            modeCanicule = true;
            if (time(NULL) - departTempoVentilation >= tempoVentilation) {
                if (time(NULL) - departTempoFroid >= tempoFroid) { // tempo de 3 minutes
                    if (m_sondesGainable ->tempUnitIntLue >= 26) {//m_consDelta ->consigneVentIntCa) {///////////////////////////////////::
                        departTempoV4V = time(NULL);
                        etatsGainable = TEMPO_V4V_CANICULE;
                    } else {
                        departTempoFroid = time(NULL);
                    }
                } else {
                    m_relais ->activeRelaisVentilationInt();
                }
            } else {
                departTempoCanicule = time(NULL);
            }
        } else {
            departTempoV4V = time(NULL);
            m_relais ->desactiveTousRelais();
            autoModeEteHiver();
        } 

        break;

        case TEMPO_V4V_CANICULE:
    
        qDebug() << "TEMPO_V4V_CANICULE";
    
        if (digitalRead (thermostats) == 1) {
            etatsGainable = DEPART;
        } else if (time(NULL) - departTempoV4V >= tempoV4V) {
            departTempoComp = time(NULL);
            m_relais ->activeRelaiV4V();
            //compteurV4VCa++;
            etatsGainable = TEMPO_COMPRESSEUR_CANICULE;
        } else {
            m_relais ->activeRelaisVentIntCanicule(); 
        }

        break;

        case TEMPO_COMPRESSEUR_CANICULE:
    
        qDebug() << "TEMPO_COMPRESSEUR_CANICULE";
    
        if (digitalRead (thermostats) == 1) {
            etatsGainable = DEPART;
        } else if (time(NULL) - departTempoComp >= tempoComp) {
            departChronoFiltre = time(NULL);
            departTempoDegFr = time(NULL);
            //compteurCompCa++;
            m_relais ->activeRelaiComp();
            etatsGainable = TEMPO_DEGIVRAGE_CANICULE;
        } else {
            m_relais ->activeRelaisVentExtCanicule();
            m_relais ->activeRelaisVentIntCanicule();
        }

        break;
    
        case TEMPO_DEGIVRAGE_CANICULE:
    
        qDebug() << "TEMPO_DEGIVRAGE_CANICULE";

        if (digitalRead (thermostats) == 1) {
            finChronoFiltre = time(NULL);
            nettoyageFiltre = (finChronoFiltre - departChronoFiltre) + nettoyageFiltre;
            m_relais ->desactiveTousRelais();
            etatsGainable = DEPART;
        } else if (time(NULL) - departTempoDegFr >= tempoDegFr) { // tempo 20 minutes
            if (m_sondesGainable ->tempEchIntLue < m_consignesGainable ->consigneDegFr) { // si temperature est inferieur a -3°C
                m_relais ->forceVentIntDegFr = true; // force grande vitesse
                if (time(NULL) - departTempoTempDegFr >= tempoTempDegFr) { // tempo de 1 minute (a regler)
                    if (m_sondesGainable ->tempEchIntLue < m_consignesGainable ->consigneDegFr) { // si temperature est toujours inferieur a -3°C on degivre
                        finChronoFiltre = time(NULL);
                        nettoyageFiltre = (finChronoFiltre - departChronoFiltre) + nettoyageFiltre;
                        m_relais ->forceVentIntDegFr = false;
                        etatsGainable = DEGIVRAGE_FROID;
                    }
                } else {
                    m_relais ->activeRelaisVentExtCanicule();
                    m_relais ->activeRelaisVentIntCanicule();
                }
            } else {
                departTempoTempDegFr = time(NULL);
                m_relais ->forceVentIntDegFr = false;
                m_relais ->activeRelaisVentExtCanicule();
                m_relais ->activeRelaisVentIntCanicule();
            }
        } else {
            departTempoTempDegFr = time(NULL);
            m_relais ->activeRelaisVentExtCanicule();
            m_relais ->activeRelaisVentIntCanicule();
        }
    
        break;

        case FILTRE:
        
        qDebug() << "FILTRE";
    
        m_relais ->desactiveTousRelais();
        if (digitalRead (capteurFiltre) == 0) {
            nettoyageFiltre = 0;
            //compteurArretProgramme++,
            entretienFiltre = false;
            etatsGainable = DEPART;
        } else {
            entretienFiltre = true;
        }
    
        break;
    }
}

