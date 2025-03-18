#ifndef MainWindowJeu_H
#define MainWindowJeu_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include "MainWindow.h"
#include "MenuSauvegardeJeu.h"
#include "MenuPostSauvegarde.h"
#include "Victoire.h"
#include "InterfaceJeu.h"

class MainWindowJeu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowJeu(QWidget *parent = nullptr);
    void setLeftFrameText(const QString &text);
    void setRightFrameText(const QString &text);

    const QMap<QString, bool>* selectedInsectsStored;

    public slots:
    void setupJoueurs(const QString &joueur1Name, const QString &joueur2Name);
    void resetToInterfaceJeu();
    void onInsectSelectionValidated(const QMap<QString, bool>& selectedInsects);
    void assignPartie(Partie* partie);

signals :
    void menuClicked();
    void sauvergardeBtnClicked();
    void sauvegardeReturnClicked();
    void goToMenuDebut();
    void quitGameClicked();
    void updateInsectSelection(const QMap<QString, bool>& selectedInsects);

private:
    enum class MenuType {
        Victoire,
        PostSauvegarde
    };

private slots:
    void showMenu();
    void showPostSauvegarde();
    void showVictoire();
    void showMenuSauvegarde();
    void onSauvegardeReturnClicked();
private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QFrame *leftFrame;
    QFrame *rightFrame;
    QLabel *leftLabel;
    QLabel *rightLabel;
    QLabel *leftImageLabel;

    QStackedWidget *stackedWidget;
    InterfaceJeu *interfaceJeu;
    MenuSauvegardeJeu *menuSauvegardeJeu;
    MenuPostSauvegarde *menuPostSauvegarde;
    Victoire *affichageVictoire;
    Partie* partie;
};

#endif // MainWindowJeu
