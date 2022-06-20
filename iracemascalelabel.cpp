#include "iracemascalelabel.h"

IracemaScaleLabel::IracemaScaleLabel()
{

}

int IracemaScaleLabel::scalePoint() const
{
    return _scalePoint;
}

void IracemaScaleLabel::setScalePoint(int newScalePoint)
{
    if (_scalePoint == newScalePoint)
        return;
    _scalePoint = newScalePoint;
    emit scalePointChanged();
}

const QString &IracemaScaleLabel::scaleText()
{
    if(_scaleText.isEmpty())
        _scaleText = QString::number(_scalePoint);

    return _scaleText;
}

void IracemaScaleLabel::setScaleText(const QString &newScaleText)
{
    if (_scaleText == newScaleText)
        return;
    _scaleText = newScaleText;
    emit scaleTextChanged();
}
