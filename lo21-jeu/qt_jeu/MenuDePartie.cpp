#include "MenuDePartie.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QSizePolicy>
#include <QDebug>

MenuDePartie::MenuDePartie(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QPushButton *continuebtn = new QPushButton("Continuer la partie", this);
    QPushButton *abandonnerbtn = new QPushButton("Abandonner la partie", this);
    QPushButton *returnbtn = new QPushButton("Retour", this);
    QPushButton *quitterbtn = new QPushButton("Quitter", this);

    layout->addWidget(continuebtn);
    layout->addWidget(abandonnerbtn);
    layout->addWidget(returnbtn);
    layout->addWidget(quitterbtn);

    connect(continuebtn, &QPushButton::clicked, this, &MenuDePartie::onContinuerClicked);
    connect(abandonnerbtn, &QPushButton::clicked, this, &MenuDePartie::onAbandonnerClicked);
    connect(quitterbtn, &QPushButton::clicked, this, &MenuDePartie::onQuitClicked);
    connect(returnbtn, &QPushButton::clicked, this, &MenuDePartie::onReturnClicked);

}

void MenuDePartie::onContinuerClicked() {
    qDebug() << "Nouvelle partie cliqué!";
    // TODO retourner sur le jeu -> mainWindow
    emit continuerClicked();
}

void MenuDePartie::onAbandonnerClicked() {
    qDebug() << "Charger jeu cliqué!";
    // TODO modif avec la bonne fonction pour supp la partie
    emit abandonnerClicked();
}

void MenuDePartie::onQuitClicked() {
    qDebug() << "Quitter cliqué!";
    qApp->quit();
}
void MenuDePartie::onReturnClicked() {
    qDebug() << "Charger jeu cliqué!";
    emit returnClicked();
}



