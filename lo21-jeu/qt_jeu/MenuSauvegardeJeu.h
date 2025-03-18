#ifndef MENUSAUVEGARDEJEU_H
#define MENUSAUVEGARDEJEU_H

#include <QMainWindow>

class MenuSauvegardeJeu : public QMainWindow {
    Q_OBJECT
public:
    explicit MenuSauvegardeJeu(QWidget *parent = nullptr);

signals:
    void ouiBtnClicked();
    void nonBtnClicked();
    void returnBtnClicked();

private slots:
    void onOuiBtnClicked();
    void onNonBtnClicked();
    void onReturnBtnClicked();
    void onQuitClicked();
};

#endif // MENUSAUVEGARDEJEU_H






