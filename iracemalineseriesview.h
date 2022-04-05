#ifndef IRACEMALINESERIESVIEW_H
#define IRACEMALINESERIESVIEW_H

#include "iracemalineseries.h"

#include <QPainter>
#include <QPixmap>
#include <QQuickPaintedItem>
#include <QSharedPointer>
#include <QtQml>

class IracemaLineSeriesView : public QQuickPaintedItem
{
    Q_OBJECT
//    Q_PROPERTY(QList<IracemaLineSeries *> lines READ lines WRITE setLines NOTIFY linesChanged)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(QSizeF gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged)
    QML_NAMED_ELEMENT(IracemaLineSeriesView)

private:
    QPainter *_pixmapPainter;
    QPixmap _pixmap;
    QColor _gridColor = Qt::lightGray;
    QSizeF _gridSize = QSizeF(0, 0);
    QList<IracemaLineSeries *> _lines;

    void _drawLine(QPainter *painter, IracemaLineSeries *line);
    void _drawHorizontalGrid(QPainter *painter);
    void _drawVerticalGrid(QPainter *painter);
    void _drawGrid(QPainter *painter);

public:
    explicit IracemaLineSeriesView(QQuickItem *parent = nullptr);
    ~IracemaLineSeriesView();

    void paint(QPainter *painter);

    Q_INVOKABLE void updateChart();
    Q_INVOKABLE void updateChartSize();

    const QList<IracemaLineSeries *> &lines() const;
    void setLines(const QList<IracemaLineSeries *> &newLines);

    const QColor &gridColor() const;
    void setGridColor(const QColor &newGridColor);

    const QSizeF &gridSize() const;
    void setGridSize(const QSizeF &newGridSize);

    void componentComplete();

signals:
    void linesChanged();
    void gridColorChanged();
    void gridSizeChanged();

};

#endif // IRACEMALINESERIESVIEW_H
