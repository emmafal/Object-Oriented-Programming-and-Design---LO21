#include "Victoire.h"
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QSizePolicy>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
//TODO à relier à Jeu
Victoire::Victoire(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Fin de la partie");
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *titre = new QLabel("Fin de la partie", this);
    titre->setAlignment(Qt::AlignCenter);
    QFont fontTitre;
    fontTitre.setPointSize(16);
    fontTitre.setBold(true);
    titre->setFont(fontTitre);
    layout->addWidget(titre);

    QPushButton *menubtn = new QPushButton("Menu principal", this);
    QPushButton *quitterbtn = new QPushButton("Quitter", this);

    layout->addWidget(menubtn);
    layout->addWidget(quitterbtn);
    connect(menubtn, &QPushButton::clicked, this, &Victoire::onMenuClicked);
    connect(quitterbtn, &QPushButton::clicked, this, &Victoire::onQuitClicked);
}

void Victoire::onMenuClicked() {
    qDebug() << "Menu cliqué";
    emit menuClicked();
}

void Victoire::onQuitClicked() {
    qDebug() << "Quitter cliqué!";
    qApp->quit();
}



