#include "MenuPostSauvegarde.h"
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

MenuPostSauvegarde::MenuPostSauvegarde(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Menu post sauvegarde");
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *titre = new QLabel("Menu post sauvegarde", this);
    titre->setAlignment(Qt::AlignCenter);
    QFont fontTitre;
    fontTitre.setPointSize(16);
    fontTitre.setBold(true);
    titre->setFont(fontTitre);
    layout->addWidget(titre);

    QPushButton *menuBtn = new QPushButton("Menu", this);
    QPushButton *quitterbtn = new QPushButton("Quitter", this);
    QPushButton *returnBtn = new QPushButton("Return", this);

    layout->addWidget(menuBtn);
    layout->addWidget(returnBtn);
    layout->addWidget(quitterbtn);

    // menu -> mainWindow
    connect(menuBtn, &QPushButton::clicked, this, &MenuPostSauvegarde::goToMainWindow);
    connect(returnBtn, &QPushButton::clicked, this, &MenuPostSauvegarde::onReturnClicked);
    connect(quitterbtn, &QPushButton::clicked, this, &MenuPostSauvegarde::onQuitClicked);

}
void MenuPostSauvegarde::goToMainWindow(){
    qDebug() << "Retour menu principal!";
    emit menuClicked();
}
void MenuPostSauvegarde::onQuitClicked() {
    qDebug() << "Quitter cliqué!";
    qApp->quit();
}
void MenuPostSauvegarde::onReturnClicked() {
    qDebug() << "Retour à la sauvegarde!";
    emit returnClicked();
}

