#include "InterfaceJeu.h"
#include "HexagoneItem.h"
#include "PositionQt.h"
#include <QDebug>
#include <QPixmap>
#include <QSpacerItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QPainter>
#include <cmath>
using enum TypePiece;

InterfaceJeu::InterfaceJeu(QWidget *parent)
    : QMainWindow(parent),
    leftFrame(new QFrame(this)),
    rightFrame(new QFrame(this)),
    leftLabel(new QLabel(this)),
    rightLabel(new QLabel(this)),
    leftTextLabel(new QLabel("Joueur 1", this)),
    rightTextLabel(new QLabel("Joueur 2", this)),


    insectImages({
        Insect(Fourmis, ":images/fourmi_blanc.png", 3),
        Insect(Araignee, ":images/araignee_blanc.png", 2),
        Insect(Sauterelle, ":images/sauterelle_blanc.png", 3),
        Insect(Scarabee, ":images/scarabee_blanc.png", 2),
        Insect(ReineAbeille, ":images/abeille_blanc.png", 1)
    }),
    insectImagesRight({
        Insect(Fourmis, ":images/fourmi_noir.png", 3),
        Insect(Araignee, ":images/araignee_noir.png", 2),
        Insect(Sauterelle, ":images/sauterelle_noir.png", 3),
        Insect(Scarabee, ":images/scarabee_noir.png", 2),
        Insect(ReineAbeille, ":images/abeille_noir.png", 1)
    })
{
    caseSelectionnee = nullptr;

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QVBoxLayout(centralWidget);


    topLayout = new QHBoxLayout();
    leftFrame->setFrameStyle(QFrame::Box);
    rightFrame->setFrameStyle(QFrame::Box);

    QFrame* middleFrame = new QFrame(this);
    middleFrame->setFrameStyle(QFrame::Box);
    QVBoxLayout* middleLayout = new QVBoxLayout(middleFrame);
    middleFrame->setLayout(middleLayout);


    graphicsView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    graphicsView->setRenderHint(QPainter::Antialiasing);
    graphicsView->setMinimumSize(800, 800);
    scene->setBackgroundBrush(Qt::NoBrush);
    scene->setSceneRect(400, 0, 0, 0);
    graphicsView->setStyleSheet("border: none; background: transparent;");

        const qreal hexSize = 40.0;
    const int rows = 15;
    const int cols = 20;
    const qreal hexWidth = sqrt(3) * hexSize;
    const qreal hexHeight = 1.5 * hexSize;

    /*for (int r = 0; r < rows; ++r) {

            int qOffset = r / 2;

        for (int q = 0; q < cols; ++q) {

            PositionQt pos(q - qOffset, r);


            qDebug() << "Hex (" << pos.getQ() << "," << pos.getR() << ")";

            qreal x = hexWidth * q;
            qreal y = hexHeight * r;


            if (r % 2 == 1) {
                x += hexWidth / 2;
            }


            HexagonItem* hex = new HexagonItem(x, y, hexSize);
            scene->addItem(hex);
            connect(hex, &HexagonItem::hexagonClicked, this, &InterfaceJeu::onHexagonClicked);
        }
    }*/

    middleFrame->layout()->addWidget(graphicsView);

    leftFrame->setFixedSize(150, 900);
    rightFrame->setFixedSize(150, 900);

    leftFrameLayout = new QVBoxLayout(leftFrame);
    rightFrameLayout = new QVBoxLayout(rightFrame);
    QFrame* titleLeftFrame = new QFrame(this);
    insectLeftFrame = new QFrame(this);
    titleLeftFrame->setFrameStyle(QFrame::Box);
    insectLeftFrame->setFrameStyle(QFrame::Box);
    titleLeftFrame->setFixedSize(150, 100);
    insectLeftFrame->setFixedSize(150, 800);
    titleleftFrameLayout = new QVBoxLayout(titleLeftFrame);
    insectleftFrameLayout = new QVBoxLayout(insectLeftFrame);
    titleLeftFrame->setStyleSheet("border: none; background: transparent;");
    insectLeftFrame->setStyleSheet("border: none; background: transparent;");
     //Configurer les labels des cadres gauche et droit
    leftLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    leftLabel->setStyleSheet("border: none;");
    rightLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    rightLabel->setStyleSheet("border: none;");

    // Ajouter les éléments dans le cadre gauche
    leftTextLabel->setAlignment(Qt::AlignCenter);
    leftTextLabel->setStyleSheet("font-weight: bold;");
    leftFrameLayout->setContentsMargins(0, 0, 0, 0);
    leftFrameLayout->setAlignment(Qt::AlignTop);
    leftFrameLayout->addWidget(titleLeftFrame);
    leftFrameLayout->addWidget(insectLeftFrame);
    titleleftFrameLayout->addWidget(leftTextLabel);
    titleleftFrameLayout->addWidget(leftLabel);
    titleleftFrameLayout->setContentsMargins(5, 0, 5, 0);
    titleleftFrameLayout->setAlignment(Qt::AlignTop);
    insectleftFrameLayout->setContentsMargins(5, 0, 5, 0);
    insectleftFrameLayout->setAlignment(Qt::AlignTop);

    // Ajouter les insectes dans le cadre gauche
  //  for (const auto& insect : insectImages) {
  ////      addInsectToLayout(leftFrameLayout, insect);
  //  }

    QFrame* titleRightFrame = new QFrame(this);
    insectRightFrame = new QFrame(this);
    titleRightFrame->setFrameStyle(QFrame::Box);
    insectRightFrame->setFrameStyle(QFrame::Box);
    titleRightFrame->setFixedSize(150, 100);
    insectRightFrame->setFixedSize(150, 800);
    titleRightFrameLayout = new QVBoxLayout(titleRightFrame);
    insectRightFrameLayout = new QVBoxLayout(insectRightFrame);
    titleRightFrame->setStyleSheet("border: none; background: transparent;");
    insectRightFrame->setStyleSheet("border: none; background: transparent;");
    // Ajouter les éléments dans le cadre droit (Joueur 2)
    rightTextLabel->setAlignment(Qt::AlignCenter);
    rightTextLabel->setStyleSheet("font-weight: bold;");
    rightFrameLayout->addWidget(titleRightFrame);
    rightFrameLayout->addWidget(insectRightFrame);
    titleRightFrameLayout->addWidget(rightTextLabel);
    titleRightFrameLayout->addWidget(rightLabel);
    rightFrameLayout->setContentsMargins(0, 0, 0, 0);
    rightFrameLayout->setAlignment(Qt::AlignTop);
    titleRightFrameLayout->setContentsMargins(5, 0, 5, 0);
    titleRightFrameLayout->setAlignment(Qt::AlignTop);
    insectRightFrameLayout->setContentsMargins(5, 0, 5, 0);
    insectRightFrameLayout->setAlignment(Qt::AlignTop);

    // Ajouter les insectes dans le cadre droit
   // for (const auto& insect : insectImagesRight) {
   ////     addInsectToLayout(rightFrameLayout, insect);
   // }

    // Ajouter les cadres dans le layout supérieur
    topLayout->addWidget(leftFrame);
    topLayout->addWidget(middleFrame);
    topLayout->addWidget(rightFrame);

    mainLayout->addLayout(topLayout);
    mainLayout->addStretch();

    // Partie inferieure avec les boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *returnActionBtn = new QPushButton("Revenir en arriere");
    buttonLayout->addWidget(returnActionBtn);
    mainLayout->addLayout(buttonLayout);

    // Partie inférieure avec le bouton "Quitter"
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    QPushButton *quitButton = new QPushButton("Quitter");
    bottomLayout->addWidget(quitButton);
    bottomLayout->addStretch();
    mainLayout->addLayout(bottomLayout);



    connect(returnActionBtn, &QPushButton::clicked, this, &InterfaceJeu::onReturnActionClicked);
    connect(quitButton, &QPushButton::clicked, this, &InterfaceJeu::onQuitClicked);
}
void InterfaceJeu::updatePlateau() {
    const qreal hexSize = 40.0;
    const int rows = 15;
    const int cols = 20;
    const qreal hexWidth = sqrt(3) * hexSize;
    const qreal hexHeight = 1.5 * hexSize;
     int qmin = -10;
     int rmin = -10;

     scene->clear();
    if (partie->getFin() != TypeFin::Aucune) {
        emit victoireConditionMet();
    }

    if (!partie->actionPossible(partie->getJoueurActuel())) {
        partie->passerTour();
        updatePlateau();
        return;
    }

    if (partie->getJoueurActuel().getType() == TypeJoueur::IA) {
        const Mouvement* mouvement = partie->getIA().choisirMouvement(partie->getJoueurActuel(), partie->getPlateau(), partie->getNbTours() == 0);
        partie->jouerTour(mouvement);
        updatePlateau();
        return;
    }

    const Plateau& plateau = partie->getPlateau();
    if (scene == nullptr) {
        qDebug() << "scene not initialized";
        return;
    }

    std::set<Deplacement> deplacements;
    if (caseSelectionnee != nullptr) {
        deplacements = caseSelectionnee->getDernierePiece()->getDeplacements(caseSelectionnee->getPos(),plateau);
        if (deplacements.empty()) {
            caseSelectionnee = nullptr;
        }

    }
    for (auto it=plateau.getCases().begin();it != plateau.getCases().end();++it)
    {


        const Case& c = (*it).second;
        QPixmap insectPixmap;
        if (c.getNbPieces() >0) {
            const Piece* piece =c.getDernierePiece();
            TypePiece type = piece->getType();
            Couleur couleur = piece->getCouleur();
             std::string couleur_postfix ="noir";
            if (couleur == Couleur::Blanc) {
                 couleur_postfix = "blanc";
            }
            std::string picture_name;


            switch (type) {
            case TypePiece::Araignee:

                picture_name = "araignee";
                break;
            case TypePiece::Coccinelle:

                picture_name = "coccinelle";
                break;
            case TypePiece::Fourmis:

                picture_name = "fourmi";
                break;
            case TypePiece::Moustique:

                picture_name = "moustique";
                break;
            case TypePiece::ReineAbeille:

                picture_name = "abeille";
                break;
            case TypePiece::Sauterelle:

                picture_name = "sauterelle";
                break;
            case TypePiece::Scarabee:

                picture_name = "scarabee";
                break;
            }

            std::string path = std::format(":images/{}_{}",picture_name,couleur_postfix);
            QString pathQ = QString::fromStdString(path);
            insectPixmap = QPixmap(pathQ);
        }


        Position case_pos = c.getPos();
        PositionQt posqt(case_pos.getQ()-qmin,case_pos.getR()-rmin);
        //qreal x = hexWidth * (case_pos.getQ()-qmin);
        //qreal y = hexHeight * (case_pos.getR()-rmin);
        qreal actq = case_pos.getQ()-qmin;
        qreal actr = case_pos.getR()-rmin;
        qreal x = hexSize * (sqrt(3) * actq +(sqrt(3)/2)*actr);
        qreal y = hexSize *1.5*actr;
        qDebug() << "q r x y" << actq << " " << actr << " " << x << " " << y;
            //  if (case_pos.getR()-rmin % 2 == 1) {
        //     x += hexWidth / 2;
        // }


        HexagonItem* hex = new HexagonItem(x, y, hexSize);
        Joueur& joueur = partie->getJoueurActuel();


        scene->addItem(hex);
        if (c.getNbPieces()>0) {
            hex->setImage(insectPixmap);
            if (joueur.getPieceSelectionnee() == nullptr && caseSelectionnee== nullptr && plateau.getCases().at(case_pos).getDernierePiece()->getCouleur()==joueur.getCouleur()) {
                   connect(hex, &HexagonItem::hexagonClicked, this, &InterfaceJeu::onHexagonClicked);
            }
        }
        if (caseSelectionnee != nullptr) {
            for (auto it=deplacements.begin();it!=deplacements.end(); ++it)
            {
                if ((*it).getDest()==case_pos) {
                    hex->setAvailable(Qt::blue);
                    //scene->addItem(hex);
                    connect(hex, &HexagonItem::hexagonClicked, this, &InterfaceJeu::onHexagonClicked);
                    break;
                }
            }
        }
        if (joueur.getPieceSelectionnee() != nullptr) {
            const Piece* piece = joueur.getPieceSelectionnee();
            std::set<Placement> placements = piece->getPlacements(partie->getPlateau(), partie->getNbTours()==0);
            for (auto it=placements.begin();it!=placements.end(); ++it)
            {
                if ((*it).getDest()==case_pos) {
                      hex->setAvailable(Qt::green);
                      //scene->addItem(hex);
                      connect(hex, &HexagonItem::hexagonClicked, this, &InterfaceJeu::onHexagonClicked);
                    break;
                }
            }

        }


       // connect(hex, &HexagonItem::hexagonClicked, this, &InterfaceJeu::onHexagonClicked);
    }

    QList<QGraphicsItem*> all = scene->items();

    // for (int r = 0; r < rows; ++r) {

    //     int qOffset = r / 2;

    //     for (int q = 0; q < cols; ++q) {

    //         PositionQt pos(q - qOffset, r);


    //         qDebug() << "Hex (" << pos.getQ() << "," << pos.getR() << ")";

    //         qreal x = hexWidth * q;
    //         qreal y = hexHeight * r;


    //         if (r % 2 == 1) {
    //             x += hexWidth / 2;
    //         }


    //         HexagonItem* hex = new HexagonItem(x, y, hexSize);
    //         scene->addItem(hex);
    //         connect(hex, &HexagonItem::hexagonClicked, this, &InterfaceJeu::onHexagonClicked);
    //     }
    // }
}
void InterfaceJeu::refreshDeck(QString joueurName,QFrame* frame, Deck deck,bool left) {
    std::string couleur_postfix;
    QVBoxLayout* layout =  qobject_cast<QVBoxLayout*>(frame->layout());
     removeAllsInsectFromLayout(layout);

    if (left)  {
        couleur_postfix ="blanc";
        insectImages.empty();
        leftTextLabel->setText("Joueur 1: " + joueurName);
    }
    else
    {
        rightTextLabel->setText("Joueur 1: " + joueurName);
        couleur_postfix ="noir";
        insectImagesRight.empty();
    }
   // QLabel* label = new QLabel(this);
   // QLabel* textLabel= new QLabel(JoueurName, this);
    /*label->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    label->setStyleSheet("border: none;");
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setStyleSheet("font-weight: bold;");
    layout->addWidget(textLabel);
    layout->addWidget(label);
    layout->setContentsMargins(5, 0, 5, 0);
    layout->setAlignment(Qt::AlignTop);*/

    // delete all deck item in the layout




    std::map<TypePiece, size_t> effectif = deck.getEffectifs();
    for (Deck::effectif_iterator it = deck.begin(); it != deck.end(); ++it) {
        TypePiece type = (*it).first;
        size_t effectif = (*it).second;
        std::string picture_name;
        switch (type) {
        case TypePiece::Araignee:

            picture_name = "araignee";
            break;
        case TypePiece::Coccinelle:

            picture_name = "coccinelle";
            break;
        case TypePiece::Fourmis:

            picture_name = "fourmi";
            break;
        case TypePiece::Moustique:

            picture_name = "moustique";
            break;
        case TypePiece::ReineAbeille:

            picture_name = "abeille";
            break;
        case TypePiece::Sauterelle:

            picture_name = "sauterelle";
            break;
        case TypePiece::Scarabee:

            picture_name = "scarabee";
            break;
        }

        std::string path = std::format(":images/{}_{}",picture_name,couleur_postfix);
        QString pathQ = QString::fromStdString(path);
        Insect insect = Insect(type,pathQ,effectif);
        Couleur couleur = Couleur::Noir;
        if (left) {
            couleur = Couleur::Blanc;
        }
        addInsectToLayout(layout,insect,couleur);

    }
}

void InterfaceJeu::emptyLayout(QVBoxLayout* layout) {
    QObject* parent= layout->parent();
    if (layout != NULL )
    {
       // delete layout->widget();
        qDeleteAll(parent->children());
      //  QLayoutItem* item;
      //  while ( ( item = layout->takeAt( 0 ) ) != NULL )
      //  {
      //      delete item->widget();
      //      delete item;
      //  }
    }
}

void InterfaceJeu::updateDecks() {
    updatePlateau();

    Deck deck1 = this->partie->getJoueur1().getDeck();
    Deck deck2 = this->partie->getJoueur2().getDeck();
    QString joueur1 = QString::fromStdString(this->partie->getJoueur1().getNom());
    QString joueur2 = QString::fromStdString(this->partie->getJoueur2().getNom());
    refreshDeck(joueur1,insectLeftFrame,deck1,true);
    refreshDeck(joueur2,insectRightFrame,deck2,false);
    if (partie->getTour() == Couleur::Blanc) {
        leftFrame->setStyleSheet("border: 3px solid #FF5733; border-radius: 5px;");
        rightFrame->setStyleSheet("border: 2px solid #CCCCCC; border-radius: 5px;");
    }
    else
    {
        rightFrame->setStyleSheet("border: 3px solid #00BFFF; border-radius: 5px;");
        leftFrame->setStyleSheet("border: 2px solid #CCCCCC; border-radius: 5px;");
    }

}

void InterfaceJeu::onQuitClicked() {
    qDebug() << "Quitter cliqué! redirection vers menu sauvegarde";
    emit quitClicked();
}

void InterfaceJeu::onReturnActionClicked() {
    if (partie->historiqueMouvements.size() < 2 || partie->sauvegardes.size() < 2){
        qDebug() << "Annulation impossible (moins de 2 coups)";
    }
    else {
        partie->retourArriere();
        updateDecks();
        qDebug() << "Action annulee";
    }
}

void InterfaceJeu::updatePlayerNames(const QString &joueur1Name, const QString &joueur2Name) {
    leftTextLabel->setText("Joueur 1: " + joueur1Name);
    rightTextLabel->setText("Joueur 2: " + joueur2Name);
}



void InterfaceJeu::removeInsectFromLayout(QVBoxLayout* layout, const QString& imagePath) {
    for (int i = 0; i < layout->count(); ++i) {
        QLayoutItem* item = layout->itemAt(i);
        QHBoxLayout* insectLayout = qobject_cast<QHBoxLayout*>(item->layout());

        if (insectLayout) {
            QLabel* imageLabel = qobject_cast<QLabel*>(insectLayout->itemAt(0)->widget());

            if (imageLabel && imageLabel->objectName() == imagePath) {
                while (QLayoutItem* childItem = insectLayout->takeAt(0)) {
                    delete childItem->widget();
                    delete childItem;
                }
                layout->removeItem(item);
                delete insectLayout;
                return;
            }
        }
    }
}

void InterfaceJeu::removeAllsInsectFromLayout(QVBoxLayout* layout) {
    //for (int i = 0; i < layout->->takeAt(0)); ++i)
  while (QLayoutItem* item = layout->takeAt(0)) {
        //QLayoutItem* item = layout->itemAt(i);
        QHBoxLayout* insectLayout = qobject_cast<QHBoxLayout*>(item->layout());

        if (insectLayout) {

                while (QLayoutItem* childItem = insectLayout->takeAt(0)) {
                    delete childItem->widget();
                    delete childItem;
                }
                layout->removeItem(item);
                delete insectLayout;

                //return;

        }
    }
}

void InterfaceJeu::addInsectToLayout(QVBoxLayout* layout, const Insect& insect,Couleur couleur) {
    QPushButton* insectButton = new QPushButton(this);
    QPixmap insectPixmap(insect.imagePath);

    if (insectPixmap.isNull()) {
        qDebug() << "Erreur de chargement de l'image de l'insecte.";
    } else {
        insectButton->setIcon(QIcon(insectPixmap));
        insectButton->setIconSize(QSize(70, 70));
    }

    insectButton->setStyleSheet("border: none; padding: 0px;");
    insectButton->setFlat(true);
    insectButton->setFixedSize(70, 70);

    QLabel* insectCountLabel = new QLabel(QString::number(insect.count), this);
    insectCountLabel->setStyleSheet("font-weight: bold; font-size: 22px; border: none;");
    insectCountLabel->setAlignment(Qt::AlignLeft);
    insectCountLabel->setFixedWidth(50);

    QHBoxLayout* insectLayout = new QHBoxLayout();
    insectLayout->addWidget(insectButton);
    insectLayout->addWidget(insectCountLabel);
    layout->addLayout(insectLayout);

    if (partie->getJoueurActuel().getCouleur() == couleur) {
        connect(insectButton, &QPushButton::clicked, this, [this, insect]() {
            selectedImagePath = insect.imagePath;
            caseSelectionnee = nullptr;
            if (partie->getJoueurActuel().getPieceSelectionnee() != nullptr) {
                TypePiece type =partie->getJoueurActuel().getPieceSelectionnee()->getType();
                 partie->getJoueurActuel().annulerSelection();
                 if (type == insect.type) {
                    updateDecks();
                    return;
                }
            }
            partie->getJoueurActuel().selectionnerPieceDeck(insect.type);
          //  removeAllsInsectFromLayout( qobject_cast<QVBoxLayout*>(insectLeftFrame->layout()));
          //  removeAllsInsectFromLayout( qobject_cast<QVBoxLayout*>(rightFrame->layout()));

            updateDecks();

            switch (insect.type) {
            case TypePiece::Fourmis:
                qDebug() << "Type d'insecte sélectionné: Fourmi";
                break;
            case TypePiece::Araignee:
                qDebug() << "Type d'insecte sélectionné: Araignée";
                break;
            case TypePiece::Sauterelle:
                qDebug() << "Type d'insecte sélectionné: Sauterelle";
                break;
            case TypePiece::Scarabee:
                qDebug() << "Type d'insecte sélectionné: Scarabée";
                break;
            case TypePiece::ReineAbeille:
                qDebug() << "Type d'insecte sélectionné: Abeille";
                break;
            case TypePiece::Moustique:
                qDebug() << "Type d'insecte sélectionné: Moustique";
                break;
            case TypePiece::Coccinelle:
                qDebug() << "Type d'insecte sélectionné: Coccinelle";
                break;
            default:
                qDebug() << "Type d'insecte inconnu";
                break;
            }
        });
    }
}

void InterfaceJeu::updateInsectSelection(const QMap<QString, bool>& selectedInsects) {
    QVBoxLayout* leftFrameLayout = qobject_cast<QVBoxLayout*>(leftFrame->layout());
    QVBoxLayout* rightFrameLayout = qobject_cast<QVBoxLayout*>(rightFrame->layout());

    for (auto it = selectedInsects.begin(); it != selectedInsects.end(); ++it) {
        const QString& insectName = it.key();
        bool checked = it.value();

        QString leftImage, rightImage;
        TypePiece insectType;

        if (insectName == "moustique") {
            insectType = TypePiece::Moustique;
            leftImage = ":images/moustique_blanc.png";
            rightImage = ":images/moustique_noir.png";
        } else if (insectName == "coccinelle") {
            insectType = TypePiece::Coccinelle;
            leftImage = ":images/coccinelle_blanc.png";
            rightImage = ":images/coccinelle_noir.png";
        } else {
            continue;
        }

        Insect insect{insectType, leftImage, 1};

        if (checked) {

            addInsectToLayout(leftFrameLayout, insect,Couleur::Blanc);

            insect.imagePath = rightImage;
            addInsectToLayout(rightFrameLayout, insect,Couleur::Noir);
        } else {

            removeInsectFromLayout(leftFrameLayout, leftImage);
            removeInsectFromLayout(rightFrameLayout, rightImage);
        }
    }
}


void InterfaceJeu::onHexagonClicked(HexagonItem* hex) {
    QPointF center = hex->boundingRect().center();
    qreal x = center.x();
    qreal y = center.y();
    int qmin= -10;
    int rmin= -10;
    qreal hexSize = 40.0;
    PositionQt pos = PositionQt::fromPixel(x, y, hexSize);
    Position destination = Position(pos.getQ()+qmin,pos.getR()+rmin);
    Joueur& joueur = partie->getJoueurActuel();

    if (caseSelectionnee != nullptr) {
        const Deplacement* deplacement = new Deplacement(caseSelectionnee->getPos(),destination);
        partie->jouerTour(deplacement);
        caseSelectionnee = nullptr;
        updateDecks();
        return;
    }
    if (joueur.getPieceSelectionnee() == nullptr) {
        caseSelectionnee = &partie->getPlateau().getCases().at(destination);
        updatePlateau();
        qDebug() << "Aucun insecte sélectionné !";
        return;
    }

    qDebug() << "piece sélectionnée !";
    const Placement* placement= new Placement(joueur.getPieceSelectionnee(),destination);
    joueur.finirSelection();
    partie->jouerTour(placement);
    caseSelectionnee = nullptr;
    updateDecks();

    // QPixmap insectPixmap(selectedImagePath);
    // if (insectPixmap.isNull()) {
    //     qDebug() << "Erreur de chargement de l'image pour l'hexagone.";
    //     return;
    // }
    // hex->setImage(insectPixmap);



    qDebug() << "Hex (" << pos.getQ() << ", " << pos.getR() << ")";
}

void InterfaceJeu::assignPartie(Partie* partie1) {
    this->partie = partie1;
    updatePlateau();
    updateDecks();
    Couleur couleur = this->partie->getTour();
    std::string tourCouleur ="Blanc";
    if (couleur == Couleur::Noir)
    {
        tourCouleur = "Noir";
    }




     qDebug() << "Partie assignée" << tourCouleur;
}
