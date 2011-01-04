#ifndef TYPES_HPP
#define TYPES_HPP

#include <QString>
#include <QList>

struct str_num_pair {
	QString str;
	int num;
};

struct str_chrdata {
	int max;
	QString str;
	QList<str_num_pair> chrdata;
};

#endif // TYPES_HPP
