#include "paint.h"
#include "ui_paint.h"

Paint::Paint(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Paint)
{
    ui->setupUi(this);
    QStandardItemModel * model=new QStandardItemModel;
    QTimer * MainTimer=new QTimer;
    connect(MainTimer,SIGNAL(timeout()),this,SLOT(RepaintEvent()));
    MainTimer->start(1000/100);
    PaintMenu=new HomeMenu;
    this->setBaseSize(Width,Height);
    PaintMenu->setGeometry(0,0,400,400);
    PaintMenu->show();
    PositionLable=new QLabel("Position: ");
    connect(ui->actionSave_as_2,SIGNAL(triggered()),this,SLOT(SaveEvent()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(OpenEvent1()));
}

Paint::~Paint()
{
    delete ui;
}

void Paint::paintEvent(QPaintEvent *)
{
    QPainter ptr(this);
    int ind[4]={0};
    ptr.drawImage(QRectF(0,0,this->width(),this->height()),BackgroundeImage);
    for(int i=0;i<PensilePointArr.size()+LineArr.size()+RectArr.size()+EllipseArr.size();++i)
    {
        int time=INT_MAX;
        int index=-1;
        if(ind[0]<PensilePointArr.size())
        if(PensileTimeArr[ind[0]]<time)
        {
            time=PensileTimeArr[ind[0]];
            index=0;
        }
        if(ind[1]<LineArr.size())
        if(LineTimeArr[ind[1]]<time)
        {
            time=LineTimeArr[ind[1]];
            index=1;
        }
        if(ind[2]<RectArr.size())
        if(RectTimeArr[ind[2]]<time)
        {
            time=RectTimeArr[ind[2]];
            index=2;
        }
        if(ind[3]<EllipseArr.size())
        if(EllipseTimeArr[ind[3]]<time)
        {
            time=EllipseTimeArr[ind[3]];
            index=3;
        }
        if(index==-1)
            return;
        if(index==0){
            ptr.setPen(PensilePenArr[ind[0]]);
            ptr.drawPoint(PensilePointArr[ind[0]]);}
        if(index==1){
            ptr.setPen(LinePenArr[ind[1]]);
            ptr.drawLine(LineArr[ind[1]]);}
        if(index==2){
            ptr.setPen(RectPenArr[ind[2]]);
            ptr.setBrush(RectBrushArr[ind[2]]);
            ptr.drawRect(RectArr[ind[2]]);}
        if(index==3){
            ptr.setPen(EllipsePenArr[ind[3]]);
            ptr.setBrush(EllipseBrushArr[ind[3]]);
            ptr.drawEllipse(EllipseArr[ind[3]]);}
        ind[index]++;
    }
}

void Paint::SaveEvent()
{
    this->screen()->grabWindow(this->winId()).toImage().save(QFileDialog::getSaveFileName()+".png","PNG");
}

void Paint::OpenEvent1()
{
    QString str=QFileDialog::getOpenFileName();
    qDebug() << str;
    BackgroundeImage=QImage(str);

}
void Paint::RepaintEvent()
{

    this->repaint();
    ui->statusbar->showMessage("Position: " + QString::number(this->cursor().pos().x()-this->pos().x())+' ' + QString::number(this->cursor().pos().y()-this->pos().y()));
    TimeIndex++;

}

void Paint::mousePressEvent(QMouseEvent *event)
{
    calculatePenAndBrush();
    if(PaintMenu->PaintDevicesView->currentIndex().row()==0)
    {
        this->setCursor(Qt::ClosedHandCursor);
        if(PaintMenu->TransformView->currentIndex().row()==2 || PaintMenu->TransformView->currentIndex().row()==3){
        if(PaintMenu->ShapesView->currentIndex().row()==0)
        {
            int ind=PaintMenu->CurrentLineView->currentIndex().row();
            if(ind!=-1){
            QLine copy=LineArr[ind];
            LineArr[ind]=QLine(copy.x1(),copy.y2(),copy.x2(),copy.y1());}
        }
        if(PaintMenu->ShapesView->currentIndex().row()==1)
        {
            int ind=PaintMenu->CurrentRectView->currentIndex().row();
            if(ind!=-1){
            QRect copy=RectArr[ind];
            RectArr[ind]=QRect(copy.topLeft().x()-(copy.width()-copy.height())/2.,copy.topLeft().y()-(copy.width()-copy.height())/2.,copy.bottomRight().x()+(copy.width()-copy.height())/2.,copy.bottomRight().y()+(copy.width()-copy.height())/2.);}

        }
        if(PaintMenu->ShapesView->currentIndex().row()==2)
        {
            int ind=PaintMenu->CurrentEllipseView->currentIndex().row();
            if(ind!=-1){
            QRect copy=EllipseArr[ind];
            EllipseArr[ind]=QRect(copy.topLeft().x()-(copy.width()-copy.height())/2.,copy.topLeft().y()-(copy.width()-copy.height())/2.,copy.bottomRight().x()+(copy.width()-copy.height())/2.,copy.bottomRight().y()+(copy.width()-copy.height())/2.);}

        }
        }
    }
    else
        this->setCursor(Qt::ArrowCursor);
    if(PaintMenu->PaintDevicesView->currentIndex().row()==1)
    {
    PensilePenArr.push_back(MyPen);
    PensilePointArr.push_back(event->pos());
    PensileTimeArr.push_back(TimeIndex);
    }
    if(PaintMenu->PaintDevicesView->currentIndex().row()==2){
        if(PaintMenu->ShapesView->currentIndex().row()==0)
        {
            LineArr.push_back(QLine(event->pos(),event->pos()));
            PaintMenu->CurrentLineModel.setItem(PaintMenu->CurrentLineModel.rowCount(),new QStandardItem(QString::number(PaintMenu->CurrentLineModel.rowCount())));
            LinePenArr.push_back(MyPen);
            LineTimeArr.push_back(TimeIndex);
        }
        if(PaintMenu->ShapesView->currentIndex().row()==1)
        {
            RectArr.push_back(QRect(event->pos(),event->pos()));
            PaintMenu->CurrentRectModel.setItem(PaintMenu->CurrentRectModel.rowCount(),new QStandardItem(QString::number(PaintMenu->CurrentRectModel.rowCount())));
            RectPenArr.push_back(MyPen);
            RectBrushArr.push_back(MyBrush);
            RectTimeArr.push_back(TimeIndex);
        }
        if(PaintMenu->ShapesView->currentIndex().row()==2)
        {
            EllipseArr.push_back(QRect(event->pos(),event->pos()));
            PaintMenu->CurrentEllipseModel.setItem(PaintMenu->CurrentEllipseModel.rowCount(),new QStandardItem(QString::number(PaintMenu->CurrentEllipseModel.rowCount())));
            EllipsePenArr.push_back(MyPen);
            EllipseBrushArr.push_back(MyBrush);
            EllipseTimeArr.push_back(TimeIndex);
        }
    }

}

void Paint::mouseMoveEvent(QMouseEvent *event)
{
    calculatePenAndBrush();
    if(PaintMenu->PaintDevicesView->currentIndex().row()==0)
    {
        if(PaintMenu->TransformView->currentIndex().row()==0 || PaintMenu->TransformView->currentIndex().row()==1){
        if(PaintMenu->ShapesView->currentIndex().row()==0)
        {
            int ind=PaintMenu->CurrentLineView->currentIndex().row();
            if(ind!=-1){
            QLine copy=LineArr[ind];
            if(PaintMenu->TransformView->currentIndex().row()==0)
            LineArr[ind]=QLine(copy.p1(),event->pos());
            else
                LineArr[ind]=QLine(event->pos(),copy.p2()-copy.p1()+event->pos());
            }
        }
        if(PaintMenu->ShapesView->currentIndex().row()==1)
        {
            int ind=PaintMenu->CurrentRectView->currentIndex().row();
            if(ind!=-1){
            QRect copy=RectArr[ind];
            if(PaintMenu->TransformView->currentIndex().row()==0)
            RectArr[ind]=QRect(copy.topLeft(),event->pos());
            else
                RectArr[ind]=QRect(event->pos(),copy.bottomRight()-copy.topLeft()+event->pos());
            }
        }
        if(PaintMenu->ShapesView->currentIndex().row()==2)
        {
            int ind=PaintMenu->CurrentEllipseView->currentIndex().row();
            if(ind!=-1){
            QRect copy=EllipseArr[ind];
            if(PaintMenu->TransformView->currentIndex().row()==0)
            EllipseArr[ind]=QRect(copy.topLeft(),event->pos());
            else
                EllipseArr[ind]=QRect(event->pos(),copy.bottomRight()-copy.topLeft()+event->pos());
            }
        }
        }

    }
    if(PaintMenu->PaintDevicesView->currentIndex().row()==2){
        if(PaintMenu->ShapesView->currentIndex().row()==0)
        {
            LineArr.back().setP2(event->pos());
        }
        if(PaintMenu->ShapesView->currentIndex().row()==1)
        {
            RectArr.back().setBottomRight(event->pos());
        }
        if(PaintMenu->ShapesView->currentIndex().row()==2)
        {
            EllipseArr.back().setBottomRight(event->pos());
        }
    }
    if(PaintMenu->PaintDevicesView->currentIndex().row()==1)
    {
    PensilePenArr.push_back(MyPen);
    PensilePointArr.push_back(event->pos());
    PensileTimeArr.push_back(TimeIndex);

    }
}

void Paint::mouseReleaseEvent(QMouseEvent *event)
{
    calculatePenAndBrush();
    if(PaintMenu->PaintDevicesView->currentIndex().row()==0)
    {
        this->setCursor(Qt::OpenHandCursor);
    }
    else
        this->setCursor(Qt::ArrowCursor);
    if(PaintMenu->PaintDevicesView->currentIndex().row()==1)
    {
    PensilePenArr.push_back(MyPen);
    PensilePointArr.push_back(event->pos());
    PensileTimeArr.push_back(TimeIndex);
    }
}

void Paint::calculatePenAndBrush()
{
    MyPen=QPen(PaintMenu->BorderPen.color());
    if(PaintMenu->PenTypeBox.currentIndex()==0)
        MyPen=QPen(Qt::NoPen);
    if(PaintMenu->PenSizeBox.currentIndex()==0)
        MyPen.setWidth(10);
    if(PaintMenu->PenSizeBox.currentIndex()==1)
        MyPen.setWidth(20);
    if(PaintMenu->PenSizeBox.currentIndex()==2)
        MyPen.setWidth(40);
    MyBrush=PaintMenu->FillBrush;
    if(PaintMenu->BrushTypeBox.currentIndex()==0)
        MyBrush=QBrush(Qt::NoBrush);
}



