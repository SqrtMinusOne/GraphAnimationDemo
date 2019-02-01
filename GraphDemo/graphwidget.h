#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QTimer>

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);
    void itemMoved();

    void scaleView(qreal scaleFactor);

    void zoomIn();

    void zoomOut();

    // QWidget interface
    void keyPressEvent(QKeyEvent *event) override;

protected:
    // QObject interface
    void timerEvent(QTimerEvent *event) override;


    // QGraphicsView interface
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    QTimer* animationTimer;

private slots:
    void processAnimations();
};

#endif // GRAPHWIDGET_H
