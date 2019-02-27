#pragma once

#include <QtWidgets/QWidget>
#include "ui_MarkDownTest.h"
#include <QWebEngineView>
#include <QDesktopServices>
#include <QTextEdit>

#pragma execution_character_set("utf-8")

class PreviewPage : public QWebEnginePage
{
	Q_OBJECT
public:
	explicit PreviewPage(QObject *parent = nullptr) : QWebEnginePage(parent) {}

protected:
	bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
	{
		QString strUrl = url.toString();
		// Only allow qrc:/index.html.
		if (url.scheme() == QString("qrc"))
			return true;
		// 从浏览器中打开链接;
		QDesktopServices::openUrl(url);
		return false;
	}
};

class Document : public QObject
{
    Q_OBJECT
        Q_PROPERTY(QString text MEMBER m_text NOTIFY textChanged FINAL)
public:
    explicit Document(QObject *parent = nullptr) : QObject(parent) {}

    void setText(const QString &text)
    {
        if (text == m_text)
            return;
        m_text = text; 
        emit textChanged(m_text);
    }

signals:
    void textChanged(const QString &text);

private:
    QString m_text;
};

class MarkDownTest : public QWidget
{
	Q_OBJECT

public:
	MarkDownTest(QWidget *parent = Q_NULLPTR);

private:
	QWebEngineView * m_webEngineView;
	QTextEdit* m_inputMdContentEdit;
	Document m_content;
};
