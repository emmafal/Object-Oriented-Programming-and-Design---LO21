#include "MainWindowJeu.h"

MainWindowJeu::MainWindowJeu(QWidget *parent): QMainWindow(parent) {
    stackedWidget = new QStackedWidget(this);

    menuSauvegardeJeu = new MenuSauvegardeJeu(this); //0
    menuPostSauvegarde = new MenuPostSauvegarde(this); //1
    affichageVictoire = new Victoire(this); //2
    interfaceJeu = new InterfaceJeu(this); //3

    stackedWidget->addWidget(menuSauvegardeJeu);
    stackedWidget->addWidget(menuPostSauvegarde);
    stackedWidget->addWidget(affichageVictoire);
    stackedWidget->addWidget(interfaceJeu);

    // pour revenir en arrière
    connect(menuSauvegardeJeu, &MenuSauvegardeJeu::returnBtnClicked, this, &MainWindowJeu::onSauvegardeReturnClicked);
    connect(menuPostSauvegarde, &MenuPostSauvegarde::returnClicked, this, &MainWindowJeu::showMenuSauvegarde);

    // victoire -> menu début
    connect(affichageVictoire, &Victoire::menuClicked, this, &MainWindowJeu::showMenu);

    // sauvegarde (btn oui/non) -> post sauvegarde
    connect(menuSauvegardeJeu, &MenuSauvegardeJeu::ouiBtnClicked, this, &MainWindowJeu::showPostSauvegarde);
    connect(menuSauvegardeJeu, &MenuSauvegardeJeu::nonBtnClicked, this, &MainWindowJeu::showPostSauvegarde);

    // Post sauvegarde (menu clique) -> menuDebut
    connect(menuPostSauvegarde, &MenuPostSauvegarde::menuClicked, this, &MainWindowJeu::showMenu);

    // quitter dans jeu -> menu sauvegarde
    connect(interfaceJeu, &InterfaceJeu::quitClicked, this, &MainWindowJeu::showMenuSauvegarde);

    // lorsque conditions victoire -> Victoire ajouter le connect ou jsp
    //TODO
    connect(interfaceJeu, &InterfaceJeu::victoireConditionMet, this, &MainWindowJeu::showVictoire);

    // extension (settings) -> interface jeu
    QObject::connect(this, &MainWindowJeu::updateInsectSelection, interfaceJeu, &InterfaceJeu::updateInsectSelection);

    setCentralWidget(stackedWidget);

    setWindowTitle("Jeu");
    stackedWidget->setCurrentIndex(3);
}

void MainWindowJeu::showMenuSauvegarde(){
    qDebug() << "Sauvegarde menu";
    setWindowTitle("Sauvegarder");
    stackedWidget->setCurrentIndex(0);
}
void MainWindowJeu::showVictoire() {
    qDebug() << "Fin de la partie";
    setWindowTitle("Fin de la partie");
    stackedWidget->setCurrentIndex(2);
}
void MainWindowJeu::onSauvegardeReturnClicked() {
    qDebug() << "Retour au jeu apres sauvegarde";
    setWindowTitle("Jeu");
    stackedWidget->setCurrentIndex(3);
}
void MainWindowJeu::showPostSauvegarde() {
    qDebug() << "Menu post sauvegarde";
    setWindowTitle("Menu");
    stackedWidget->setCurrentIndex(1);
}
void MainWindowJeu::showMenu() {
    qDebug() << "Retour à MenuDebut";
    emit goToMenuDebut();
}
void MainWindowJeu::setupJoueurs(const QString &joueur1Name, const QString &joueur2Name) {
    qDebug() << "Transfert des noms";

   // interfaceJeu->updatePlayerNames(joueur1Name, joueur2Name);
}
void MainWindowJeu::resetToInterfaceJeu() {
    qDebug() << "Réinitialisation vers InterfaceJeu";
    setWindowTitle("Jeu");
    stackedWidget->setCurrentIndex(3);
}
void MainWindowJeu::onInsectSelectionValidated(const QMap<QString, bool>& selectedInsects) {
    qDebug() << "MainWindowJeu: Insectes validés :" << selectedInsects;
    selectedInsectsStored = &selectedInsects;
   // emit updateInsectSelection(selectedInsects);
}

void MainWindowJeu::assignPartie(Partie* partie1) {
    this->partie = partie1;
    Couleur couleur = partie->getTour();
    std::string tourCouleur ="Blanc";
    if (couleur == Couleur::Noir)
    {
        tourCouleur = "Noir";
    }
    qDebug() << "Partie a assigner" << tourCouleur;
    this->interfaceJeu->assignPartie(this->partie);
}
