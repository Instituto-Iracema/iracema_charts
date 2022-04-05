#ifndef IRACEMALINESERIES_H
#define IRACEMALINESERIES_H

#include <QPointF>
#include <QQuickItem>
#include <QVector>

class IracemaLineSeries : public QQuickItem
{
    Q_OBJECT
    QML_NAMED_ELEMENT(IracemaLineSeries)

private:
    QVector<QPointF> _data;
    QVector<QPointF> _dataBuffer;

public:
    explicit IracemaLineSeries(QQuickItem *parent = nullptr);

    Q_INVOKABLE void addData(QVector<QPointF> data);
    Q_INVOKABLE void addPoint(QPointF point);
    Q_INVOKABLE void addPoint(float x, float y);

signals:

};

#endif // IRACEMALINESERIES_H
