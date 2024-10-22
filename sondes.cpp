#include "sondes.h"

#include "gpioPin.hpp"
#include <QtMath>
#include <QDebug>

const int DS_Pin = 4;

Sondes::Sondes()
{
    pinMode(DS_Pin,OPENDRAIN_PULLUP);
    m_ds18b20 = new BB_DS18B20(gpioline[DS_Pin]);
}

void Sondes::lectureSondes()
{	
    m_ds18b20 ->GlobalStartConversion();
    
    if (m_ds18b20 ->ReadSensor(0x073CE1E380974428)) {
		//m_ds18b20 ->temperature = qFloor(10*m_ds18b20 ->temperature+0.5)/10;
        tempExtLue = m_ds18b20 ->temperature;
    }
    if (m_ds18b20 ->ReadSensor(0x0D3CE1E38060EC28)) {
		//m_ds18b20 ->temperature = qFloor(10*m_ds18b20 ->temperature+0.5)/10;
        tempUnitExtLue = m_ds18b20 ->temperature;
    }
    if (m_ds18b20 ->ReadSensor(0x993CE1E380483528)) {
		//m_ds18b20 ->temperature = qFloor(10*m_ds18b20 ->temperature+0.5)/10;
        tempEchExtLue = m_ds18b20 ->temperature;
    }
    if (m_ds18b20 ->ReadSensor(0xAE3CE1E380125128)) {
		//m_ds18b20 ->temperature = qFloor(10*m_ds18b20 ->temperature+0.5)/10;
        tempUnitIntLue = m_ds18b20 ->temperature;
    }
    if (m_ds18b20 ->ReadSensor(0xEA3CE1E3805E9F28)) {
		//m_ds18b20 ->temperature = qFloor(10*m_ds18b20 ->temperature+0.5)/10;
        tempEchIntLue = m_ds18b20 ->temperature;
    }
    // a faire pour les autres capteurs et peut être utiliser
    //  le fichier config contenant l'identification des capteurs.

}

void Sondes::lectureConsigneIntCa()
{
    consigneIntCa = tempExtLue - 6;
    consigneVentIntCa = consigneIntCa + 2;
}
