#pragma once

#include "TimeRange.h"

class ScaleCalculator
{
public:
    explicit ScaleCalculator(const TimeRange& crRange, int iMaxDivisionCnt);

    const b_time_duration& getScale() const noexcept;
    const b_ptime& getFirstDivision() const noexcept;

    const b_time_duration& getSupScale() const noexcept;
    const b_ptime& getFirstSupDivision() const noexcept;

private:
    void calcScale(const b_time_duration& tdMinScale);
    void calcFirstDivision();

    TimeRange m_Range;

    b_time_duration m_tdScale;
    b_ptime m_ptFirstDivision;

    b_time_duration m_tdSupScale;
    b_ptime m_ptFirstSupDivision;
};

