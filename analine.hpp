#ifndef ANALINE_HPP
#define ANALINE_HPP

#include <QObject>
#include <QDate>
#include <QString>
#include <QStringList>
#include <QRegExp>

class analine
{
public:
	void addString(QString s);
	QString get_file(void);
	QDate get_date(void);
	bool is_html(void);
	bool is_date(QDate s);
	int get_hour();
private:
	QString getMonthNum(QString s);
	QString getFileType(QString s);
	bool isEmpty;
	QString ip;
	QDate date;
	QString time;
	QString file;
	QString filetype;
signals:

public slots:

};

#endif // ANALINE_HPP
