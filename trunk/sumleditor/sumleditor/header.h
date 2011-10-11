#ifndef HEADER_H
#define HEADER_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainterPath>
#include "comfunctions.h"


/**
 * �����, ����������� ������ � ��� ����� �����.
 */
class Header : public QGraphicsItem
{
public:

	QString name;	/** ��� ���������. */

	/**
	 * ����������� �� ���������. 
	 * @param graphWidget ��������� �� ������, �� ������� ����� ��������.
	 */
	Header(GraphWidget *graphWidget);

	/**
	 * ����������.
	 */
	~Header();

	/** 
	 * ������� ������������� ������ ������.
	 * @return ������ ��������������.
	 */
	QRectF boundingRect() const;

	/** 
	 * ������� ����� ������.
	 * @return ������ �����.
	 */
	QPainterPath shape() const;

	/**
	 * ���������� ������.
	 * @param painter ���������� ��������.
	 * @param option �������� ���������.
	 * @param widget ������, �� ������� ������.
	 */
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	/**
	 * ������������ ������������� ���� �������.
	 */
	enum { Type = 0 };

	/**
	 * ������� ������������� ���� �������.
	 * @return ������������� ���� �������.
	 */
    inline int type() const { return Type; }

	/**
	 * ������ ����� ��������� ������� �������� ��������� ������� �� �����.
	 */
	void getCurrentCoords();

	/**
	 * ������ ������� ���������� �� �����.
	 * @param newX ���������� �� X.
	 * @param newY ���������� �� Y.
	 * @param newZ ���������� �� Z.
	 */
	void setCoords(double newX, double newY, double newZ);

protected:

	/** 
	 * ������� ����� ������������� �� ������.
	 * @param ������� ����.
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
	/** ��������� �� ������, �� ������� ������. */
	GraphWidget		*graph;

	double x; /** ���������� �� ��� �. */

	double y; /** ���������� �� ��� y. */

	double z; /** ���������� �� ��� Z. */
};

#endif // HEADER_H