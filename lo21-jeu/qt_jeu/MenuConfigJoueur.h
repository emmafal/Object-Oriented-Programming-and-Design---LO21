#ifndef MENUCONFIGJOUEUR_H
#define MENUCONFIGJOUEUR_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class MenuConfigJoueur: public QMainWindow
{
    Q_OBJECT
public:
    explicit MenuConfigJoueur(QWidget *parent = nullptr);

    // Méthodes pour obtenir les noms des joueurs
    // QString getNomJoueur1() const { return saisieJoueur1->text(); }
    // QString getNomJoueur2() const { return saisieJoueur2->text(); }
    // QString getNomJoueurIA() const { return saisieJoueur->text(); }

signals:
    void jvsJConfigured(const QString &saisieJoueur1,const QString &saisieJoueur2 );
    void iaConfigured(const QString& joueurName, const QString& IA);
    void playerNamesEntered(const QString &joueur1, const QString &joueur2);
    void validerClicked();
    void returnClicked();

private slots:
    void onQuitClicked();
    void onReturnClicked();
    void onJvsJClicked();
    void onIAClicked();

private:
    QLineEdit *saisieJoueur1;
    QLineEdit *saisieJoueur2;
    QLineEdit *saisieJoueur;
    QPushButton *buttonJvsJ;
    QPushButton *buttonIA;
};

#endif // MENUCONFIGJOUEUR_H
