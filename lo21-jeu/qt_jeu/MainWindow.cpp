#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    stackedWidget = new QStackedWidget(this);

    menuDebut = new MenuDebut(this);
    menuConfigJoueur = new MenuConfigJoueur(this);
    menuDePartie = new MenuDePartie(this);
    settingsPartie = new SettingsPartie(this);

    stackedWidget->addWidget(menuDebut); //0
    stackedWidget->addWidget(menuConfigJoueur); //1
    stackedWidget->addWidget(menuDePartie); //2
    stackedWidget->addWidget(settingsPartie); //3

    // Connexions de retour
    connect(menuConfigJoueur, &MenuConfigJoueur::returnClicked, this, &MainWindow::returnToMenuDebut);
    connect(settingsPartie, &SettingsPartie::returnClicked, this, &MainWindow::showMenuConfigJoueur);
    connect(menuDePartie, &MenuDePartie::returnClicked, this, &MainWindow::returnToMenuDebut);

    // Nouvelle partie -> config joueur
    connect(menuDebut, &MenuDebut::newPartieClicked, this, &MainWindow::showMenuConfigJoueur);

    // Charger partie -> menu de partie // TODO check si y'a bien une partie chargée
    connect(menuDebut, &MenuDebut::loadGameClicked, this, &MainWindow::showMenuDePartie);

    // JvsJ ou contre IA -> settings partie
    connect(menuConfigJoueur, &MenuConfigJoueur::jvsJConfigured, this, &MainWindow::onJoueursConfigured);
    connect(menuConfigJoueur, &MenuConfigJoueur::validerClicked, this, &MainWindow::showSettingsPartie);
    connect(menuConfigJoueur, &MenuConfigJoueur::iaConfigured, this, &MainWindow::onJoueursConfigured);
    connect(menuConfigJoueur, &MenuConfigJoueur::validerClicked, this, &MainWindow::showSettingsPartie);

    // Abandonner partie -> menu début
    connect(menuDePartie, &MenuDePartie::abandonnerClicked, this, &MainWindow::returnToMenuDebut); // TODO : supprimer la partie
    // Continuer la partie -> revenir au jeu
    //connect(menuDePartie, &MenuDePartie::continuerClicked, this, &MainWindow::goToWindowJeu); // TODO : récupérer la partie en cours?

    // Settings -> jeu
    connect(settingsPartie, &SettingsPartie::validerClicked, this, &MainWindow::goToWindowJeuClicked);

    // extensions selectionnee -> interface jeu
   
    connect(settingsPartie, &SettingsPartie::validatedInsectSelection, this, &MainWindow::onInsectSelectionValidated);

    setCentralWidget(stackedWidget);
    setWindowTitle("Menu");
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::returnToMenuDebut() {
    qDebug() << "Retour à MenuDebut";
    setWindowTitle("Menu");
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::showMenuConfigJoueur() {
    qDebug() << "Affichage de MenuConfigJoueur";
    setWindowTitle("Configuration du jeu");
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showMenuDePartie() {
    qDebug() << "Affichage de MenuDePartie";
    setWindowTitle("Menu");
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::showSettingsPartie() {
    qDebug() << "Paramètres du jeu";
    stackedWidget->setCurrentIndex(3);
    setWindowTitle("Paramètres du jeu");
}

void MainWindow::resetToMenuDebut() {
    qDebug() << "Réinitialisation vers MenuDebut";
    setWindowTitle("Menu");
    stackedWidget->setCurrentIndex(0);
}
void MainWindow::onJoueursConfigured(const QString &joueur1Name, const QString &joueur2Name) {
    qDebug() << "Transfert des infos en cours";
    this->joueur1Name = joueur1Name;
    this->joueur2Name = joueur2Name;
    emit joueursConfigured(joueur1Name, joueur2Name);
}
void MainWindow::onInsectSelectionValidated(const QMap<QString, bool>& selectedInsects) {
    qDebug() << "Insectes validés :" << selectedInsects;
    emit insectSelectionValidated(selectedInsects);
}

std::string MainWindow::getjoueur1Name() {
    return this->joueur1Name.toStdString();
}

std::string MainWindow::getjoueur2Name() {
    return this->joueur2Name.toStdString();
}

