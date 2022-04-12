#ifndef IRACEMALINESERIES_H
#define IRACEMALINESERIES_H

#include <QLineF>
#include <QPointF>
#include <QQuickItem>
#include <QVector>

class IracemaLineSeries : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(qreal lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    //TODO review if these properties are necessary
    Q_PROPERTY(QVector<QLineF> data READ data NOTIFY dataChanged)
    Q_PROPERTY(QVector<QLineF> dataBuffer READ dataBuffer NOTIFY dataBufferChanged)
    QML_NAMED_ELEMENT(IracemaLineSeries)

private:
    QColor _lineColor = Qt::black;
    qreal _lineWidth = 1;

    QVector<QLineF> _data;
    QVector<QLineF> _dataBuffer;

    void _addPointToBuffer(QPointF point);


public:
    explicit IracemaLineSeries(QQuickItem *parent = nullptr);

    Q_INVOKABLE void addData(QVector<QPointF> data);
    Q_INVOKABLE void addPoint(QPointF point);
    Q_INVOKABLE void addPoint(float x, float y);
    Q_INVOKABLE void applyBuffer();
    Q_INVOKABLE void clearData();

    const QColor &lineColor() const;
    void setLineColor(const QColor &newLineColor);

    qreal lineWidth() const;
    void setLineWidth(qreal newLineWidth);

    const QVector<QLineF> &data() const;

    const QVector<QLineF> &dataBuffer() const;

signals:

    void lineColorChanged();
    void lineWidthChanged();
    void dataChanged();
    void dataBufferChanged();
};

#endif // IRACEMALINESERIES_H
