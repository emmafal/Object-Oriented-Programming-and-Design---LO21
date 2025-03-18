#ifndef MENUDEPARTIE_H
#define MENUDEPARTIE_H
#include <QMainWindow>

class MenuDePartie : public QMainWindow
{
    Q_OBJECT
public:
    explicit MenuDePartie(QWidget *parent = nullptr);
signals :
    void continuerClicked();
    void abandonnerClicked();
    void returnClicked();

private slots:
    void onContinuerClicked();
    void onAbandonnerClicked();
    void onReturnClicked();
    void onQuitClicked();
};

#endif // MENUDEPARTIE_H
