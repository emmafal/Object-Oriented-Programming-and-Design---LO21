#include "SettingsPartie.h"
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QSizePolicy>
#include <QDebug>

SettingsPartie::SettingsPartie(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Parametres du jeu");
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QPushButton *quitterbtn = new QPushButton("Quitter", this);
    QPushButton *returnbtn = new QPushButton("Retour", this);
    QLabel *labelEntier = new QLabel("Entrez un nombre entier (0 à 99) pour la quantité de retours possible :", this);
    layout->addWidget(labelEntier);

    saisieEntier = new QLineEdit(this);
    saisieEntier->setText("0");
    QIntValidator *validator = new QIntValidator(0, 99, this);
    saisieEntier->setValidator(validator);
    layout->addWidget(saisieEntier);

    moustique = new QCheckBox("Moustique", this);
    coccinelle = new QCheckBox("Coccinelle", this);

    QPushButton *validerBtn = new QPushButton("Valider", this);

    layout ->addWidget(moustique);
    layout->addWidget(coccinelle);
    layout->addWidget(validerBtn);
    layout->addWidget(quitterbtn);
    layout->addWidget(returnbtn);

    connect(quitterbtn, &QPushButton::clicked, this, &SettingsPartie::onQuitClicked);
    connect(returnbtn, &QPushButton::clicked, this, &SettingsPartie::onReturnClicked);
    connect(validerBtn, &QPushButton::clicked, this, &SettingsPartie::onValidateButtonClicked);
}

void SettingsPartie::onReturnClicked() {
    qDebug() << "Retour cliqué";
    emit returnClicked();
}

void SettingsPartie::onQuitClicked() {
    qDebug() << "Quitter cliqué!";
    qApp->quit();
}

void SettingsPartie::onValidateButtonClicked() {
    QMap<QString, bool> insectSelection;
    if (moustique->isChecked()) {
        qDebug() << "moustique coche";
    }
    if (coccinelle->isChecked()) {
        qDebug() << "coccinelleCheckbox coche";
    }

    insectSelection["moustique"] = moustique->isChecked();
    insectSelection["coccinelle"] = coccinelle->isChecked();

    emit validatedInsectSelection(insectSelection);
    emit validerClicked();
}

std::string SettingsPartie::getJoueur1() {
    return this->joueur1Name.toStdString();
}

std::string SettingsPartie::getJoueur2() {
    return this->joueur2Name.toStdString();
}
