#include "stdafx.h"
#include "freecomment.h"
#include <QPainterPath>

/** ����������� �� ���������. */
FreeComment::FreeComment(GraphWidget *graphWidget)
{
	// ������ ��������� ������
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(2);
	isSelected = false;
	this->setCursor(Qt::PointingHandCursor);
        this->x = 0;
        this->y = 0;
        this->z = 0;
}

/** ���������� �� ���������. */
FreeComment::~FreeComment()
{

}

/** ������� ������������� ������ ������. */
QRectF FreeComment::boundingRect() const
{
	return QRectF(0,0,150,100);
}

/** ������� ����� ������. */
QPainterPath  FreeComment::shape() const
{
	QPainterPath path;
	path.addRect(0,0,150,100);

	return path;
}

/** ���������� ������. */
void  FreeComment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QLinearGradient gradient(0,0,100,50);					// ������ �������� ������

	if (isSelected)
	{
		gradient.setColorAt(0, QColor(Qt::yellow).light(150));	// ����� ���������
		gradient.setColorAt(1, QColor(Qt::darkYellow).light(150));
	}
	else
	{
		gradient.setColorAt(0, QColor(Qt::yellow));	// ����� ���������
		gradient.setColorAt(1, QColor(Qt::darkYellow));
	}

	QPen pen;
	pen.setWidth(2);

	// ���������� ������������� �������
	painter->setBrush(gradient);

	if (isSelected)
		pen.setColor(Qt::red);
	else
		pen.setColor(Qt::black);

	pen.setJoinStyle(Qt::RoundJoin);
	painter->setPen(pen);
	//painter->drawRect(0,0,100,50);
	QPainterPath path;
	QPolygon pol;
	pol<<QPoint(0,0)<<QPoint(130,0)<<QPoint(150,20)<<QPoint(150,100)<<QPoint(0,100)<<QPoint(0,0);

	path.addPolygon(pol);
	painter->drawPath(path);
	painter->drawLine(130,0,130,20);
	painter->drawLine(130,20,150,20);

	QRectF textRect(5,5,140,90);								// ������������� � �������

	// ������ �����
	QFont font = painter->font();
	font.setBold(true);
	font.setPointSize(8);

	painter->setFont(font);

	// ������ �������� ������
	QTextOption opt;
	opt.setAlignment(Qt::AlignCenter);

	//painter->drawText(textRect.translated(2, 2),text,opt); // Create shadow of the name
	
	// ���������� �����
	painter->setPen(Qt::black);
	painter->drawText(textRect,text, opt);
}

/** ������� ����� ������������� �� ������. */
void  FreeComment::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

/** ������ ����� ��������� ������� �������� ��������� ������� �� �����. */
void FreeComment::getCurrentCoords()
{
	x = this->pos().x();
	y = this->pos().y();
	z = this->zValue();	
}

/** ������ ������� ���������� �� �����. */
void FreeComment::setCoords(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
	this->setX(x);
	this->setY(y);
	this->setZValue(z);
}

/** ���������� ���������� ����������� � ����. */
QDomElement FreeComment::save(QDomDocument & domDoc)
{
    getCurrentCoords();

	QDomElement element = domDoc.createElement("freecomment");

	QDomAttr attr = domDoc.createAttribute("text");
	attr.setValue(text.toUtf8());
	element.setAttributeNode(attr);

	attr = domDoc.createAttribute("name");
	attr.setValue(name.toUtf8());
	element.setAttributeNode(attr);

	attr = domDoc.createAttribute("x");
	attr.setValue(QString::number(x));
	element.setAttributeNode(attr);

	attr = domDoc.createAttribute("y");
	attr.setValue(QString::number(y));
	element.setAttributeNode(attr);

	attr = domDoc.createAttribute("z");
	attr.setValue(QString::number(z));
	element.setAttributeNode(attr);

	return element;
}

/** ���������� ���������� ����������� �� �����. */
void FreeComment::load(const QDomElement & element)
{
	text = element.attribute("text", "text");
	name = element.attribute("name", "name");
	x    = element.attribute("x", "0").toDouble();
	y    = element.attribute("y", "0").toDouble();
	z    = element.attribute("z", "0").toDouble();
}
