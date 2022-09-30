#ifndef IRACEMASCALELINE_H
#define IRACEMASCALELINE_H

#include <QSGFlatColorMaterial>
#include <QQuickItem>
#include <QPointF>
#include <QColor>


class IracemaScaleLine : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF initialPoint READ initialPoint WRITE setInitialPoint NOTIFY initialPointChanged)
    Q_PROPERTY(QPointF finalPoint READ finalPoint WRITE setFinalPoint NOTIFY finalPointChanged)
    Q_PROPERTY(qreal lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(qreal yScaleTop READ yScaleTop WRITE setYScaleTop NOTIFY yScaleTopChanged)
    Q_PROPERTY(qreal yScaleBottom READ yScaleBottom WRITE setYScaleBottom NOTIFY yScaleBottomChanged)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    QML_NAMED_ELEMENT(IracemaScaleLine)

private:
    QPointF _initialPoint;
    QPointF _finalPoint;
    qreal _lineWidth;
    qreal _yScaleTop;
    qreal _yScaleBottom;

    QColor _lineColor;
    QSGFlatColorMaterial* _lineMaterial;

public:
    IracemaScaleLine();

    QPointF initialPoint() const {
        return _initialPoint;
    }
    void setInitialPoint(QPointF newPoint) {
        if(_initialPoint == newPoint)
            return;

        _initialPoint = newPoint;
        emit initialPointChanged();
    }

    QPointF finalPoint() const {
        return _finalPoint;
    }

    void setFinalPoint(QPointF newPoint) {
        if(_finalPoint == newPoint)
            return;

        _finalPoint = newPoint;
        emit finalPointChanged();
    }

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
        if (qFuzzyCompare(_yScaleTop, newYScaleTop))
            return;

        _yScaleTop = newYScaleTop;
        emit yScaleTopChanged();
    }

    qreal yScaleBottom() const {
        return _yScaleBottom;
    }

    void setYScaleBottom(qreal newYScaleBottom) {
        if (qFuzzyCompare(_yScaleBottom, newYScaleBottom))
            return;

        _yScaleBottom = newYScaleBottom;
        emit yScaleBottomChanged();
    }

    const QColor lineColor() const {
        return _lineColor;
    }

    void setLineColor(const QColor &newLineColor) {
        if (_lineColor == newLineColor)
            return;

        _lineColor = newLineColor;
        _lineMaterial->setColor(_lineColor);
        emit lineColorChanged();
    }

    QSGFlatColorMaterial *lineMaterial() const
    {
        return _lineMaterial;
    }

signals:
    void initialPointChanged();
    void finalPointChanged();
    void lineWidthChanged();
    void yScaleTopChanged();
    void yScaleBottomChanged();
    void lineColorChanged();
};

#endif // IRACEMASCALELINE_H


