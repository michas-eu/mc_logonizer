#include "analine.hpp"

void analine::addString(QString s)
{
	QStringList list;
	list = s.split(" ");
	if (list.size() < 7) {
		isEmpty = true;
	} else {
		isEmpty = false;
		ip = list[0];
		file = list[6];
		filetype = getFileType(file);
		list = list[3].split(":");
		time = list[1].append(list[2]).append(list[3]);
		list = list[0].remove(0,1).split("/");
		list[1] = getMonthNum(list[1]);
		date.setDate(
			(list[2]).toInt(),
			(list[1]).toInt(),
			(list[0]).toInt()
		);

	}
}

QString analine::get_file()
{
	if (isEmpty) return "";
	return getFileType(file).append(" ").append(file);
}

QDate analine::get_date()
{
	return date;
}

bool analine::is_html() {
	if (filetype=="html") return true;
	if (filetype=="php") return true;
	return false;
}

bool analine::is_date(QDate s)
{
	return (date==s);
}

int analine::get_hour()
{
	return time.left(2).toInt();
}

QString analine::getMonthNum(QString s)
{
	if (s=="Jan") return "01";
	if (s=="Feb") return "02";
	if (s=="Mar") return "03";
	if (s=="Apr") return "04";
	if (s=="May") return "05";
	if (s=="Jun") return "06";
	if (s=="Jul") return "07";
	if (s=="Aug") return "08";
	if (s=="Sep") return "09";
	if (s=="Oct") return "10";
	if (s=="Nov") return "11";
	if (s=="Dec") return "12";
	return "00";
}

QString analine::getFileType(QString s){
	QRegExp rx;
	rx.setPatternSyntax(QRegExp::RegExp2);
	rx.setPattern("[^\\?]*\\.jpg(\\?.*)?$");
	if (rx.exactMatch(s)) return "jpeg";
	rx.setPattern("[^\\?]*\\.(php|html|htm)(\\?.*)?$");
	if (rx.exactMatch(s)) return "html";
	rx.setPattern("[^\\?]*\\.([^\\?\\.]{1,4})(\\?.*)?$");
	if (rx.exactMatch(s)) {
		return rx.cap(1).toLower();
	}
	return "html";
}
