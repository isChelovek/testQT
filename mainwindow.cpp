#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "checkboxdelegate.h"
#include <QApplication>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QTableView>

#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>

#define MODEL_ROWS 4            //Количество строк модели
#define MODEL_COLUMN 2          //Количество столбцов модели
#define DELEGATE_COLUMN 0       //Столбец с делегатом

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(5);


    for( int i = 0; i < ui->tableWidget->rowCount(); ++i ) {
        ui->tableWidget->setIndexWidget(
            ui->tableWidget->model()->index( i, COLUMN_ACTION ),
            createButtonWidget()
        );
    }

    const int n = 10;
    int pr;
    QTableWidgetItem* ptwi = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pr=i*j;
            ptwi = new QTableWidgetItem(QString("%1").arg(pr));
            //вызовом метода setItem() созданная ячейка таблицы
            //устанавливается в позицию, указанную в первом
            //и втором параметрах
            ui->tableWidget->setItem(i, j, ptwi);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

QWidget* MainWindow::createButtonWidget() const {
    QWidget* wgt = new QWidget;
    QBoxLayout* l = new QHBoxLayout;
    QPushButton* btn = new QPushButton( "Click me!" );
    connect( btn, SIGNAL( clicked( bool ) ), SLOT( onBtnClicked() ) );
    l->setMargin( 0 );
    l->addWidget( btn );
    l->addStretch();
    wgt->setLayout( l );

    return wgt;
}

void MainWindow::onBtnClicked() {
    if( QPushButton* btn = qobject_cast< QPushButton* >( sender() ) ) {
        QModelIndex index = ui->tableWidget->indexAt( btn->parentWidget()->pos() );
        qDebug() << index.row() << "x" << index.column();
        QStringList name;
        for( int i = COLUMN_LAST_NAME; i <= COLUMN_MIDDLE_NAME; ++i ) {
            name << ui->tableWidget->model()->data(
                     ui->tableWidget->model()->index( index.row(), i )
                 ).toString();
        }
        QMessageBox::information( this, "The button was clicked", name.join( " " ) );
    }
}

