#pragma once
#include <QtWidgets/QMainWindow>
class HTMLContent
{
public:
	HTMLContent();
	~HTMLContent();
	void addKeyword(QString keyWord);
	void addVariable(QString vaiable);
	void addComment(QString comment);
	void addOperator(QString oneOperator);
	QString fetchHTML() {
		return this->htmlContent;
	}
private:
	QString htmlContent;
};

