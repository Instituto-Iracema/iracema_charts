#ifndef IRACEMALINESERIESVIEW_H
#define IRACEMALINESERIESVIEW_H

#include "iracemalineseries.h"

#include <QPainter>
#include <QQuickPaintedItem>
#include <QSizeF>

class IracemaLineSeriesView : public QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY(IracemaLineSeriesView)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(QSizeF gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged)
    Q_PROPERTY(QSizeF gridOffset READ gridOffset WRITE setGridOffset NOTIFY gridOffsetChanged)
    Q_PROPERTY(unsigned int updateTime READ updateTime WRITE setUpdateTime NOTIFY updateTimeChanged)
    Q_PROPERTY(qreal gridLineWidth READ gridLineWidth WRITE setGridLineWidth NOTIFY gridLineWidthChanged)
    Q_PROPERTY(qreal xScaleBottom READ xScaleBottom WRITE setXScaleBottom NOTIFY xScaleBottomChanged)
    Q_PROPERTY(qreal xScaleTop READ xScaleTop WRITE setXScaleTop NOTIFY xScaleTopChanged)
    Q_PROPERTY(QQmlListProperty<IracemaLineSeries> lines READ lines)
    QML_NAMED_ELEMENT(IracemaLineSeriesView)

private:
    // QProperties

    QColor _gridColor = Qt::gray;
    /**
     * @brief Size of the grid on X and Y axis in pixels
     */
    QSizeF _gridSize = QSizeF(1, 1);
    /**
     * @brief Offset of the grid, from left and top in pixels
     */
    QSizeF _gridOffset = QSizeF(0, 0);
    /**
     * @brief Width of the line of the grid
     */
    qreal _gridLineWidth = 1;

    qreal _xScaleBottom = 0;
    qreal _xScaleTop = 10000;

    unsigned int _updateTime = 50;

    QList<IracemaLineSeries *> _lines;
    QQmlListProperty<IracemaLineSeries> lines();

    QPixmap _pixmap;
    QPainter *_pixmapPainter = new QPainter();

    int _updateTimerId = -1;

    void _drawGridHorizontal(QPainter *painter);
    void _drawGridVertical(QPainter *painter);
    void _drawGrid(QPainter *painter);
    void _drawLineSeries(QPainter *painter, IracemaLineSeries *line);
    void _drawLines();
    qreal _convertValueToNewScale(qreal oldValue, qreal oldScaleBottom, qreal oldScaleTop, qreal newScaleBottom, qreal newScaleTop);

    static void appendLine(QQmlListProperty<IracemaLineSeries> *list, IracemaLineSeries *line);

public:
    explicit IracemaLineSeriesView(QQuickItem *parent = nullptr);

    void paint(QPainter *painter);

    const QColor &gridColor() const;
    void setGridColor(const QColor &newGridColor);

    const QSizeF &gridSize() const;
    void setGridSize(const QSizeF &newGridSize);

    const QSizeF &gridOffset() const;
    void setGridOffset(const QSizeF &newGridOffset);

    unsigned int updateTime() const;
    void setUpdateTime(unsigned int newUpdateTime);

    qreal gridLineWidth() const;
    void setGridLineWidth(qreal newGridLineWidth);

    qreal xScaleBottom() const;
    void setXScaleBottom(qreal newXScaleBottom);

    qreal xScaleTop() const;
    void setXScaleTop(qreal newXScaleTop);

signals:
    void gridColorChanged();
    void gridSizeChanged();
    void gridOffsetChanged();
    void updateTimeChanged();
    void gridLineWidthChanged();
    void xSizeChanged();
    void xScaleBottomChanged();
    void xScaleTopChanged();

protected:
    // QQuickItem interface
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

    // QObject interface
    void timerEvent(QTimerEvent *event);
};

#endif // IRACEMALINESERIESVIEW_H
