#include "node.h"

#include <QStyleOption>


Node::Node(GraphWidget *graphWidget)
    :graph(graphWidget)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    x = -15;
    y = -15;
    w = 30;
    h = 30;
}


QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(x - adjust, y - adjust, w + adjust, h + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(x, y, w, h);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Заливка
    QColor color = Qt::yellow;
    if (option->state & QStyle::State_Sunken) {
        color = Qt::darkYellow;
    }
    painter->setBrush(color);

    //Граница
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(x, y, w, h);
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}

QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}


void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

int Node::getH() const
{
    return h;
}

int Node::getW() const
{
    return w;
}

int Node::getY() const
{
    return y;
}

int Node::getX() const
{
    return x;
}

