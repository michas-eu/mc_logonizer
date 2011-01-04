#include "sumator.hpp"

void sumator::clear()
{
	allPack.clear();
	this->html_filter=false;
	this->date_filter=QDate();
}

void sumator::add(QByteArray buff)
{
	analine x;
	x.addString(buff);
	allPack.append(x);
}

str_chrdata sumator::get_files()
{
	int i;
	QMap<QString,int> str_map;
	str_chrdata ret;
	str_num_pair tmp_pair;
	QString tmp_str;
	QStringList strs;

	for (i = 0; i<allPack.size(); i++) {
		if (filtering(allPack[i])) continue;
		tmp_str = allPack[i].get_file();
		str_map[tmp_str] = str_map.value(tmp_str,0)+1;
	}
	strs = str_map.uniqueKeys();
	ret.max = 0;
	foreach (tmp_str,strs) {
		tmp_pair.num = str_map[tmp_str];
		if (tmp_pair.num > ret.max) ret.max = tmp_pair.num;
		tmp_str.append(" ");
		tmp_str.append(QString::number(tmp_pair.num));
		tmp_pair.str = tmp_str;
		ret.chrdata.append(tmp_pair);
		tmp_str.append("\n");
		ret.str.append(tmp_str);
	}
	return ret;
}

str_chrdata sumator::get_popular_files()
{
	int i;
	QHash<QString,int> str_hash;
	QLinkedList<str_num_pair> str_llist;
	str_num_pair tmp_pair;
	str_chrdata ret;
	QString tmp_str;
	QString key;
	QList<QString> keys;

	for (i = 0; i<allPack.size(); i++) {
		if (filtering(allPack[i])) continue;
		tmp_str = allPack[i].get_file();
		str_hash[tmp_str] = str_hash.value(tmp_str,0)+1;
	}

	keys = str_hash.keys();
	foreach (key, keys) {
		tmp_pair.str = key;
		tmp_pair.num = str_hash[key];
		if (str_llist.isEmpty()) {
			str_llist << tmp_pair;
		} else {
			ins_sorted(str_llist,tmp_pair);
		}
	}

	if (str_llist.isEmpty()) ret.max = 0;
	else ret.max = str_llist.first().num;

	foreach (tmp_pair, str_llist) {
		tmp_str = QString::number(tmp_pair.num);
		tmp_str.append(" ");
		tmp_str.append(tmp_pair.str);
		tmp_pair.str = tmp_str;
		ret.chrdata.append(tmp_pair);
		ret.str.append(tmp_pair.str).append("\n");
	}
	return ret;
}

void sumator::ins_sorted(QLinkedList<str_num_pair> &llist, str_num_pair &elm)
{
	str_num_pair tmp_pair;
	QLinkedList<str_num_pair>::iterator itr;
	for (itr = llist.begin(); itr != llist.end(); itr++) {
		tmp_pair = *itr;
		if (elm.num > tmp_pair.num) {
			llist.insert(itr,elm);
			return;
		}
	}
	llist << elm;
	return;
}

str_chrdata sumator::get_hours()
{
	int i;
	int itmp;
	str_chrdata ret;
	str_num_pair ptmp;
	int vect[24];

	ret.max = 0;
	for (i = 0; i<24; i++) {
		vect[i] = 0;
	}
	for (i = 0; i<allPack.size(); i++) {
		if (filtering(allPack[i])) continue;
		itmp = allPack[i].get_hour();
		vect[itmp]++;
	}
	ret.str = "";
	for (i = 0; i<24; i++) {
		ptmp.num = vect[i];
		ptmp.str = QString::number(i);
		ptmp.str += " - ";
		ptmp.str += QString::number(vect[i]);
		ret.chrdata.append(ptmp);
		ret.str += ptmp.str.append("\n");
		if (vect[i] > ret.max) ret.max = vect[i];
	}

	return ret;
}

bool sumator::filtering(analine &atmp)
{
	if (html_filter) {
		if (!atmp.is_html()) return true;
	}
	if (!date_filter.isNull()) {
		if (!atmp.is_date(date_filter)) return true;
	}
	return false;
}

QString sumator::get_dates()
{
	//No filtering.
	QMap<QDate,bool> date_map;
	QList<QDate> dates;
	QDate tmp_date;
	QString ret;
	int i;
	for (i = 0; i<allPack.size(); i++) {
		tmp_date = allPack[i].get_date();
		if (!date_map.contains(tmp_date)) {
			date_map.insert(tmp_date,true);
		}
		i++;
	}
	dates = date_map.uniqueKeys();
	foreach (tmp_date,dates) {
		ret.append(tmp_date.toString("yyyy.MM.dd"));
		ret.append("\n");
	}
	return ret;
}
