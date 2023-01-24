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

#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>

#include <QtCharts/QPolarChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QScatterSeries>

QT_CHARTS_USE_NAMESPACE
//#include "/usr/include/qt5/QtCharts/5.15.5/QtCharts/private/qscatterseries_p.h"


////QT_FORWARD_DECLARE_CLASS(QScatterSeriesPrivate)
//class MXYSeries : public QtCharts::QScatterSeries
//{
//    Q_OBJECT
////    void aMethod()
////    {
////      QDeclarativeTextEditPrivate *d = reinterpret_cast<QDeclarativeTextEditPrivate *>(QDeclarativeItem::d_ptr.data());
////      QTextDocument *d_doc = d->document;
////      ...
////    }
//public:
//    void dMethod()
//    {
//        QtCharts::QScatterSeriesPrivate *d = reinterpret_cast<QtCharts::QScatterSeriesPrivate *>
//                (d_ptr.data());
//        QtCharts::QXYSeriesPrivate *d1 = reinterpret_cast<QtCharts::QXYSeriesPrivate *>(d);
//        d1;
//        ///TODO: copy d_stuff
//    }

//};

class MValueAxis : public QtCharts::QValueAxis
{
    Q_OBJECT
public:
    MValueAxis(QObject *parent = nullptr){};
};

class MPolarChart : public QtCharts::QPolarChart
{
    Q_OBJECT
public:
    explicit MPolarChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()){};
};



class ChartView : public QtCharts::QChartView
{
public:
    ChartView(QWidget *parent = 0);
    void addPoints(const QList<QPair<float, QPointF> > &points);
    void addArea(const QList<QPointF> &upPoints, const QList<QPointF> &lowPoints) const;
    void addSquare() const;
protected:
  //  void keyPressEvent(QKeyEvent *event);

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //void switchChartType();
    QtCharts::QCategoryAxis *elevationAxis;
    QtCharts::QCategoryAxis *azimuthAxis;
    MPolarChart *chart;
    QtCharts::QScatterSeries *starsSeries;
};

#endif
