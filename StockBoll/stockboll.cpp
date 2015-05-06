#include "stockboll.h"
#include "qcursor.h"
#include "qevent.h"
#include "qabstractitemdelegate.h"
#include "qpainter.h"
#include "QGridLayout"
#include "QLabel"
#include "QNetworkAccessManager"
#include "QNetworkRequest"
#include "QTextCodec"
#include "QNetworkReply"

StockBoll::StockBoll(QWidget *parent)
	: QWidget(parent)
{
	QIcon icon = QIcon(":/icon/logo");
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(icon);
	trayIcon->setToolTip(tr("hello"));
	QString titlec = tr("title");
	QString textc = tr("hell0:text");
	trayIcon->show();
	trayIcon->showMessage(titlec, textc, QSystemTrayIcon::Information, 2000);


	ui.setupUi(this);

	QGridLayout *gridLayout = new QGridLayout;
	gridLayout->setColumnStretch(0, 1);
	gridLayout->setColumnStretch(1, 1);

	gridLayout->setMargin(15);
	gridLayout->setColumnStretch(0, 1);
	gridLayout->setColumnStretch(1, 1);

	QLabel *lbl1 = new QLabel(QWidget::tr("1"));
	lbl1->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	QLabel *lbl2 = new QLabel(QWidget::tr("2"));
	lbl2->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	QLabel *lbl3 = new QLabel(QWidget::tr("3"));
	lbl3->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	QLabel *lbl4 = new QLabel(QWidget::tr("4"));
	lbl4->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);

	gridLayout->addWidget(lbl1, 0, 0);
	gridLayout->addWidget(lbl2, 0, 1);
	gridLayout->addWidget(lbl3, 1, 0);
	gridLayout->addWidget(lbl4, 1, 1);

	setLayout(gridLayout);

	resize(100, 100);
	setWindowTitle(QWidget::tr("Qt Test"));

	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground);//���ñ���͸��
	QPixmap pix;
	pix.load(":/images/360bg");  //����������Ϊ��ȡͼƬ�ķ�ʽ
	//resize(pix.size());
	mouseMovePos = QPoint(0, 0);


	m_nTimerId = startTimer(1000);

	netManager = new QNetworkAccessManager(this);  //�½�QNetworkAccessManager����  
	connect(netManager, SIGNAL(finished(QNetworkReply*)),  //�����źźͲ�  
		this, SLOT(this->replyFinished(QNetworkReply*)));
	QNetworkRequest request;
	request.setUrl(QUrl("http://www.baidu.com"));
	QNetworkReply *reply = netManager->get(request);
	connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
	netManager->get(QNetworkRequest(QUrl("http://www.baidu.com"))); //�������� 
}

StockBoll::~StockBoll()
{
	if (m_nTimerId != 0)
	{
		killTimer(m_nTimerId);
	}
}

void StockBoll::mouseMoveEvent(QMouseEvent *event)
{
	if (mouseMovePos != QPoint(0, 0))
	{
		move(geometry().x() + event->globalPos().x() - mouseMovePos.x(), geometry().y() + event->globalPos().y() - mouseMovePos.y());
		mouseMovePos = event->globalPos();
	}
}

void StockBoll::mousePressEvent(QMouseEvent *event)
{
	mouseMovePos = event->globalPos();
}

void StockBoll::mouseReleaseEvent(QMouseEvent *event)
{
	mouseMovePos = QPoint(0, 0);
}

void StockBoll::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	//painter.drawPixmap(0, 0, QPixmap(":/images/360bg"));
}

void StockBoll::timerEvent(QTimerEvent *event)
{

}

void StockBoll::replyFinished(QNetworkReply *reply)  //���ظ�������  
{
	QTextCodec *codec = QTextCodec::codecForName("utf8");
	//ʹ��utf8���룬�����ſ�����ʾ����  
	QString all = codec->toUnicode(reply->readAll());
	//ui->textBrowser->setText(all);
	reply->deleteLater();   //���Ҫ�ͷ�reply����  
}

void StockBoll::on_readyRead()
{
	QTextCodec *codec = QTextCodec::codecForName("utf8");
}
