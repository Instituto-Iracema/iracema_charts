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

public:
    IracemaPointLabel();
    IracemaPointLabel(QPointF graphPoint, QString text);

    QPointF graphPoint() const {
        return _graphPoint;
    }
    void setGraphPoint(QPointF newGraphPoint) {
        if(_graphPoint == newGraphPoint)
            return;
        _graphPoint = newGraphPoint;
        emit graphPointChanged();
    }

    const QString &text() const {
        return _text;
    }
    void setText(const QString &newText) {
        if(_text == newText)
            return;
        _text = newText;
        emit textChanged();
    }

private:
    QPointF _graphPoint;
    QString _text;

signals:
    void graphPointChanged();
    void textChanged();
};

#endif // IRACEMAPOINTLABEL_H
