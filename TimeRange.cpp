#include "TimeRange.h"

TimeRange::TimeRange(const b_ptime& ptBeg, const b_ptime& ptEnd)
    : m_ptBeg(ptBeg),
      m_ptEnd(ptEnd)
{
    corectOrder();
}

bool TimeRange::isValid() const noexcept
{
    return !m_ptBeg.is_not_a_date_time() && !m_ptEnd.is_not_a_date_time();
}

const b_ptime& TimeRange::getBeg() const noexcept
{
    return m_ptBeg;
}

void TimeRange::setBeg(const b_ptime& ptTime) noexcept
{
    if (ptTime.is_not_a_date_time())
        return ;

    m_ptBeg = ptTime;
    corectOrder();
}

const b_ptime& TimeRange::getEnd() const noexcept
{
    return m_ptEnd;
}

void TimeRange::setEnd(const b_ptime& ptTime) noexcept
{
    if (ptTime.is_not_a_date_time())
        return ;

    m_ptEnd = ptTime;
    corectOrder();
}

b_time_duration TimeRange::getDuration() const noexcept
{
    return m_ptEnd - m_ptBeg;
}

void TimeRange::corectOrder() noexcept
{
    if (m_ptBeg > m_ptEnd)
        std::swap(m_ptBeg, m_ptEnd);
}
