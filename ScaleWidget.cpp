#include "ScaleWidget.h"

#include <iostream>

#include <QMouseEvent>
#include <QWheelEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>

#include "ScaleCalculator.h"
#include "ScaleWidget_staff.h"

bool is_midnight(const b_ptime& ptDateTime)
{
    auto ptTime = ptDateTime.time_of_day();
    return  ptTime.hours() == 0 &&
            ptTime.minutes() == 0 &&
            ptTime.seconds() == 0;
}

QString time_to_string(const b_ptime& ptTime) ///@todo
{
    if (is_midnight(ptTime))
    {
        auto strTime = std::to_string(ptTime.date().day()) + "." + std::to_string(ptTime.date().month());

        return QString::fromStdString(strTime);
    }
    else
    {
        auto strTime = std::to_string(ptTime.time_of_day().hours()) + ":" + std::to_string(ptTime.time_of_day().minutes()) + ":" + std::to_string(ptTime.time_of_day().seconds());
        return QString::fromStdString(strTime);
    }
}

ScaleWidget::ScaleWidget(const TimeRange& crRange)
    : m_iMousePos(0),
      m_bScaleGrabbed(false),
      m_Range(crRange)
{
    setMinimumWidth(10 * getMinSectionWidth());
    setFixedHeight(fontMetrics().lineSpacing() * 4);
}

void ScaleWidget::mousePressEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() != Qt::LeftButton)
        return ;

    m_iMousePos = pEvent->pos().x();
    m_bScaleGrabbed = true;
}

void ScaleWidget::mouseReleaseEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() != Qt::LeftButton)
        return ;

    m_bScaleGrabbed = false;
}

void ScaleWidget::mouseMoveEvent(QMouseEvent* pEvent)
{
    if (!m_bScaleGrabbed)
        return;

    auto iShift = m_iMousePos - pEvent->pos().x();
    m_iMousePos = pEvent->pos().x();
    double dShift = abs_to_relative(iShift, 0, geometry().width());

    auto tdShift = m_Range.getDuration() * dShift;

    m_Range.setBeg(m_Range.getBeg() + tdShift);
    m_Range.setEnd(m_Range.getEnd() + tdShift);

    update();
}

void ScaleWidget::wheelEvent(QWheelEvent* pEvent)
{
    double dScale = 1 + static_cast<double>(pEvent->delta()) / (120 * 16);
    double dPos = abs_to_relative(pEvent->pos().x(), 0, geometry().width());

    scale(dPos, dScale);
}

void ScaleWidget::paintEvent(QPaintEvent* pEvent)
{
    QPainter Painter(this);

    QWidget::paintEvent(pEvent);

    ScaleCalculator Calc(m_Range, geometry().width() / getMinSectionWidth());

    auto ptDivision = Calc.getFirstDivision();
    auto ptSupDivision = Calc.getFirstSupDivision();

    auto dPos = abs_to_relative(ptDivision, m_Range);
    auto iPos = relative_to_abs(dPos, 0, geometry().width());

    while (iPos < geometry().width())
    {
        if (ptDivision != ptSupDivision)
            printDivision(Painter, iPos);
        else
        {
            printSupDivision(Painter, iPos, ptDivision);
            ptSupDivision += Calc.getSupScale();
        }

        ptDivision += Calc.getScale();

        dPos = abs_to_relative(ptDivision, m_Range);
        iPos = relative_to_abs(dPos, 0, geometry().width());
    }
}

void ScaleWidget::scale(double dPos, double dScale)
{
    auto tdDuration = m_Range.getDuration() * dScale;

    if (tdDuration.total_seconds() < geometry().width())
        return;

    auto ptPos = relative_to_abs(dPos, m_Range);

    auto ptBeg = ptPos - (ptPos - m_Range.getBeg()) * dScale;
    auto ptEnd = ptBeg + tdDuration;

    m_Range = TimeRange{ptBeg, ptEnd};

    update();
}

void ScaleWidget::printDivision(QPainter& rPainter, int iPos)
{
    rPainter.drawLine(iPos, geometry().height(), iPos, geometry().height() - fontMetrics().lineSpacing() * 1);
}

void ScaleWidget::printSupDivision(QPainter& rPainter, int iPos, const b_ptime& ptTime)
{
    auto iLineY = geometry().height() - fontMetrics().lineSpacing() * 2;

    rPainter.drawLine(iPos, geometry().height(), iPos, iLineY);

    auto qstrText = time_to_string(ptTime);

    auto iWidth = fontMetrics().width(qstrText);
    auto iTextPosX = iPos - iWidth / 2;
    auto iTextPosY = iLineY - 2;

    if (is_midnight(ptTime))
        rPainter.setFont(QFont(font().family(), font().pointSize(), QFont::Bold));
    else
        rPainter.setFont(QFont(font().family(), font().pointSize(), QFont::Bold));

    rPainter.drawText(iTextPosX, iTextPosY, qstrText);
}

int ScaleWidget::getMinSectionWidth() const noexcept
{
    return fontMetrics().width("  00:00:00  ");
}
