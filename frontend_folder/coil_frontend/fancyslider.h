#ifndef FANCYSLIDER_H
#define FANCYSLIDER_H

#include <QWidget>
#include <QSlider>

class FancySlider : public QSlider
{
    Q_OBJECT
public:
    explicit FancySlider(QWidget *parent = nullptr);
    explicit FancySlider(Qt::Orientation orientation, QWidget *parent = nullptr);

protected:
    virtual void sliderChange(SliderChange change);

signals:

public slots:
};

#endif // FANCYSLIDER_H
