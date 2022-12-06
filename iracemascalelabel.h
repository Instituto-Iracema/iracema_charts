#ifndef IRACEMASCALELABEL_H
#define IRACEMASCALELABEL_H

#include <QQuickItem>

class IracemaScaleLabel : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int scalePoint READ scalePoint WRITE setScalePoint NOTIFY scalePointChanged)
    Q_PROPERTY(QString scaleText READ scaleText WRITE setScaleText NOTIFY scaleTextChanged)
    QML_NAMED_ELEMENT(IracemaScaleLabel)

public:
    IracemaScaleLabel();

    int scalePoint() const {
        return _scalePoint;
    }
    void setScalePoint(int newScalePoint) {
        if(_scalePoint == newScalePoint)
            return;
        _scalePoint = newScalePoint;
        emit scalePointChanged();
    }

    const QString& scaleText() {
        if(_scaleText.isEmpty())
            _scaleText = QString::number(_scalePoint);

        return _scaleText;
    }
    void setScaleText(const QString &newScaleText) {
        if(_scaleText == newScaleText)
            return;
        _scaleText = newScaleText;
        emit scaleTextChanged();
    }

private:
    int _scalePoint;
    QString _scaleText;

signals:
    void scalePointChanged();
    void scaleTextChanged();
};

#endif // IRACEMASCALELABEL_H
