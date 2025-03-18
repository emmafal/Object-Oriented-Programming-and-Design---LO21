#include "MenuConfigJoueur.h"
#include "MenuDePartie.h"
#include "MenuDebut.h"
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QSizePolicy>
#include <QDebug>

MenuDebut::MenuDebut(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QPushButton *newpartiebtn = new QPushButton("Nouvelle partie", this);
    QPushButton *loadgamebtn = new QPushButton("Charger une partie", this);
    QPushButton *quitterbtn = new QPushButton("Quitter", this);

    layout->addWidget(newpartiebtn);
    layout->addWidget(loadgamebtn);
    layout->addWidget(quitterbtn);

    connect(newpartiebtn, &QPushButton::clicked, this, &MenuDebut::onNewPartieClicked);
    connect(loadgamebtn, &QPushButton::clicked, this, &MenuDebut::onLoadGameClicked);
    connect(quitterbtn, &QPushButton::clicked, this, &MenuDebut::onQuitClicked);
}

void MenuDebut::onNewPartieClicked() {
    qDebug() << "Nouvelle partie cliqué!";
    emit newPartieClicked(); // a enlever ?
}

void MenuDebut::onLoadGameClicked() {
    qDebug() << "Charger jeu cliqué!";
    // TODO fonction pour checker si il existe une partie sauvegardé
    emit loadGameClicked(); // a enlever ?
}

void MenuDebut::onQuitClicked() {
    qDebug() << "Quitter cliqué!";
    qApp->quit();
}


