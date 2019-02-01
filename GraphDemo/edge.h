#ifndef EDGE_H
#define EDGE_H

#include "graphwidget.h"

#include <QGraphicsItem>
#include <QGraphicsScene>

class Node;

typedef struct AnimatiedObject {
    int position = 0;
    QGraphicsItem* item;
} AnimatiedObject;

class Edge : public QGraphicsItem
{
public:
    Edge(Node* sourceNode, Node* destNode, GraphWidget* widget);
    void adjust();

    Node *getSource() const;
    Node *getDest() const;

    void addEllipseAnimation(QColor color, int position = 0);

    void drawAnimatedObjects();

    void processAnimations();

    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    enum { Type = UserType + 2 };
    int type() const override { return Type; }
private:
    void addAnimation(QGraphicsItem* item, int position = 0);
    Node *source, *dest;
    GraphWidget* widget;
    QPointF sourcePoint, destPoint;
    int arrowSize;
    QList<AnimatiedObject> animations;
};

#endif // EDGE_H
