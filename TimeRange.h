#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>

using b_ptime = boost::posix_time::ptime;
using b_time_duration = boost::posix_time::time_duration;

class TimeRange
{
public:
    TimeRange() = default;

    explicit TimeRange(const b_ptime& ptBeg, const b_ptime& ptEnd);

    bool isValid() const noexcept;

    const b_ptime& getBeg() const noexcept;
    void setBeg(const b_ptime& ptTime) noexcept;

    const b_ptime& getEnd() const noexcept;
    void setEnd(const b_ptime& ptTime) noexcept;

    b_time_duration getDuration() const noexcept;

private:
    void corectOrder() noexcept;

    b_ptime m_ptBeg;
    b_ptime m_ptEnd;
};

