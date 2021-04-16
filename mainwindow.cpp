#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QFileDialog>
#include<QFontDialog>
#include<QFont>
#include<QColorDialog>
#include<QColor>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actioncut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionpaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionundo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionredo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionnew_triggered()
{
    file_path=" ";
    ui->textEdit->setText(" ");
}

void MainWindow::on_actionopen_triggered()
{
    QString file_name=QFileDialog::getOpenFileName(this,"open the file");
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream in(&file);
    QString text=in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionsave_triggered()
{

    QFile file(file_path);
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text= ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}

void MainWindow::on_actionsaveAs_triggered()
{
    QString file_name=QFileDialog::getSaveFileName(this,"open the file");
    QFile file(file_name);
     file_path=file_name;
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text= ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}

void MainWindow::on_actionquit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionselectfont_triggered()
{
    bool fontSelected;
    QFont font=QFontDialog::getFont(&fontSelected,this);
    if(fontSelected)
    {
        ui->textEdit->setFont(font);
    }
}

void MainWindow::on_actionbold_triggered()
{
    ui->textEdit->setFontWeight(QFont::Bold);
}


void MainWindow::on_actionfontcolor_triggered()
{
    QColor color=QColorDialog::getColor(Qt::white,this,"Choose color");
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
}

void MainWindow::on_actionfontbackgroundcolour_triggered()
{
    QColor color=QColorDialog::getColor(Qt::white,this,"Choose color");
    if(color.isValid())
    {
        ui->textEdit->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionitalic_triggered()
{
    ui->textEdit->setFontItalic(true);

}

void MainWindow::on_actionunderline_triggered()
{
    ui->textEdit->setFontUnderline(true);

}

void MainWindow::on_actionprint_triggered()
{
    QPrinter p;
        p.setPrinterName("HP Laser Jet");
        QPrintDialog pd(&p,this);
        if(pd.exec()==QDialog::Rejected)
        {
            QMessageBox::warning(this,"Error","Can't access printer");
            return;
        }
        ui->textEdit->print(&p);
}

void MainWindow::on_actionaboutqt_triggered()
{
    QMessageBox::information(this,"ABOUT QT","Qt is a widget toolkit for creating graphical user interfaces as well as cross-platform applications");
}
