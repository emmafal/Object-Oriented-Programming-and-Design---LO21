#ifndef VICTOIRE_H
#define VICTOIRE_H
#include <QMainWindow>
#include "Partie.h"

class Victoire : public QMainWindow
{
    Q_OBJECT
public:
    explicit Victoire(QWidget *parent = nullptr);
signals :
    void menuClicked();

private slots:
    void onMenuClicked();
    void onQuitClicked();
private:
    Partie* partie;
};
#endif // VICTOIRE_H
