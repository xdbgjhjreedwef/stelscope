/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chartview.h"
#include <QtGui/QMouseEvent>
#include <QtCore/QDebug>
#include <QtCharts/QAbstractAxis>

#include <QtCharts/QAbstractAxis>

#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>

#include <QGraphicsEllipseItem>

#include <QDebug>

#include <math.h>

QT_CHARTS_USE_NAMESPACE

#define MAX_ELEVATION 90
#define MAX_AZIMUTH 360


ChartView::ChartView(QWidget *parent)
    : QChartView(parent),
      starsSeries(new QtCharts::QScatterSeries())
{
    //TODO: init private stuff in params
    //TODO: forward declare some stuff
    chart = new MPolarChart();
    chart->setBackgroundBrush(QBrush(QColor(Qt::transparent)));
    azimuthAxis = new QCategoryAxis();
    azimuthAxis->setRange(0,MAX_AZIMUTH);
    for(unsigned int i = 0; i < MAX_AZIMUTH; i += 15)
    {
        switch (i) {
        case 0:
            azimuthAxis->append(QString("<font size=5 color=\"blue\">N</font>"), i);
            break;
        case 90:
            azimuthAxis->append(QString("<font size=5 color=\"orange\">E</font>"), i);
            break;
        case 180:
            azimuthAxis->append(QString("<font size=5 color=\"red\">S</font>"), i);
            break;
        case 270:
            azimuthAxis->append(QString("<font size=5 color=\"green\">W</font>"), i);
            break;
        default:
            azimuthAxis->append(QString::number(i), i);
            break;
        }

    }
    azimuthAxis->setLabelFormat("%.1f");
    QFont labelsFont = azimuthAxis->labelsFont();
    labelsFont.setPointSize(10);
    azimuthAxis->setLabelsFont(labelsFont);
    //azimuthAxis->setShadesVisible(true);
    azimuthAxis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    azimuthAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
    chart->addAxis(azimuthAxis, QPolarChart::PolarOrientationAngular);

    elevationAxis = new QCategoryAxis;
    elevationAxis->setRange(0, MAX_ELEVATION);
    for(unsigned int i = 0; i <= MAX_ELEVATION; i += 10)
        elevationAxis->append(QString::number(MAX_ELEVATION-i), i);
    elevationAxis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    elevationAxis->setLabelsVisible(true);
    elevationAxis->setRange(0,MAX_ELEVATION);
    chart->addAxis(elevationAxis, QPolarChart::PolarOrientationRadial);



    azimuthAxis->setRange(0, 360);
    //angularAxis->setReverse(true);
    //TODO: zoom w/ rubberband
    //setRubberBand();

    setChart(chart);
    setRenderHint(QPainter::Antialiasing);
    //chart->legend()->hide();
    adjustSize();

    ///TODO:
    //chart->setTransform()
    addSquare();

    QList<QPointF> upPoints = {QPointF(145, MAX_ELEVATION-45),
                              QPointF(130, MAX_ELEVATION-45)};
    QList<QPointF> lowPoints = {QPointF(145, MAX_ELEVATION-55),
                              QPointF(130, MAX_ELEVATION-55)};

    addArea(upPoints,lowPoints);

    starsSeries->setUseOpenGL(true);
    chart->addSeries(starsSeries);
    starsSeries->attachAxis(elevationAxis);
    starsSeries->attachAxis(azimuthAxis);
}

void ChartView::addArea(const QList<QPointF> &upPoints,
                        const QList<QPointF> &lowPoints) const
{
    QLineSeries *series21 = new QLineSeries();
    series21->setName("inner");
    series21->append(upPoints);
    QLineSeries *series22 = new QLineSeries();
    series22->setName("outer");
    series22->append(lowPoints);

    QAreaSeries *series20 = new QAreaSeries();
    series20->setName("area");
    series20->setUpperSeries(series21);
    series20->setLowerSeries(series22);

    series20->setPen(QPen(QBrush(QColor(Qt::green)),3.0));
    chart->addSeries(series20);
    series20->attachAxis(elevationAxis);
    series20->attachAxis(azimuthAxis);

    series20->setPointsVisible(true);
    series20->setPointLabelsClipping(true);
    series20->setPointLabelsVisible(true);
}

void ChartView::addSquare() const
{

    QScatterSeries *series30 = new QScatterSeries();
    series30->setName("square");

    series30->append(atan2(20/57.2958,50/57.2958)*57.2958,hypot(20,50));

    series30->append(atan2(20/57.2958,70/57.2958)*57.2958,hypot(20,70));



    series30->append(atan2(30/57.2958,60/57.2958)*57.2958,hypot(40,50));

    series30->append(atan2(40/57.2958,50/57.2958)*57.2958,hypot(40,50));
    series30->append(atan2(40/57.2958,70/57.2958)*57.2958,hypot(40,70));

    series30->setUseOpenGL(true);
    chart->addSeries(series30);
    series30->attachAxis(elevationAxis);
    series30->attachAxis(azimuthAxis);

    connect(series30,&QScatterSeries::clicked,[=](const QPointF &point){qDebug()<<"square clicked @ (Az,El):"<<point;});
    //        QScatterSeries::replace()
    //        NOTE: For that I use a double buffer QVector<QVector<QPointF>> *_lists:


    QTransform transform;
    transform.setMatrix(1.0,0.0,0,
                        0.0,1.0,0.0,
                        0.0,0.0,1.0);
//    chart->setTransform(transform);
//    chart->setRotation(5
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    QChartView::mouseReleaseEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    QChartView::mousePressEvent(event);

    auto const widgetPos = event->localPos();
    auto const scenePos = mapToScene(QPoint(static_cast<int>(widgetPos.x()), static_cast<int>(widgetPos.y())));
    //TODO: QPointF
    auto const chartItemPos = chart->mapFromScene(scenePos);
    auto const valueGivenSeries = chart->mapToValue(chartItemPos);
    qDebug() << "valSeries:" << valueGivenSeries << itemAt(mapFromScene(event->pos()));
    QGraphicsItem *it = itemAt(mapFromScene(event->pos()));
    qDebug()<<"type"<<it->type();
    //NOTE: try cast?
    if(it->type()==4/*QGraphicsEllipseItem::type()*/)
        it->setScale(it->scale()*1.5);
}

void ChartView::addPoints(const QList<QPair<float,QPointF>> &points)
{

    //QXYSeriesPrivate *d = reinterpret_cast<QXYSeriesPrivate*> ();
    starsSeries->setName("stars");
    //starsSeries->setMarkerSize(10);
    //starsSeries->blockSignals(true);
    auto i = points.constBegin();
    while (i != points.constEnd()) {
        starsSeries->append(i->second);
        ///NOTE: reimplement?
        /// s
        ///
       // starsSeries->setMarkerSize(20.);//
        const QPointF p =  chart->mapToPosition(starsSeries->at(0),starsSeries);
        QGraphicsItem *it = itemAt(p.toPoint());
        if(it->type()==4/*QGraphicsEllipseItem::type()*/)
            it->setScale(i->first);
        ++i;

    }

}
