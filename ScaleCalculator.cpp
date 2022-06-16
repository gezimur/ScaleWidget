#include "ScaleCalculator.h"

enum enu_scale
{
    e_1_sec = 0,
    e_5_sec,
    e_10_sec,
    e_30_sec,

    e_1_min,
    e_5_min,
    e_10_min,
    e_30_min,

    e_1_hour,
    e_2_hour,
    e_4_hour,
    e_8_hour,
    e_12_hour,

    e_1_day,
    e_cnt
};

b_time_duration get_scale(enu_scale eScale)
{
    using namespace boost::posix_time;

    switch (eScale)
    {
    case enu_scale::e_1_sec:
        return seconds(1);
    case enu_scale::e_5_sec:
        return seconds(5);
    case enu_scale::e_10_sec:
        return seconds(10);
    case enu_scale::e_30_sec:
        return seconds(30);
    case enu_scale::e_1_min:
        return minutes(1);
    case enu_scale::e_5_min:
        return minutes(5);
    case enu_scale::e_10_min:
        return minutes(10);
    case enu_scale::e_30_min:
        return minutes(30);
    case enu_scale::e_1_hour:
        return hours(1);
    case enu_scale::e_2_hour:
        return hours(2);
    case enu_scale::e_4_hour:
        return hours(4);
    case enu_scale::e_8_hour:
        return hours(8);
    case enu_scale::e_12_hour:
        return hours(12);
    case enu_scale::e_1_day:
        return hours(24);
    default:
        return pos_infin;
    }
}

b_time_duration get_scale(int iScale)
{
    return get_scale(static_cast<enu_scale>(iScale));
}

b_time_duration get_max_scale()
{
    return get_scale( static_cast<int>(enu_scale::e_cnt) - 1 );
}

b_time_duration mult_scale(const b_time_duration& tdMinScale)
{
    auto tdScale = get_max_scale();
    std::vector<double> vMult = {2, 2.5};
    int iMult = 0;

    while (tdMinScale > tdScale)
    {
        tdScale = tdScale * vMult[iMult];

        ++iMult;
        iMult %= vMult.size();
    }

    return tdScale;
}

b_ptime round(const b_ptime& ptDateTime, const b_time_duration& tdScale)
{
    b_time_duration tdTime = ptDateTime.time_of_day();
    auto iSec = (tdTime.total_seconds() / tdScale.total_seconds()) * tdScale.total_seconds();

    return {ptDateTime.date(), boost::posix_time::seconds(iSec)};
}

ScaleCalculator::ScaleCalculator(const TimeRange& crRange, int iMaxDivisionCnt)
    : m_Range(crRange)
{
    auto tdMinScale = crRange.getDuration() / iMaxDivisionCnt;
    calcScale(tdMinScale);
    calcFirstDivision();
}

const b_time_duration& ScaleCalculator::getScale() const noexcept
{
    return m_tdScale;
}

const b_ptime& ScaleCalculator::getFirstDivision() const noexcept
{
    return m_ptFirstDivision;
}

const b_time_duration& ScaleCalculator::getSupScale() const noexcept
{
    return m_tdSupScale;
}

const b_ptime& ScaleCalculator::getFirstSupDivision() const noexcept
{
    return m_ptFirstSupDivision;
}


void ScaleCalculator::calcScale(const b_time_duration& tdMinScale)
{
    int i = 0;

    while (tdMinScale > get_scale(i))
        ++i;

    auto tdScale = get_scale(i);
    if (tdScale.is_pos_infinity())
        m_tdSupScale = mult_scale(tdMinScale);
    else
        m_tdSupScale = tdScale;

    m_tdScale = m_tdSupScale / 5;
}

void ScaleCalculator::calcFirstDivision()
{
    m_ptFirstSupDivision = round(m_Range.getBeg() + m_tdSupScale, m_tdSupScale);

    m_ptFirstDivision = m_ptFirstSupDivision;
    while (m_Range.getBeg() < (m_ptFirstDivision - m_tdScale))
        m_ptFirstDivision -= m_tdScale;
}
