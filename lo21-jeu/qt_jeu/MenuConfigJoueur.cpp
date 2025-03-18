#include "MenuConfigJoueur.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMainWindow>
#include <QSizePolicy>
#include <QApplication>
#include <QDebug>


MenuConfigJoueur::MenuConfigJoueur(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Configuration du jeu");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *titre = new QLabel("Joueur vs Joueur", this);
    QFont fontTitre;
    fontTitre.setPointSize(16);
    fontTitre.setBold(true);
    titre->setFont(fontTitre);
    layout->addWidget(titre);

    QLabel *labelJoueur1 = new QLabel("Nom du Joueur 1 :", this);
    layout->addWidget(labelJoueur1);
    saisieJoueur1 = new QLineEdit(this);
    saisieJoueur1->setText("Alice");
    saisieJoueur1->setPlaceholderText("Entrez le nom du Joueur 1");
    layout->addWidget(saisieJoueur1);

    QLabel *labelJoueur2 = new QLabel("Nom du Joueur 2 :", this);
    layout->addWidget(labelJoueur2);
    saisieJoueur2 = new QLineEdit(this);
    saisieJoueur2->setText("Bob");
    saisieJoueur2->setPlaceholderText("Entrez le nom du Joueur 2");
    layout->addWidget(saisieJoueur2);

    QPushButton *validerJvsJBtn = new QPushButton("Valider", this);
    layout->addWidget(validerJvsJBtn);

    QLabel *titre2 = new QLabel("Jouer contre une IA", this);
    QFont fontTitre2;
    fontTitre2.setPointSize(16);
    fontTitre2.setBold(true);
    titre2->setFont(fontTitre2);
    layout->addWidget(titre2);

    QLabel *labelJoueur = new QLabel("Nom du Joueur :", this);
    layout->addWidget(labelJoueur);
    saisieJoueur = new QLineEdit(this);
    saisieJoueur->setText("Caribou");
    saisieJoueur->setPlaceholderText("Entrez le nom du Joueur");
    layout->addWidget(saisieJoueur);

    QPushButton *validerIaBtn = new QPushButton("Valider", this);
    layout->addWidget(validerIaBtn);

    QPushButton *returnbtn = new QPushButton("Retour", this);
    QPushButton *quitterbtn = new QPushButton("Quitter", this);
    layout->addWidget(quitterbtn);
    layout->addWidget(returnbtn);

    connect(validerJvsJBtn, &QPushButton::clicked, this, &MenuConfigJoueur::onJvsJClicked);
    connect(validerIaBtn, &QPushButton::clicked, this, &MenuConfigJoueur::onIAClicked);
    connect(quitterbtn, &QPushButton::clicked, this, &MenuConfigJoueur::onQuitClicked);
    connect(returnbtn, &QPushButton::clicked, this, &MenuConfigJoueur::onReturnClicked);
}


void MenuConfigJoueur::onReturnClicked() {
    qDebug() << "Clic sur 'Retour'.";
    emit returnClicked();
}

void MenuConfigJoueur::onQuitClicked() {
    qDebug() << "Quitter cliqué!";
    qApp->quit();
}

void MenuConfigJoueur::onIAClicked() {
    qDebug() << "IA cliqué!";
    emit iaConfigured(saisieJoueur->text(), "Skynet");
    emit validerClicked();
}

void MenuConfigJoueur::onJvsJClicked() {
    qDebug() << "J vs J";
    emit jvsJConfigured(saisieJoueur1->text(), saisieJoueur2->text());
    emit validerClicked();
    qDebug() << "Nom du Joueur 1 :" << saisieJoueur1;
    qDebug() << "Nom du Joueur 2 :" << saisieJoueur2;
}


