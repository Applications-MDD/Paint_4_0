#include "homemenu.h"

HomeMenu::HomeMenu(QWidget *parent) : QWidget(parent)
{
        QHBoxLayout *mainMenuLayout=new QHBoxLayout;
        QHBoxLayout *CurrentShapesLayout=new QHBoxLayout;
        QVBoxLayout *mainLayout=new QVBoxLayout;
        mainLayout->addLayout(mainMenuLayout);
        mainLayout->addWidget(new QSplitter);
        mainLayout->addLayout(CurrentShapesLayout);
        this->setLayout(mainLayout);
        // PaintDevices
        PaintDevicesView=new QListView;
        PaintDevicesView->setModel(&PaintDeviseModel);
        PaintDevicesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        PaintDeviseModel.setItem(0,new QStandardItem("Hand"));
        PaintDeviseModel.setItem(1,new QStandardItem("Pencil"));
        PaintDeviseModel.setItem(2,new QStandardItem("Shape"));
        QVBoxLayout* PaintDevicesLayout=new QVBoxLayout;
        PaintDevicesLayout->addWidget(PaintDevicesView);
        PaintDevicesLayout->addWidget(new QLabel("Paint Devices"));
        mainMenuLayout->addLayout(PaintDevicesLayout);
        // Transform
        TransformView=new QListView;
        TransformView->setModel(&TransformeModel);
        TransformView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        TransformeModel.setItem(0,new QStandardItem("Resize"));
        TransformeModel.setItem(1,new QStandardItem("Replace"));
        TransformeModel.setItem(2,new QStandardItem("Rotate right 90"));
        TransformeModel.setItem(3,new QStandardItem("Rotate left 90"));
        QVBoxLayout * TransformLayout=new QVBoxLayout;
        TransformLayout->addWidget(TransformView);
        TransformLayout->addWidget(new QLabel("Transform"));
        mainMenuLayout->addLayout(TransformLayout);
        //Shapes
        ShapesView=new QListView;
        ShapesView->setModel(&ShapesModel);
        ShapesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ShapesModel.setItem(0,new QStandardItem("Line"));
        ShapesModel.setItem(1,new QStandardItem("Rectangle"));
        ShapesModel.setItem(2,new QStandardItem("Ellipse"));
        QVBoxLayout *ShapesLayout=new QVBoxLayout;
        ShapesLayout->addWidget(ShapesView);
        ShapesLayout->addWidget(new QLabel("Shapes"));
        mainMenuLayout->addLayout(ShapesLayout);
        // Pencile and Brush
        PenTypeBox.addItem("No outline");
        PenTypeBox.addItem("Solid color");
        BrushTypeBox.addItem("No outline");
        BrushTypeBox.addItem("Solid color");
        QVBoxLayout *PenBrushTypeLayout=new QVBoxLayout;
        PenBrushTypeLayout->addWidget(&PenTypeBox);
        PenBrushTypeLayout->addWidget(&BrushTypeBox);
        mainMenuLayout->addLayout(PenBrushTypeLayout);
        // Pen size
        PenSizeBox.addItem("Little");
        PenSizeBox.addItem("Medium");
        PenSizeBox.addItem("Huge");
        mainMenuLayout->addWidget(&PenSizeBox);
        // Pen Color;
        connect(&PenButton,SIGNAL(clicked()),this,SLOT(PenButtonPressed()));
        PenButton.setStyleSheet("background-color: black");
        QVBoxLayout * PenColorLayout=new QVBoxLayout;
        PenColorLayout->addWidget(&PenButton);
        PenColorLayout->addWidget(new QLabel("Color 1"));
        mainMenuLayout->addLayout(PenColorLayout);
        // Brush Color;
        connect(&BrushButton,SIGNAL(clicked()),this,SLOT(BrushButtonPressed()));
        BrushButton.setStyleSheet("background-color: white");
        QVBoxLayout * BrushColorLayout=new QVBoxLayout;
        BrushColorLayout->addWidget(&BrushButton);
        BrushColorLayout->addWidget(new QLabel("Color 2"));
        mainMenuLayout->addLayout(BrushColorLayout);
        // Current Shapes
        QVBoxLayout * CurrentLineLayout=new QVBoxLayout;
        CurrentLineView=new QListView;
        CurrentLineView->setModel(&CurrentLineModel);
        CurrentLineView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QVBoxLayout * CurrentRectLayout=new QVBoxLayout;
        CurrentRectView=new QListView;
        CurrentRectView->setModel(&CurrentRectModel);
        CurrentRectView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QVBoxLayout * CurrentEllipseLayout=new QVBoxLayout;
        CurrentEllipseView=new QListView;
        CurrentEllipseView->setModel(&CurrentEllipseModel);
        CurrentEllipseView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        CurrentLineLayout->addWidget(CurrentLineView);
        CurrentLineLayout->addWidget(new QLabel("Line"));
        CurrentRectLayout->addWidget(CurrentRectView);
        CurrentRectLayout->addWidget(new QLabel("Rectungle"));
        CurrentEllipseLayout->addWidget(CurrentEllipseView);
        CurrentEllipseLayout->addWidget(new QLabel("Ellipse"));
        CurrentShapesLayout->addLayout(CurrentLineLayout);
        CurrentShapesLayout->addLayout(CurrentRectLayout);
        CurrentShapesLayout->addLayout(CurrentEllipseLayout);

}

void HomeMenu::PenButtonPressed()
{
           QColor Color1=QColorDialog::getColor();
           BorderPen=QPen(Color1);
           PenButton.setStyleSheet("background-color: rgb("+QString::number(Color1.red())+','+QString::number(Color1.green())+','+QString::number(Color1.blue())+")");
}

void HomeMenu::BrushButtonPressed()
{
    QColor Color2=QColorDialog::getColor();
    FillBrush=QBrush(Color2);
    BrushButton.setStyleSheet("background-color: rgb("+QString::number(Color2.red())+','+QString::number(Color2.green())+','+QString::number(Color2.blue())+")");

}
