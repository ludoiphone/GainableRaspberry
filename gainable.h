#ifndef GAINABLE_H
#define GAINABLE_H
#include <QtWidgets>

#include "sondes.h"
#include "configini.h"
#include "relais.h"

class Gainable: public QWidget
{
    Q_OBJECT
	
public:
    Gainable();
    
    bool modeFroid = false;
    bool modeChauffage = false;
    bool modeCanicule = false;
    
    bool gifChauffage = false;
    bool gifFroid = false;
    bool gifDegivrage = false;
    bool gifEgouttage = false;
    
    bool gifVentilExt = false;
    bool gifVentilInt = false;
    
    void autoModeEteHiver();
    
    void gainable();

private:
    Sondes *m_sondesGainable;
    
    Setting *m_consignesGainable;
    
    Relais *m_relais;
    
    unsigned long long departAutoMode;
    unsigned short autoMode = 1; // 10 secondes
    unsigned long long departTempoVentilation;
    unsigned short tempoVentilation = 5; // 5 secondes
    unsigned long long departTempoFroid;
    unsigned short tempoFroid = 30;//180; // 3 minutes
    unsigned long long departTempoV4V;
    unsigned short tempoV4V = 4.5; // 45 secondes
    unsigned long long departTempoComp;
    unsigned short tempoComp = 9; // 1 minute 30 secondes
    unsigned long long departTempoDegFr;
    unsigned short tempoDegFr = 120; // 20 minutes
    unsigned long long departTempoTempDegFr;
    unsigned short tempoTempDegFr = 12; // 2 minutes
    unsigned long long departTempoChauffage;
    unsigned short tempoChauffage = 30;//180; // 3 minutes
    unsigned long long departTempoCompDegElec;
    unsigned short tempoCompDegElec = 6.0; // 1 minutes
    unsigned long long departTempoV4VDegElec;
    unsigned short tempoV4VDegElec = 6.0; // 1 minutes
    unsigned long long departTempoTempDegElec;
    unsigned short tempoTempDegElec = 30; // 5 minutes
    unsigned long long departTempoDegCh;
    unsigned short tempoDegCh = 270; // 45 minutes
    unsigned long long departTempoDegNat;
    unsigned short tempoDegNat = 60; // 10 minutes
    unsigned long long departTempoEgouttage;
    unsigned short tempoEgouttage = 30; // 5 minutes
    unsigned long long departTempoFinEgouttage;
    unsigned short tempoFinEgouttage = 18; // 3 minutes
    unsigned long long departTempoCanicule;
    unsigned short tempoCanicule = 18; // 3 minutes

    unsigned long long nettoyageFiltre = 0; //////////// a enregistrer dans setting configini /////////////////
    unsigned long long departChronoFiltre;
    unsigned long long finChronoFiltre;
    unsigned long long tempsNettoyageFiltre = 1820000; // 21 jours  alerte nettoyage filtre
    unsigned long long tempsArretProgramme = 2679000; // 1 mois arret programme par manque d'entretien filtre
    
    bool canicule = false;
    bool entretienFiltre = false;
    
    enum
    {
		DEPART,
        COMMANDE_FROID,
        TEMPO_V4V,
        TEMPO_COMPRESSEUR_FROID,
        TEMPO_DEGIVRAGE_FROID,
        DEGIVRAGE_FROID,
        EGOUTTAGE_FROID,
        FIN_EGOUTTAGE_FROID,
        COMMANDE_CHAUFFAGE,
        TEMPO_COMPRESSEUR_CHAUFFAGE,
        TEMPO_DEGIVRAGE,
        MODE_DEGIVRAGE,
        DEGIVRAGE_NATUREL,
        EGOUTTAGE_NATUREL,
        FIN_EGOUTTAGE_NATUREL,
        TEMPO_DEG_V4V,
        TEMPO_DEG_COMPRESSEUR,
        DEGIVRAGE_ELECTRIC,
        EGOUTTAGE_CHAUFFAGE,
        FIN_EGOUTTAGE_CHAUFFAGE,
        COMMANDE_CANICULE,
        TEMPO_V4V_CANICULE,
        TEMPO_COMPRESSEUR_CANICULE,
        TEMPO_DEGIVRAGE_CANICULE,
        FILTRE,
    } etatsGainable = DEPART;
    
    void filtre();

	
	
};

#endif // GAINABLE_H
