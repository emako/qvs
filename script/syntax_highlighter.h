#ifndef SYNTAX_HIGHLIGHTER_H
#define SYNTAX_HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

enum class BlockState : int
{
    LongStringSingleStart = 81,
    LongStringSingleMiddle,
    LongStringDoubleStart,
    LongStringDoubleMiddle
};

enum class TokenType
{
    Undecided,
    Keyword,
    Operator,
    String,
    Number,
    Comment,
};

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    SyntaxHighlighter(QTextDocument *parent = nullptr);
    ~SyntaxHighlighter();

    enum ECOMMENT_TYPE {
        eCOMMENT_TYPE_SHARP,
        eCOMMENT_TYPE_DOBULE_SLASH,
        eCOMMENT_TYPE_MAX,
    };

    enum EHIGHLIGHTER_COLOR : int{
        eHIGHLIGHTER_COLOR_KEYWORD_R = 14,
        eHIGHLIGHTER_COLOR_KEYWORD_G = 170,
        eHIGHLIGHTER_COLOR_KEYWORD_B = 149,

        eHIGHLIGHTER_COLOR_OPERATOR_R = 185,
        eHIGHLIGHTER_COLOR_OPERATOR_G = 103,
        eHIGHLIGHTER_COLOR_OPERATOR_B = 78,

        eHIGHLIGHTER_COLOR_COMMENT_R = 127,
        eHIGHLIGHTER_COLOR_COMMENT_G = 127,
        eHIGHLIGHTER_COLOR_COMMENT_B = 127,

        eHIGHLIGHTER_COLOR_FUNCTION_R = 6,
        eHIGHLIGHTER_COLOR_FUNCTION_G = 115,
        eHIGHLIGHTER_COLOR_FUNCTION_B = 224,

        eHIGHLIGHTER_COLOR_STRING_R = 140,
        eHIGHLIGHTER_COLOR_STRING_G = 32,
        eHIGHLIGHTER_COLOR_STRING_B = 140,

        eHIGHLIGHTER_COLOR_NUMBER_R = 63,
        eHIGHLIGHTER_COLOR_NUMBER_G = 131,
        eHIGHLIGHTER_COLOR_NUMBER_B = 0,
    };

    QStringList m_keywordsList;
    QStringList m_operatorsList;

    QTextCharFormat m_keywordFormat;
    QTextCharFormat m_operatorFormat;
    QTextCharFormat m_commentFormat;
    QTextCharFormat m_functionFormat;
    QTextCharFormat m_stringFormat;
    QTextCharFormat m_numberFormat;

public slots:
    void setup(void);
    virtual void clear(void);
    void addSyntaxKeywords(const QStringList& a_keywords, const QTextCharFormat& a_format = QTextCharFormat());
    void addSyntaxComment(const ECOMMENT_TYPE& a_type = eCOMMENT_TYPE_SHARP, const QTextCharFormat& a_format = QTextCharFormat());
    void addSyntaxFunction(const QTextCharFormat& a_format = QTextCharFormat());
    void addSyntax(const QString& a_pattern, const QTextCharFormat& a_format);

protected:
    void highlightBlock(const QString &a_text);

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> m_highlightingRules;

};

#endif // SYNTAX_HIGHLIGHTER_H
