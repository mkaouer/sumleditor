#include "stdafx.h"
#include "lifeline.h"

/** ����������� �� ���������. */
Lifeline::Lifeline(GraphWidget *graphWidget)
{
	graph = graphWidget;
	// ������ ��������� ������
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	this->setCursor(Qt::PointingHandCursor);
	setCacheMode(DeviceCoordinateCache);
	setZValue(1);
	isSelected = false;
	isEnd = false;
	this->x = NULL;
	this->y = NULL;
	this->z = NULL;
	isSelectedByMessage = false;
}

/** ���������� �� ���������. */
Lifeline::~Lifeline()
{

}

/** ������� ������������� ������ ������. */
QRectF Lifeline::boundingRect() const
{
	return QRectF(0,0,90,320);
}

/** ������� ����� ������. */
QPainterPath  Lifeline::shape() const
{
	QPainterPath path;
	path.addRect(0,0,90,320);

	return path;
}

/** ���������� ������. */
void  Lifeline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QLinearGradient gradient(0,0,90,30);					// ������ �������� ������

	if (isSelected || isSelectedByMessage)
	{
		gradient.setColorAt(0, QColor(Qt::blue).light(150));	// ����� ���������
		gradient.setColorAt(1, QColor(Qt::darkBlue).light(150));
	}
	else
	{
		gradient.setColorAt(0, QColor(Qt::blue));	// ����� ���������
		gradient.setColorAt(1, QColor(Qt::darkBlue));
	}
	// ���������� ������������� �������
	painter->setBrush(gradient);

	QPen pen;
	pen.setWidth(2);

	if (isSelected)
		pen.setColor(Qt::red);
	else
		pen.setColor(Qt::black);

	if (isSelectedByMessage)
		pen.setColor(QColor(255,200,15));

	painter->setPen(pen);
	painter->drawRect(0,0,90,30);

	QRectF textRect(5,5,80,20);								// ������������� � �������

	// ������ �����
	QFont font = painter->font();
	font.setBold(true);
	font.setPointSize(8);

	painter->setFont(font);
	painter->setPen(Qt::black);

	// ������ �������� ������
	QTextOption opt;
	opt.setAlignment(Qt::AlignCenter);

	painter->drawText(textRect.translated(2, 2),name,opt); 
	// ���������� �����
	painter->setPen(Qt::white);
	painter->drawText(textRect, name, opt);

	QLine line (45,30,45,300);
	pen.setStyle(Qt::DashLine);
	pen.setDashOffset(3);
	painter->setPen(pen);
	painter->drawLine(line);

	if (isEnd)	// ���� �� �����������
	{
		// ������ �� ����� ����� �������
		pen.setStyle(Qt::SolidLine);
		painter->setPen(pen);
		painter->drawLine(25,280,65,320);
		painter->drawLine(25,320,65,280);
	}
}

/** ������� ����� ������������� �� ������. */
void  Lifeline::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

/** ������ ����� ��������� ������� �������� ��������� ������� �� �����. */
void Lifeline::getCurrentCoords()
{
	x = this->pos().x();
	y = this->pos().y();
	z = this->zValue();	
}

/** ������ ������� ���������� �� �����. */
void Lifeline::setCoords(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
	this->setX(x);
	this->setY(y);
	this->setZValue(z);
}

/** ������� �������� ���� ��� ������� ������ ����. */
void Lifeline::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
	QGraphicsItem::mouseMoveEvent(event);
	this->setY(30);							// ����� ����� �������� �� ����� ���������� �
        QListIterator<Message*>i(messages);

        Message *buf;

        while(i.hasNext())
        {
            buf = i.next();
            buf->update();
            buf->calcMessCoords(buf->sender->pos(),buf->receiver->pos(),buf->pos());
        }
}

QDomElement Lifeline::save(QDomDocument & domDoc, int id)
{
	QDomElement element = domDoc.createElement("lifeline");

        getCurrentCoords();

	QDomAttr attr = domDoc.createAttribute("name");
	attr.setValue(name.toUtf8());
	element.setAttributeNode(attr);

	attr = domDoc.createAttribute("is_end");
	attr.setValue(QString::number(isEnd));
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

	attr = domDoc.createAttribute("id");
	attr.setValue(QString::number(id));
	element.setAttributeNode(attr);

	return element;
}

/** ������� ���������� ����� ����� �� �����. */
void Lifeline::load(const QDomElement &element)
{
    this->x     = element.attribute("x", "0").toDouble();
    this->y     = element.attribute("y", "0").toDouble();
    this->z     = element.attribute("z", "0").toDouble();
    this->isEnd = element.attribute("is_end", "0").toInt();
    this->id    = element.attribute("id", "0").toInt();
    this->name  = element.attribute("name", "name");
}