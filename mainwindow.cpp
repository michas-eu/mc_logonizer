#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	chwrt = new chart_writer(this);
	ui->canva->setScene(chwrt->get_scene());

	setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
	delete ui;
	sm.clear();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
	e->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *e)
{
	if (!e->mimeData()->hasUrls()) 	return;
	QString tmp;
	tmp = e->mimeData()->urls().first().toLocalFile();
	load_file(tmp);
	e->accept();
}

void MainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void MainWindow::on_pushButton_clicked()
{
	QString alfa;
	alfa = ui->file_name->text();
	alfa = QFileDialog::getOpenFileName(this,"",alfa);
	if (!alfa.isEmpty()) {
		load_file(alfa);
	}
}

void MainWindow::load_file(QString s)
{
	bool tmp;
	QByteArray buff;
	myfile = new QFile(s);
	tmp = myfile->open(QIODevice::ReadOnly|QIODevice::Text);
	if (!tmp) return;
	ui->file_name->setText(s);
	sm.clear();
	while (!myfile->atEnd()) {
		buff = myfile->readLine(2048);
		sm.add(buff);
	}
	delete myfile;
	on_btn_filt_clicked();
}

void MainWindow::showText()
{
	QString alfa;
	str_chrdata beta;
	alfa = ui->filt_box->currentText();
	if (alfa == "Pliki") {
		beta = sm.get_files();
	} else if (alfa == "Popularne pliki") {
		beta = sm.get_popular_files();
	} else if (alfa == "Godziny") {
		beta = sm.get_hours();
	} else if (alfa == "Zakres dat") {
		beta.str = sm.get_dates();
	} else {
		return;
	}
	chwrt->add_elements(beta);
	ui->plainTextEdit->setPlainText(beta.str);
}

void MainWindow::on_btn_filt_clicked()
{
	sm.html_filter = ui->html_filt->isChecked();
	if (!ui->date_filt->isChecked()) {
		sm.date_filter = ui->date_edit->date();
	} else {
		sm.date_filter = QDate();
	}
	showText();
}

void MainWindow::on_date_filt_clicked(bool checked)
{
	ui->date_edit->setEnabled(!checked);
}
