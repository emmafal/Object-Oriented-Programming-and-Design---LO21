#ifndef INTERFACEJEU_H
#define INTERFACEJEU_H

#include "HexagoneItem.h"
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QPixmap>
#include <QList>
#include <QPair>
#include "TypeInsecte.h"
#include "Partie.h"


struct Insect {
    TypePiece type;
    QString imagePath;
    int count;

    Insect(TypePiece t, const QString& img, int c) : type(t), imagePath(img), count(c) {}
};

class InterfaceJeu : public QMainWindow {
    Q_OBJECT
public:
    explicit InterfaceJeu(QWidget* parent = nullptr);


    void updatePlayerNames(const QString& joueur1Name, const QString& joueur2Name);


    void addInsectToLayout(QVBoxLayout* layout, const Insect& insect,Couleur couleur);
    void refreshDeck(QString Joueurname,QFrame* layout, Deck deck,bool left);
    void removeAllsInsectFromLayout(QVBoxLayout* layout);
    void removeInsectFromLayout(QVBoxLayout* layout, const QString& imagePath);
    void setSelectedImagePath(const QString& path);


    void setMoustiqueChecked(bool checked);
    void setCoccinelleChecked(bool checked);
    void setCloporteChecked(bool checked);
    void setInsectChecked(bool checked, const QString& insectName, const QString& leftImage, const QString& rightImage);

    QString getInsectTypeFromEnum(TypePiece type);

    void updateInsectSelection(const QMap<QString, bool>& selectedInsects);

    void assignPartie(Partie* partie);
    void updateDecks();
    void updatePlateau();
private slots:
    void onQuitClicked();
    void onReturnActionClicked();
    void onHexagonClicked(HexagonItem* hex);

signals:
    void quitClicked();
    void piecePlaced();
    void victoireConditionMet();
    void goToMenuQuitterJeu();
    void imageSelected(const QString& path);

private:
    void emptyLayout(QVBoxLayout* layout);
    QString selectedImagePath;
    TypePiece selectedTypePiece;


    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QHBoxLayout* topLayout;
    QFrame* leftFrame;
    QFrame* insectLeftFrame;
    QFrame* insectRightFrame;
    QFrame* rightFrame;
    QVBoxLayout *leftFrameLayout;
    QVBoxLayout *rightFrameLayout;
    QVBoxLayout *titleleftFrameLayout;
    QVBoxLayout *insectleftFrameLayout;
    QVBoxLayout *titleRightFrameLayout;
    QVBoxLayout *insectRightFrameLayout;
    QLabel* leftLabel;
    QLabel* rightLabel;
    QLabel* leftTextLabel;
    QLabel* rightTextLabel;


    QList<Insect> insectImages;
    QList<Insect> insectImagesRight;


    QGraphicsScene* scene;
    QGraphicsView* graphicsView;
    Partie* partie;
    const Case* caseSelectionnee;
};

#endif // INTERFACEJEU_H
