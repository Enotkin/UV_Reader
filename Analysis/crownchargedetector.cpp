#include "crownchargedetector.h"
#include <QDebug>

CrownChargeDetector::CrownChargeDetector() {}

CrownChargeDetector::CrownChargeDetector(const SuspectCrownChargeSettings &settings) : suspetctSettings(settings) {}

CrownChargeDetector::~CrownChargeDetector()
{
    if (!suspectCrownCharges.empty())
        suspectCrownCharges.clear();
}

void CrownChargeDetector::findCrownCharges(std::list<Contour> &contours)
{
    contours.sort([](const Contour &a, const Contour &b){ return a.getArea() > b.getArea();});

    //Если нет веток, то все контура это начало новых веток
    if (suspectCrownCharges.empty()){
        for(const auto &contour : contours)
            suspectCrownCharges.emplace_back(contour, suspetctSettings);
        return;
    }

    //Создание селекторов
    std::list<BrancheSelector> selectors;
    for (auto &contour : contours) {
        selectors.emplace_back(contour);
    }

    //Распределение веток для селекторов
    for (auto &selector : selectors)
        for (auto &suspectCrownCharge : suspectCrownCharges)
            if(suspectCrownCharge.checkCompatibility(selector.getContour()))
                selector.addBranche(suspectCrownCharge);

    //Выбор веток селекторами
    for (auto &selector : selectors) {
        selector.selectionBranch();
    }

    //Конец раунда, уменьшение времени жизни обездоленых
    for (auto &suspectCrownCharge : suspectCrownCharges) {
        suspectCrownCharge.endRound();
    }

    //Копирование подтверждённых зарядов
    for (const auto &suspectCrownCharge : suspectCrownCharges) {
        if (suspectCrownCharge.isConfirmedCharge()){
            detectedCharges.push_back(suspectCrownCharge.getCrownCharge());
        }
    }

    //Удаление шумовых разрядов из общей кучи веток
    suspectCrownCharges.remove_if([](const auto &suspectCrownCharge){
        return suspectCrownCharge.isNoise();
    });

    suspectCrownCharges.remove_if([](const auto &suspectCrownCharge){
        return suspectCrownCharge.isConfirmedCharge();
    });

    //Дополнение веток, селекторами без пар
    for (auto &selector : selectors){
        if (!selector.isSelectingEnd())
            suspectCrownCharges.emplace_back(selector.getContour(), suspetctSettings);
    }

    //Сортировка веток
    suspectCrownCharges.sort([](const SuspectCrownCharge &a, const SuspectCrownCharge &b){ return a.getSize() > b.getSize();});
}

std::list<CrownCharge> CrownChargeDetector::getDetectedCharges() const
{
    return detectedCharges;
}

void CrownChargeDetector::setSettings(SuspectCrownChargeSettings settings)
{
    suspetctSettings = settings;
}
