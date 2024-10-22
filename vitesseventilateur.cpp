#include "vitesseventilateur.h"

VitesseVentil::VitesseVentil()
{
	m_vitesseCons = new Setting(QString("settings/parametres.ini"), QSettings::IniFormat);
	
	m_sondesVitesses = new Sondes();
}

void VitesseVentil::hysteresisTempVitesseIntCa()
{
    m_sondesVitesses ->lectureSondes();
    m_sondesVitesses ->lectureConsigneIntCa();
    
    if (tempVitIntCa) {
        tempVitIntCa = m_sondesVitesses ->tempUnitIntLue >= (m_sondesVitesses ->consigneVentIntCa - hysteresis);
    } else {
        tempVitIntCa = m_sondesVitesses ->tempUnitIntLue >= (m_sondesVitesses ->consigneVentIntCa + hysteresis);
        }
}

void VitesseVentil::hysteresisTempVitesseExtFroid()
{
    m_sondesVitesses ->lectureSondes();
    m_vitesseCons ->lireConsignesGainable();
    
    if (tempVitExtFr) {
        tempVitExtFr = m_sondesVitesses ->tempUnitExtLue >= (m_vitesseCons ->consigneGrVitExtFr - hysteresisVentExtFr);
    } else {
        tempVitExtFr = m_sondesVitesses ->tempUnitExtLue >= (m_vitesseCons ->consigneGrVitExtFr);
    }
}

void VitesseVentil::hysteresisTempVitesseIntFroid()
{
    m_sondesVitesses ->lectureSondes();
    m_vitesseCons ->lireConsignesGainable();
    
    if (tempVitIntFr) {
        tempVitIntFr = m_sondesVitesses ->tempUnitIntLue >= (m_vitesseCons ->consignePeVitIntFr - hysteresis);
    } else {
        tempVitIntFr = m_sondesVitesses ->tempUnitIntLue >= (m_vitesseCons ->consignePeVitIntFr + hysteresis);
    }
}

void VitesseVentil::hysteresisTempVitesseIntChauf()
{
    m_sondesVitesses ->lectureSondes();
    m_vitesseCons ->lireConsignesGainable();
    
    if (tempVitIntCh) {
        tempVitIntCh = m_sondesVitesses ->tempUnitIntLue <= (m_vitesseCons ->consignePeVitIntCh + hysteresis);
    } else {
        tempVitIntCh = m_sondesVitesses ->tempUnitIntLue <= (m_vitesseCons ->consignePeVitIntCh - hysteresis);
    }
}

void VitesseVentil::hysteresisTempVitesseExtChauf()
{
    m_sondesVitesses ->lectureSondes();
    m_vitesseCons ->lireConsignesGainable();
    
    if (tempVitExtCh) {
        tempVitExtCh = m_sondesVitesses ->tempUnitExtLue >= (m_vitesseCons ->consigneGrVitExtCh - hysteresis);
    } else {
        tempVitExtCh = m_sondesVitesses ->tempUnitExtLue >= (m_vitesseCons ->consigneGrVitExtCh + hysteresis);
    }
}
