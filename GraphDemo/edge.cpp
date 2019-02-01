#include "edge.h"
#include "node.h"

#include <qmath.h>

Edge::Edge(Node *sourceNode, Node *destNode, GraphWidget* widget)
{
    setAcceptedMouseButtons(nullptr);
    source = sourceNode;
    dest = destNode;
    arrowSize = 20;
    source->addEdge(this);
    dest->addEdge(this);
    this->widget = widget;
    adjust();
}

void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * source->getW() / 2) / length,
                           (line.dy() * source->getH() / 2) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

Node *Edge::getSource() const
{
    return source;
}

Node *Edge::getDest() const
{
    return dest;
}

void Edge::addEllipseAnimation(QColor color, int position){
    QGraphicsEllipseItem* ellipse = widget->scene()->addEllipse(0, 0, 10, 10);
    ellipse->setPen(QPen(color, 0));
    ellipse->setBrush(QBrush(color));
    addAnimation(ellipse, position);
}

void Edge::drawAnimatedObjects(){
    for (int i = 0; i < animations.length(); i++) {
        qreal coef = 1 - static_cast<qreal>(animations[i].position)/100;
        qreal xs = sourcePoint.x() - 5;
        qreal ys = sourcePoint.y() - 5;
        qreal xd = destPoint.x() - 5;
        qreal yd = destPoint.y() - 5;
        qreal newx = xs*coef + xd * (1-coef);
        qreal newy = ys*coef + yd * (1-coef);
        animations[i].item->setX(newx);
        animations[i].item->setY(newy);
        animations[i].item->update();
    }
}

void Edge::processAnimations(){
    for (int i = 0; i < animations.length(); i++) {
        animations[i].position = (animations[i].position + 1) % 100;
    }
    update();
}


QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    double angle = std::atan2(-line.dy(), line.dx());
    /*QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI / 3) * arrowSize);
    QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI - M_PI / 3) * arrowSize);*/
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->setBrush(Qt::black);
    //painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
    drawAnimatedObjects();
}

void Edge::addAnimation(QGraphicsItem *item, int position){
    item->setParentItem(this);
    item->setPos(sourcePoint);
    item->update();
    AnimatiedObject object;
    object.item = item;
    object.position = position;
    animations.push_back(object);
}
