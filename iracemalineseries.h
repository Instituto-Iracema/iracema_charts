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
    Q_PROPERTY(qreal lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(qreal yScaleTop READ yScaleTop WRITE setYScaleTop NOTIFY yScaleTopChanged)
    Q_PROPERTY(qreal yScaleBottom READ yScaleBottom WRITE setYScaleBottom NOTIFY yScaleBottomChanged)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(QQmlListProperty<IracemaPointLabel> graphPointLabels READ graphPointLabels NOTIFY graphPointLabelsChanged)
    QML_NAMED_ELEMENT(IracemaLineSeries)

public:
    explicit IracemaLineSeries(QQuickItem* parent = nullptr);
    ~IracemaLineSeries();

    qreal lineWidth() const {
        return _lineWidth;
    }
    void setLineWidth(qreal newLineWidth) {
        if(qFuzzyCompare(_lineWidth, newLineWidth))
            return;
        _lineWidth = newLineWidth;
        emit lineWidthChanged();
    }

    qreal yScaleTop() const {
        return _yScaleTop;
    }
    void setYScaleTop(qreal newYScaleTop) {
        if(qFuzzyCompare(_yScaleTop, newYScaleTop))
            return;
        _yScaleTop = newYScaleTop;
        emit yScaleTopChanged();
    }

    qreal yScaleBottom() const {
        return _yScaleBottom;
    }
    void setYScaleBottom(qreal newYScaleBottom) {
        if(qFuzzyCompare(_yScaleBottom, newYScaleBottom))
            return;
        _yScaleBottom = newYScaleBottom;
        emit yScaleBottomChanged();
    }

    const QVector<QLineF> data() const {
        return _data;
    }
    const QVector<QLineF> dataBuffer() const {
        return _dataBuffer;
    }

    const QList<IracemaPointLabel*> pointLabels() const {
        return _graphPointLabels;
    }
    const QList<IracemaPointLabel*> pointLabelsBuffer() {
        return _graphPointLabelsBuffer;
    }

    const QColor lineColor() const {
        return _lineColor;
    }
    void setLineColor(const QColor &newLineColor) {
        if(_lineColor == newLineColor)
            return;
        _lineColor = newLineColor;
        emit lineColorChanged();
    }

    Q_INVOKABLE QLineF at(int index);
    Q_INVOKABLE QPointF pointAt(int index);
    Q_INVOKABLE int count();

    Q_INVOKABLE void applyDataBuffer();
    Q_INVOKABLE void applyPointLabelsBuffer();

    Q_INVOKABLE void addData(const QVector<QPointF>& data);
    Q_INVOKABLE void addPoint(const QPointF& point);
    Q_INVOKABLE void addPoint(float x, float y);

    Q_INVOKABLE void appendGraphPointLabels(const QPointF& position, const QString& text);
    Q_INVOKABLE void appendGraphPointLabels(qreal x, qreal y, const QString& text);

    Q_INVOKABLE void clearData();

    QQmlListProperty<IracemaPointLabel> graphPointLabels();

private:
    qreal _lineWidth;
    qreal _yScaleTop;
    qreal _yScaleBottom;

    QVector<QLineF> _data;
    QVector<QLineF> _dataBuffer;

    QList<IracemaPointLabel*> _graphPointLabels;
    QList<IracemaPointLabel*> _graphPointLabelsBuffer;

    QColor _lineColor;

    static void _appendGraphPointLabels(QQmlListProperty<IracemaPointLabel>*, IracemaPointLabel*);

    void _addPointToBuffer(const QPointF& point);
    void _deleteGraphPoint();

signals:
    void lineWidthChanged();
    void yScaleTopChanged();
    void yScaleBottomChanged();
    void lineColorChanged();
    void graphPointLabelsChanged();
};

#endif // IRACEMALINESERIES_H
