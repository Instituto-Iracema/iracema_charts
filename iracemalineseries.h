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
    QColor _lineColor = Qt::black;
    qreal _lineWidth = 1;

    QVector<QPointF> _data;
    QVector<QPointF> _dataBuffer;

    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)

    Q_PROPERTY(qreal lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)

public:
    explicit IracemaLineSeries(QQuickItem *parent = nullptr);

    Q_INVOKABLE void addData(QVector<QPointF> data);
    Q_INVOKABLE void addPoint(QPointF point);
    Q_INVOKABLE void addPoint(float x, float y);

    const QColor &lineColor() const;
    void setLineColor(const QColor &newLineColor);

    qreal lineWidth() const;
    void setLineWidth(qreal newLineWidth);

signals:

    void lineColorChanged();
    void lineWidthChanged();
};

#endif // IRACEMALINESERIES_H
