#ifndef PAINT_H
#define PAINT_H

#include <QMainWindow>
#include <QtWidgets>
#include <homemenu.h>
QT_BEGIN_NAMESPACE
namespace Ui { class Paint; }
QT_END_NAMESPACE
class Paint : public QMainWindow
{
    Q_OBJECT

public:
    Paint(QWidget *parent = nullptr);
    ~Paint();
    void paintEvent(QPaintEvent*);

public slots:
    void SaveEvent();
    void OpenEvent1();
    //void NewEvent();
    //void ExitEvent();
    void RepaintEvent();
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
private:
    void calculatePenAndBrush();
private:
    QImage BackgroundeImage;
    QLabel * PositionLable;
    // Width Height
    const qint32 Width=500,Height=500;
    //Menu
    HomeMenu* PaintMenu;
    // pensil
    QList<QPoint> PensilePointArr;
    QList<QPen> PensilePenArr;
    QList<qint32> PensileTimeArr;
    // Lines
    QStandardItemModel LinesModel;
    QList<QLine> LineArr;
    QList<QPen> LinePenArr;
    QList<qint32> LineTimeArr;
    //Rectungles
    QStandardItemModel RectModel;
    QList<QRect> RectArr;
    QList<QPen> RectPenArr;
    QList<QBrush> RectBrushArr;
    QList<qint32> RectTimeArr;
    // Elipse
    QStandardItemModel ElipseModel;
    QList<QRect> EllipseArr;
    QList<QPen> EllipsePenArr;
    QList<QBrush> EllipseBrushArr;
    QList<qint32> EllipseTimeArr;
    //Time
    qint32 TimeIndex=0;
    // Pen Brush
    QPen MyPen;
    QBrush MyBrush;
    Ui::Paint *ui;
};
#endif // PAINT_H
