#ifndef SUMATOR_HPP
#define SUMATOR_HPP

#include <QString>
#include <QDate>
#include <QList>
#include <QLinkedList>
#include <QStringList>
#include <QHash>
#include <QMap>
#include <QtAlgorithms>
#include <QByteArray>
#include "analine.hpp"
#include "types.hpp"

class sumator
{
public:
	bool html_filter;
	QDate date_filter;

	void clear(void);
	void add(QByteArray buff);
	str_chrdata get_files(void);
	str_chrdata get_popular_files(void);
	str_chrdata get_hours(void);
	QString get_dates(void);

private:
	QList<analine> allPack;
	bool filtering(analine &atmp);
	void ins_sorted(QLinkedList<str_num_pair> &llist, str_num_pair &elm);
};

#endif // SUMATOR_HPP
