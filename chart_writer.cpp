#include "chart_writer.hpp"

chart_writer::chart_writer(QObject *parent):
    QObject(parent)
{
	last_pos = 0;
}

QGraphicsScene *chart_writer::get_scene()
{
	return &scene;
}

void chart_writer::add_elements(str_chrdata dat)
{
	str_num_pair tmp;
	qreal norm;
	scene.clear();
	last_pos = 0;
	foreach (tmp,dat.chrdata) {
		norm = (qreal)tmp.num * 100 / (qreal)dat.max;
		add_element(tmp.str,(int)norm);
	}
}

void chart_writer::add_element(QString str, int norm)
{
	QRectF rec;
	QGraphicsSimpleTextItem *nstr;

	nstr = scene.addSimpleText(str);
	rec = nstr->boundingRect();
	nstr->setPos(-rec.width(),last_pos);

	scene.addRect(5,last_pos,norm,10);

	last_pos += 15;
}
