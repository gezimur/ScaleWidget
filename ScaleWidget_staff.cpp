#include "ScaleWidget_staff.h"

b_time_duration operator*(const b_time_duration& tdDuration, double dMult)
{
    return boost::posix_time::microseconds(static_cast<long long int>(tdDuration.total_microseconds() * dMult));
}

double abs_to_relative(int iVal, int iBeg, int iEnd)
{
    return static_cast<double>(iVal - iBeg) / (iEnd - iBeg);
}

double abs_to_relative(const b_ptime& ptVal, const b_ptime& ptBeg, const b_ptime& ptEnd)
{
    return static_cast<double>((ptVal - ptBeg).total_microseconds()) / (ptEnd - ptBeg).total_microseconds();
}

double abs_to_relative(const b_ptime& ptVal, const TimeRange& crRange)
{
    return abs_to_relative(ptVal, crRange.getBeg(), crRange.getEnd());
}

int relative_to_abs(double dVal, int iBeg, int iEnd)
{
    return iBeg + (iEnd - iBeg) * dVal;
}

b_ptime relative_to_abs(double dVal, const b_ptime& ptBeg, const b_ptime& ptEnd)
{
    return ptBeg + (ptEnd - ptBeg) * dVal;
}

b_ptime relative_to_abs(double dVal, const TimeRange& crRange)
{
    return relative_to_abs(dVal, crRange.getBeg(), crRange.getEnd());
}
