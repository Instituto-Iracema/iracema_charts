#ifndef IRACEMASCALELABEL_H
#define IRACEMASCALELABEL_H

#include <QQuickItem>

class IracemaScaleLabel : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int scalePoint READ scalePoint WRITE setScalePoint NOTIFY scalePointChanged)
    Q_PROPERTY(QString scaleText READ scaleText WRITE setScaleText NOTIFY scaleTextChanged)
    QML_NAMED_ELEMENT(IracemaScaleLabel)

private:
    int _scalePoint= 0;
    QString _scaleText = "";

public:
    IracemaScaleLabel();
    int scalePoint() const;
    void setScalePoint(int newScalePoint);

    const QString &scaleText();
    void setScaleText(const QString &newScaleText);

signals:
    void scalePointChanged();
    void scaleTextChanged();
};

#endif // IRACEMASCALELABEL_H
