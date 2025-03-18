#ifndef MENUPOSTSAUVEGARDE_H
#define MENUPOSTSAUVEGARDE_H

#include <QMainWindow>

class MenuPostSauvegarde: public QMainWindow
{
    Q_OBJECT
public:
    explicit MenuPostSauvegarde(QWidget *parent = nullptr);
signals:
    void menuClicked();
    void returnClicked();
private slots:
    void goToMainWindow();
    void onQuitClicked();
    void onReturnClicked();
};

#endif // MENUPOSTSAUVEGARDE_H
