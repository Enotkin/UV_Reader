#ifndef CROWNCHARGE_H
#define CROWNCHARGE_H
#include <vector>
#include <list>

#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"

using Contour = std::vector<cv::Point>;

class CrownCharge
{
public:
    CrownCharge(const Contour &starContour);

    //!
    //! \brief Попытка вставки контура в обьект
    //! \param newContour - Контур чьё соседство проверяется
    //! \return true если контур считается соседним, false в остальных случаях
    //!
    bool tryAddContour(const Contour &newContour);

    //!
    //! \brief Проверка оставшегося времени ожидания
    //! \return Возвращает true, если время жизни закончилось
    //!
    bool timeForLifeIsEnd() const ;

    //!
    //! \brief Проверка размера заряда
    //! \return Возвращает true, если размер меньше необходимого.
    //!
    bool isItNoise() const;

    int getLifeTime() const;
    void setLifeTime(int value);

    double getDelta() const;
    void setDelta(double value);
private:
    //!
    //! \brief Контейнер содержащий контуры
    //!
    std::list<Contour> contours;

    //!
    //! \brief Необходимое количество контуров,
    //! чтобы считать что перед нами не шум
    //!
    size_t realChargeSize = 2;

    //!
    //! \brief Максимальное время жизни обьекта,
    //! перед его удалением.
    //!
    int lifeTime = 5;

    //!
    //! \brief Расстояние между центрами масс контуров,
    //! при расстоянии бельшем чем это контура не считаются соседними
    //!
    double delta = 75;

    //!
    //! \brief Оставшеесе время ожидания нового контура.
    //! Если переменная примет нулевое значение,
    //! можно считать что конструирование обьекто закончилось
    //!
    int countToDie = lifeTime;

    cv::Point getCenterMassContour(const Contour &contour) const;
    double distanceBetweenTwoPoints(const cv::Point &first, const cv::Point &second) const;
};

#endif // CROWNCHARGE_H
