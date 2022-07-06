#ifndef IRACEMALINESERIES_H
#define IRACEMALINESERIES_H

#include <QLineF>
#include <QPointF>
#include <QQuickItem>
#include <QSGFlatColorMaterial>
#include <QVector>
#include <iracemapointlabel.h>

class IracemaLineSeries : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(qreal lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(qreal yScaleTop READ yScaleTop WRITE setYScaleTop NOTIFY yScaleTopChanged)
    Q_PROPERTY(qreal yScaleBottom READ yScaleBottom WRITE setYScaleBottom NOTIFY yScaleBottomChanged)
    Q_PROPERTY(QQmlListProperty<IracemaPointLabel> graphPointLabels READ graphPointLabels NOTIFY graphPointLabelsChanged)
    QML_NAMED_ELEMENT(IracemaLineSeries)

private:
    QColor _lineColor = Qt::black;
    QSGFlatColorMaterial *_lineMaterial;
    qreal _lineWidth = 1;
    qreal _yScaleTop = 1000;
    qreal _yScaleBottom = 0;

    QVector<QLineF> _data;
    QVector<QLineF> _dataBuffer;

    QList<IracemaPointLabel *> _graphPointLabels;
    QList<IracemaPointLabel *> _graphPointLabelsBuffer;

    void _addPointToBuffer(QPointF point);

    QQmlListProperty<IracemaPointLabel> graphPointLabels();
    static void appendGraphPointLabels(QQmlListProperty<IracemaPointLabel> *list, IracemaPointLabel *label);

public:
    explicit IracemaLineSeries(QQuickItem *parent = nullptr);
    ~IracemaLineSeries();

    Q_INVOKABLE void addData(QVector<QPointF> data);
    Q_INVOKABLE void addPoint(QPointF point);
    Q_INVOKABLE void addPoint(float x, float y);
    Q_INVOKABLE void applyDataBuffer();
    Q_INVOKABLE void applyPointLabelsBuffer();
    Q_INVOKABLE QLineF at(int index);
    Q_INVOKABLE QPointF pointAt(int index);
    Q_INVOKABLE int count();
    Q_INVOKABLE void clearData();
    Q_INVOKABLE void appendGraphPointLabels(QPointF position, QString text);
    Q_INVOKABLE void appendGraphPointLabels(qreal x, qreal y, QString text);

    const QColor &lineColor() const;
    void setLineColor(const QColor &newLineColor);

    qreal lineWidth() const;
    void setLineWidth(qreal newLineWidth);

    const QVector<QLineF> &data() const;
    const QList<IracemaPointLabel*> &pointLabels() const;

    const QVector<QLineF> &dataBuffer() const;
    const QList<IracemaPointLabel*> pointLabelsBuffer();

    qreal yScaleTop() const;
    void setYScaleTop(qreal newYScaleTop);

    qreal yScaleBottom() const;
    void setYScaleBottom(qreal newYScaleBottom);

    QSGFlatColorMaterial *lineMaterial() const;

signals:

    void lineColorChanged();
    void lineWidthChanged();
    void dataChanged();
    void dataBufferChanged();
    void yScaleTopChanged();
    void yScaleBottomChanged();
    void graphPointLabelsChanged();
};

#endif // IRACEMALINESERIES_H
