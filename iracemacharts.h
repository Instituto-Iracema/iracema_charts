#ifndef IRACEMACHARTS_H
#define IRACEMACHARTS_H

#include <QQuickItem>

class IracemaCharts : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(IracemaCharts)
    QML_NAMED_ELEMENT(IracemaCharts)

public:
    explicit IracemaCharts(QQuickItem *parent = nullptr);
    ~IracemaCharts() override;
};

#endif // IRACEMACHARTS_H
