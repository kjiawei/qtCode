#include "MarkDownTest.h"
#include <QHBoxLayout>
#include <QWebChannel>
#include <QFile>

MarkDownTest::MarkDownTest(QWidget *parent)
	: QWidget(parent)
{
	m_webEngineView = new QWebEngineView;
	m_webEngineView->setContextMenuPolicy(Qt::NoContextMenu);

	PreviewPage* page = new PreviewPage(this);
	m_webEngineView->setPage(page);

	QWebChannel *channel = new QWebChannel(this);
	channel->registerObject(QStringLiteral("content"), &m_content);
	page->setWebChannel(channel);

	m_webEngineView->setUrl(QUrl("qrc:/Resources/index.html"));

	m_inputMdContentEdit = new QTextEdit;
	connect(m_inputMdContentEdit, &QTextEdit::textChanged, this, [=] {
		m_content.setText(m_inputMdContentEdit->toPlainText());
	});

	QFile defaultTextFile(":/Resources/default.md");
	defaultTextFile.open(QIODevice::ReadOnly);
	m_inputMdContentEdit->setText(QString::fromLocal8Bit(defaultTextFile.readAll()));

	QHBoxLayout* hLayout = new QHBoxLayout(this);
	hLayout->addWidget(m_inputMdContentEdit);
	hLayout->addWidget(m_webEngineView);
	hLayout->addStretch();
	hLayout->setSpacing(0);
	hLayout->setMargin(0);
}