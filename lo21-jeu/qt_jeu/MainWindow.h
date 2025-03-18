#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "MenuDebut.h"
#include "MenuConfigJoueur.h"
#include "MenuDePartie.h"
#include "SettingsPartie.h"
#include "InterfaceJeu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    std::string getjoueur1Name();
    std::string getjoueur2Name();

public slots:
    void showSettingsPartie();
    void resetToMenuDebut();
private:
    QStackedWidget *stackedWidget;    
    MenuDebut *menuDebut;             
    MenuConfigJoueur *menuConfigJoueur; 
    MenuDePartie *menuDePartie;       
    SettingsPartie *settingsPartie;   
    InterfaceJeu *interfaceJeu;      
    void returnToMenuDebut();
    void showMenuConfigJoueur();
    void showMenuDePartie();
    void goToInterfaceJeu();
    void goToWindowJeu();
    QString joueur1Name;
    QString joueur2Name;
    QString joueurName;


private slots:
    void onJoueursConfigured(const QString &joueur1Name, const QString &joueur2Name);
    void onInsectSelectionValidated(const QMap<QString, bool>& selectedInsects);
signals:
    void goToWindowJeuClicked();
    void validerJoueurClicked();
    void saveGoInterfaceClicked(const QString &joueur1Name, const QString &joueur2Name);

    void joueursConfigured(const QString &joueur1Name, const QString &joueur2Name);
    void insectSelectionValidated(const QMap<QString, bool>& selectedInsects);
};

#endif // MAINWINDOW_H
