#ifndef IRACEMAPOINTLABEL_H
#define IRACEMAPOINTLABEL_H

#include <QObject>
#include <QQuickItem>

class IracemaPointLabel : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF graphPoint READ graphPoint WRITE setGraphPoint NOTIFY graphPointChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    QML_NAMED_ELEMENT(IracemaPointLabel)

private:
    QPointF _graphPoint;
    QString _text;

public:
    IracemaPointLabel();
    IracemaPointLabel(QPointF graphPoint, QString text);

    QPointF graphPoint() const;
    void setGraphPoint(QPointF newGraphPoint);
    const QString &text() const;
    void setText(const QString &newText);

signals:
    void graphPointChanged();
    void textChanged();
};

#endif // IRACEMAPOINTLABEL_H
