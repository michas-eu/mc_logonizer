#ifndef CHART_WRITER_HPP
#define CHART_WRITER_HPP

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsRectItem>
#include <QRectF>
#include "types.hpp"


#include <QDebug>

class chart_writer : public QObject
{
	Q_OBJECT
public:
	explicit chart_writer(QObject *parent = 0);
	QGraphicsScene *get_scene(void);
	void add_elements(str_chrdata dat);

private:
	QGraphicsScene scene;
	void add_element(QString str, int val);
	int last_pos;

signals:

public slots:

};

#endif // CHART_WRITER_HPP
