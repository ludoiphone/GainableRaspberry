#include "configini.h"

Setting::Setting(const QString &nomDuFichier, QSettings::Format format): QSettings(nomDuFichier, format)
{
    
}

void Setting::consignesGainableDefaut()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneEteHiver", consigneEteHiverDefaut);
    this ->setValue("ConsigneCanicule", consigneCaniculeDefaut);
    this ->setValue("ConsigneBlocageChauffage", consigneBlocChaufDefaut);
    this ->setValue("ConsigneModeDegivrageChauffage", consigneModeDegChDefaut);
    this ->setValue("ConsigneGrandeVitesseExterieurChauffage", consigneGrVitExtChDefaut);
    this ->setValue("ConsigneGrandeVitesseExterieurFroid", consigneGrVitExtFrDefaut);
    this ->setValue("ConsigneFinDegivrageChauffage", consigneFinDegChDefaut);
    this ->setValue("ConsigneDepartChauffageEnModeChauffage", consigneDepartChauffageEnChauffageDefaut);
    this ->setValue("ConsigneDepartFroidEnModeChauffage", consigneDepartFroidEnChauffageDefaut);
    this ->setValue("ConsignePetiteVitesseInterieurChauffage", consignePeVitIntChDefaut);
    this ->setValue("ConsigneDepartFroidEnModeFroid", consigneDepartFroidEnFroidDefaut);
    this ->setValue("ConsigneDepartChauffageEnModeFroid", consigneDepartChauffageEnFroidDefaut);
    this ->setValue("ConsignePetiteVitesseInterieurFroid", consignePeVitIntFrDefaut);
    this ->setValue("ConsigneDepartVentilateurInterieurChauffage", consigneDepartVentIntChDefaut);
    this ->setValue("ConsigneDegivrageFroid", consigneDegFrDefaut);
    this ->setValue("ConsigneFinDegivrageFroid", consigneFinDegFrDefaut);
    this ->endGroup();
}

void Setting::controleFichier()
{
    if (this ->childGroups().contains("Consignes")) {
        qDebug() << "Fichier Consigne OK";
    } else {
        qDebug() << "creation fichier DEFAUT ";
        consignesGainableDefaut();
    }
}

void Setting::ecritConsigneEteHiver() // ecrit consignes
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneEteHiver", consigneEteHiver);
    this ->endGroup();
}

void Setting::ecritConsigneCanicule()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneCanicule", consigneCanicule);
    this ->endGroup();
}

void Setting::ecritConsigneBlocCh()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneBlocageChauffage", consigneBlocChauf);
    this ->endGroup();
}

void Setting::ecritConsigneModeDegCh()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneModeDegivrageChauffage", consigneModeDegCh);
    this ->endGroup();
}

void Setting::ecritConsigneGrVitExtCh()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneGrandeVitesseExterieurChauffage", consigneGrVitExtCh);
    this ->endGroup();
}

void Setting::ecritConsigneGrVitExtFr()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneGrandeVitesseExterieurFroid", consigneGrVitExtFr);
    this ->endGroup();
}

void Setting::ecritConsigneFinDegCh()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneFinDegivrageChauffage", consigneFinDegCh);
    this ->endGroup();
}

void Setting::ecritConsigneDepartChauffageEnChauffage()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneDepartChauffageEnModeChauffage", consigneDepartChauffageEnChauffage);
    this ->endGroup();
}

void Setting::ecritConsigneDepartFroidEnChauffage()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneDepartFroidEnModeChauffage", consigneDepartFroidEnChauffage);
    this ->endGroup();
}

void Setting::ecritConsignePeVitIntCh()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsignePetiteVitesseInterieurChauffage", consignePeVitIntCh);
    this ->endGroup();
}

void Setting::ecritConsigneDepartFroidEnFroid()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneDepartEnModeFroid", consigneDepartFroidEnFroid);
    this ->endGroup();
}

void Setting::ecritConsigneDepartChauffageEnFroid()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneDepartChauffageEnModeFroid", consigneDepartChauffageEnFroid);
    this ->endGroup();
}

void Setting::ecritConsignePeVitIntFr()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsignePetiteVitesseInterieurFroid", consignePeVitIntFr);
    this ->endGroup();
}
void Setting::ecritConsigneDepartVentIntCh()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneDepartVentilateurInterieurChauffage", consigneDepartVentIntCh);
    this ->endGroup();
}

void Setting::ecritConsigneDegFr()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneDegivrageFroid", consigneDegFr);
    this ->endGroup();
}

void Setting::ecritConsigneFinDegFr()
{
    this ->beginGroup("Consignes");
    this ->setValue("ConsigneFinDegivrageFroid", consigneFinDegFr);
    this ->endGroup();
}

void Setting::lireConsignesGainable() // lire consignes
{
    this ->beginGroup("Consignes");
    consigneEteHiver = this ->value("ConsigneEteHiver").toDouble();
    consigneCanicule = this ->value("ConsigneCanicule").toDouble();
    consigneBlocChauf = this ->value("ConsigneBlocageChauffage").toDouble();
    consigneModeDegCh = this ->value("ConsigneModeDegivrageChauffage").toDouble();
    consigneGrVitExtCh = this ->value("ConsigneGrandeVitesseExterieurChauffage").toDouble();
    consigneGrVitExtFr = this ->value("ConsigneGrandeVitesseExterieurFroid").toDouble();
    consigneFinDegCh = this ->value("ConsigneFinDegivrageChauffage").toDouble();
    consigneDepartChauffageEnChauffage = this ->value("ConsigneDepartChauffageEnModeChauffage").toDouble();
    consigneDepartFroidEnChauffage = this ->value("ConsigneDepartFroidEnModeChauffage").toDouble();
    consignePeVitIntCh = this ->value("ConsignePetiteVitesseInterieurChauffage").toDouble();
    consigneDepartFroidEnFroid = this ->value("ConsigneDepartFroidEnModeFroid").toDouble();
    consigneDepartChauffageEnFroid = this ->value("ConsigneDepartChauffageEnModeFroid").toDouble();
    consignePeVitIntFr = this ->value("ConsignePetiteVitesseInterieurFroid").toDouble();
    consigneDepartVentIntCh = this ->value("ConsigneDepartVentilateurInterieurChauffage").toDouble();
    consigneDegFr = this ->value("ConsigneDegivrageFroid").toDouble();
    consigneFinDegFr = this ->value("ConsigneFinDegivrageFroid").toDouble();
    this ->endGroup();
}
