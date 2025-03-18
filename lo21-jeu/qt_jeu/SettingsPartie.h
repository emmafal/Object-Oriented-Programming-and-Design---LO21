#ifndef SETTINGSPARTIE_H
#define SETTINGSPARTIE_H
#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QIntValidator>

class SettingsPartie : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingsPartie(QWidget *parent = nullptr);
    std::string getJoueur1();
    std::string getJoueur2();
signals :
    // void moustiqueisChecked();
    // void coccinelleisChecked();
    // void cloporteisChecked();
    void validatedInsectSelection(const QMap<QString, bool>& selectedInsects);

    void returnClicked();
    void validerClicked();
    void playerNamesUpdated(const QString &joueur1, const QString &joueur2);
private slots:
    void onReturnClicked();
    void onQuitClicked();
    //void onValiderClicked();
    void onValidateButtonClicked();

private:
    QLineEdit *saisieEntier;
    QCheckBox *moustique;
    QCheckBox *coccinelle;
    QString joueur1Name;
    QString joueur2Name;

    QLabel *joueur1Label;
    QLabel *joueur2Label;

};

#endif // SETTINGSPARTIE_H

