#pragma once

#include "TimeRange.h"

b_time_duration operator*(const b_time_duration& tdDuration, double dMult);

double abs_to_relative(int iVal, int iBeg, int iEnd);

double abs_to_relative(const b_ptime& ptVal, const b_ptime& ptBeg, const b_ptime& ptEnd);

double abs_to_relative(const b_ptime& ptVal, const TimeRange& crRange);

int relative_to_abs(double dVal, int iBeg, int iEnd);

b_ptime relative_to_abs(double dVal, const b_ptime& ptBeg, const b_ptime& ptEnd);

b_ptime relative_to_abs(double dVal, const TimeRange& crRange);
