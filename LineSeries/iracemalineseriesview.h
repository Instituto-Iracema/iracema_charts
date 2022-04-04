#ifndef IRACEMALINESERIESVIEW_H
#define IRACEMALINESERIESVIEW_H

#include <QQuickPaintedItem>
#include <QtQml>

class IracemaLineSeriesView : public QQuickPaintedItem
{
    Q_OBJECT
    QML_NAMED_ELEMENT(IracemaLineSeriesView)
public:
    explicit IracemaLineSeriesView(QQuickItem *parent = nullptr);

    // QQuickPaintedItem interface
public:
    void paint(QPainter *painter);
};

#endif // IRACEMALINESERIESVIEW_H
