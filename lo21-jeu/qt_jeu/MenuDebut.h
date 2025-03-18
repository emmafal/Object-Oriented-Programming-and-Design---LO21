#ifndef MENUDEBUT_H
#define MENUDEBUT_H

#include <QMainWindow>

class MenuDebut : public QMainWindow {
    Q_OBJECT
public:
    explicit MenuDebut(QWidget *parent = nullptr);

signals:
    void newPartieClicked();
    void loadGameClicked();

private slots:
    void onNewPartieClicked();
    void onLoadGameClicked();
    void onQuitClicked();
};

#endif // MENUDEBUT_H

