#include "HTMLContent.h"
#define KEYWORD_COLOR "#e74c3c"
#define VARIABLE_COLOR "#16a085"
#define COMMENT_COLOR "#bdc3c7"
#define OPERATOR_COLOR "#9b59b6"


HTMLContent::HTMLContent()
{
	this->htmlContent = "";
}


HTMLContent::~HTMLContent()
{
}

void HTMLContent::addKeyword(QString keyWord) {
	this->htmlContent.append(QString("<span style='color: %2'>%1</span>").arg(keyWord, KEYWORD_COLOR));
}

void HTMLContent::addVariable(QString variable) {
	this->htmlContent.append(QString("<span style='color: %2'>%1</span>").arg(variable, VARIABLE_COLOR));
}
void HTMLContent::addComment(QString comment) {
	this->htmlContent.append(QString("<span style='color: %2'>%1</span>").arg(comment, COMMENT_COLOR));
}
void HTMLContent::addOperator(QString oneOperator) {
	this->htmlContent.append(QString("<span style='color: %2'>%1</span>").arg(oneOperator, OPERATOR_COLOR));
}

