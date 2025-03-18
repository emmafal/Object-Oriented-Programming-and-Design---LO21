#include "MenuSauvegardeJeu.h"
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

MenuSauvegardeJeu::MenuSauvegardeJeu(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Menu sauvegarde");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *titre = new QLabel("Sauvegarder?", this);
    titre->setAlignment(Qt::AlignCenter);
    QFont fontTitre;
    fontTitre.setPointSize(16);
    fontTitre.setBold(true);
    titre->setFont(fontTitre);
    layout->addWidget(titre);

    QPushButton *ouiBtn = new QPushButton("Oui", this);
    QPushButton *nonBtn = new QPushButton("Non", this);
    QPushButton *returnBtn = new QPushButton("Retour", this);
    QPushButton *quitterbtn = new QPushButton("Quitter", this);

    layout->addWidget(ouiBtn);
    layout->addWidget(nonBtn);
    layout->addWidget(returnBtn);
    layout->addWidget(quitterbtn);

    // menu -> mainWindow
    connect(ouiBtn, &QPushButton::clicked, this, &MenuSauvegardeJeu::onOuiBtnClicked);
    connect(nonBtn, &QPushButton::clicked, this, &MenuSauvegardeJeu::onNonBtnClicked);
    connect(returnBtn, &QPushButton::clicked, this, &MenuSauvegardeJeu::onReturnBtnClicked);
    connect(quitterbtn, &QPushButton::clicked, this, &MenuSauvegardeJeu::onQuitClicked);

}
void MenuSauvegardeJeu::onOuiBtnClicked(){
    qDebug() << "Partie sauvegarde"; // TODO avec la bonne fonction
    emit ouiBtnClicked();
}
void MenuSauvegardeJeu::onNonBtnClicked() {
    qDebug() << "Partie non sauvegarde"; // TODO avec la bonne fonction ?
    emit nonBtnClicked();
}
void MenuSauvegardeJeu::onReturnBtnClicked() {
    qDebug() << "Retour au jeu après click sur return";
    emit returnBtnClicked();
}
void MenuSauvegardeJeu::onQuitClicked() {
    qDebug() << "Quitter cliqué!";
    qApp->quit();
}

