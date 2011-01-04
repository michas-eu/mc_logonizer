#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QList>
#include <QUrl>
#include "sumator.hpp"
#include "chart_writer.hpp"


namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void dragEnterEvent(QDragEnterEvent *e);
	void dropEvent(QDropEvent *e);

private:
	void changeEvent(QEvent *e);
	Ui::MainWindow *ui;
	QFile *myfile;
	chart_writer *chwrt;
	sumator sm;

private slots:
	void on_date_filt_clicked(bool checked);
	void on_btn_filt_clicked();
	void on_pushButton_clicked();
	void load_file(QString s);
	void showText();
};

#endif // MAINWINDOW_HPP
