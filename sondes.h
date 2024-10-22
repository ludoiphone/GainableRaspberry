#ifndef SONDES_H
#define SONDES_H
#include <QtWidgets>

#include "BB_DS18B20.hpp"

class Sondes: public QWidget
{
    Q_OBJECT

public:
    Sondes();
    
    double tempExtLue;
    double tempUnitExtLue;
    double tempEchExtLue;
    double tempUnitIntLue;
    double tempEchIntLue;
    
    double consigneIntCa;
    double consigneVentIntCa;
    
    void lectureSondes();
    void lectureConsigneIntCa();

private:
    BB_DS18B20 *m_ds18b20;
};

#endif //SONDES_H
