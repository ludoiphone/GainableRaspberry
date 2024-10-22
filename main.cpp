#include "mainwindow.h"

#include <QApplication>
#include "configini.h"

Setting *m_initTemps;

int main(int argc, char *argv[])
{
    qDebug() << "main";
    
    QApplication app(argc, argv);
    QApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
    
    m_initTemps = new Setting(QString("settings/parametres.ini"), QSettings::IniFormat);
    m_initTemps ->controleFichier();
    
    MainWindow window;
    return app.exec();
}
