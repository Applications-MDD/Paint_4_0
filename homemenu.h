#ifndef HOMEMENU_H
#define HOMEMENU_H

#include <QtWidgets>

class HomeMenu : public QWidget
{
    Q_OBJECT
public:
    explicit HomeMenu(QWidget *parent = nullptr);
public slots:
void PenButtonPressed();
void BrushButtonPressed();
signals:
public:
    QStandardItemModel PaintDeviseModel;
    QListView* PaintDevicesView;
    QStandardItemModel TransformeModel;
    QListView* TransformView;
    QStandardItemModel ShapesModel;
    QListView* ShapesView;
    QListView * CurrentLineView;
    QListView * CurrentRectView;
    QListView * CurrentEllipseView;
    QComboBox PenTypeBox,BrushTypeBox;
    QComboBox PenSizeBox;
    QPen BorderPen=QPen(Qt::black);
    QPushButton PenButton;
    QBrush FillBrush=QBrush(Qt::white);
    QPushButton BrushButton;
    QStandardItemModel CurrentLineModel,CurrentRectModel,CurrentEllipseModel;
};

#endif // HOMEMENU_H
