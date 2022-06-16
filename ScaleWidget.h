#pragma once

#include <QWidget>

#include "TimeRange.h"

class ScaleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScaleWidget(const TimeRange& crRange);

    void mousePressEvent(QMouseEvent* pEvent) final;
    void mouseReleaseEvent(QMouseEvent* pEvent) final;
    void mouseMoveEvent(QMouseEvent* pEvent) final;
    void wheelEvent(QWheelEvent* pEvent) final;

    void paintEvent(QPaintEvent* pEvent) final;

private:
    void scale(double dPos, double dScale);

    void printDivision(QPainter& rPainter, int iPos);

    void printSupDivision(QPainter& rPainter, int iPos, const b_ptime& ptTime);

    int getMinSectionWidth() const noexcept;

    int m_iMousePos;
    bool m_bScaleGrabbed;

    TimeRange m_Range;
};
