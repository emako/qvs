#include "syntax_highlighter.h"
#include "number_matcher.h"

struct Token
{
    QString text;
    int start;
    int length;
    TokenType type;

    Token(const QString & a_text, int a_start, int a_length, TokenType a_type):
        text(a_text), start(a_start), length(a_length), type(a_type){}
};

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    this->setup();
}

SyntaxHighlighter::~SyntaxHighlighter()
{
}

void SyntaxHighlighter::setup(void)
{
    m_keywordFormat.setForeground(QColor(eHIGHLIGHTER_COLOR_KEYWORD_R, eHIGHLIGHTER_COLOR_KEYWORD_G, eHIGHLIGHTER_COLOR_KEYWORD_B));
    m_keywordFormat.setFontWeight(QFont::Bold);
    m_operatorFormat.setForeground(QColor(eHIGHLIGHTER_COLOR_OPERATOR_R, eHIGHLIGHTER_COLOR_OPERATOR_G, eHIGHLIGHTER_COLOR_OPERATOR_B));
    m_commentFormat.setForeground(QColor(eHIGHLIGHTER_COLOR_COMMENT_R, eHIGHLIGHTER_COLOR_COMMENT_G, eHIGHLIGHTER_COLOR_COMMENT_B));
    m_functionFormat.setForeground(QColor(eHIGHLIGHTER_COLOR_FUNCTION_R, eHIGHLIGHTER_COLOR_FUNCTION_G, eHIGHLIGHTER_COLOR_FUNCTION_B));
    m_stringFormat.setForeground(QColor(eHIGHLIGHTER_COLOR_STRING_R, eHIGHLIGHTER_COLOR_STRING_G, eHIGHLIGHTER_COLOR_STRING_B));
    m_numberFormat.setForeground(QColor(eHIGHLIGHTER_COLOR_NUMBER_R, eHIGHLIGHTER_COLOR_NUMBER_G, eHIGHLIGHTER_COLOR_NUMBER_B));

    m_keywordsList << "False" << "None" << "True" << "and" << "as" <<
        "assert" << "break" << "class" << "continue" << "def" << "del" <<
        "elif" << "else" << "except" << "finally" << "for" << "from" <<
        "global" << "if" << "import" << "in" << "is" << "lambda" <<
        "nonlocal" << "not" << "or" << "pass" << "raise" << "return" <<
        "try" << "while" << "with" << "yield";

    m_operatorsList << "//=" << ">>=" << "<<=" << "**=" << "**" << "//" <<
        "<<" << ">>" << "<=" << ">=" << "==" << "!=" << "->" << "+=" << "-=" <<
        "*=" << "/=" << "%=" << "&=" << "|=" << "^=" << "+" << "-" << "*" <<
        "/" << "%" << "&" << "|" << "^" << "~" << "<" << ">" << "(" << ")" <<
        "[" << "]" << "{" << "}" << "," << ":" << "." << ";" << "@" << "=";

    addSyntaxFunction();
}

void SyntaxHighlighter::highlightBlock(const QString &a_text)
{
    foreach (const HighlightingRule &rule, m_highlightingRules)
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(a_text);
        while (matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    setCurrentBlockState(0);

    std::vector<Token> tokens;

    int i = 0;
    int j = 0;
    int textLength = a_text.length();
    bool goToNextToken = false;


    while(i < textLength)
    {
//------Long string continuation, single quotes---------------------------------

        if((i == 0) && (
            (previousBlockState() == static_cast<int>(BlockState::LongStringSingleStart)) ||
            (previousBlockState() == static_cast<int>(BlockState::LongStringSingleMiddle))))
        {
            bool foundMatchingQuotes = false;
            for(j = i; j < textLength - 2; ++j)
            {
                if((a_text.mid(j, 3) == "'''") &&
                    ((j == 0) || ((j != 0) && (a_text[j - 1] != '\\'))))
                {
                    foundMatchingQuotes = true;
                    break;
                }
            }

            if(foundMatchingQuotes)
            {
                j += 3;
                Token newToken(a_text.mid(i, j-i), i, j, TokenType::String);
                tokens.push_back(newToken);
                i = j;
                continue;
            }
            else
            {
                setCurrentBlockState(static_cast<int>(BlockState::LongStringSingleMiddle));
                setFormat(0, a_text.length(), m_stringFormat);
                return;
            }
        }

//------Long string continuation, double quotes---------------------------------

        if((i == 0) && (
            (previousBlockState() == static_cast<int>(BlockState::LongStringDoubleStart)) ||
            (previousBlockState() == static_cast<int>(BlockState::LongStringDoubleMiddle))))
        {
            bool foundMatchingQuotes = false;
            for(j = i; j < textLength - 2; ++j)
            {
                if((a_text.mid(j, 3) == "\"\"\"") &&
                    ((j == 0) || ((j != 0) && (a_text[j - 1] != '\\'))))
                {
                    foundMatchingQuotes = true;
                    break;
                }
            }

            if(foundMatchingQuotes)
            {
                j += 3;
                Token newToken(a_text.mid(i, j-i), i, j - i, TokenType::String);
                tokens.push_back(newToken);
                i = j;
                continue;
            }
            else
            {
                setCurrentBlockState(static_cast<int>(BlockState::LongStringDoubleMiddle));
                setFormat(0, a_text.length(), m_stringFormat);
                return;
            }
        }

//------Long string, single quotes.---------------------------------------------

        if((((a_text[i].toLower() == 'r') || (a_text[i].toLower() == 'u')) &&
            (a_text.mid(i + 1, 3) == "'''")) || (a_text.mid(i, 3) == "'''"))
        {
            if(a_text[i] == '\'')
                j = i + 3;
            else
                j = i + 4;

            bool foundMatchingQuotes = false;
            for(; j < textLength - 2; ++j)
            {
                if((a_text.mid(j, 3) == "'''") &&
                    ((j == 0) || ((j != 0) && (a_text[j - 1] != '\\'))))
                {
                    foundMatchingQuotes = true;
                    break;
                }
            }

            if(foundMatchingQuotes)
            {
                j += 3 - i;
                Token newToken(a_text.mid(i, j), i, j, TokenType::String);
                tokens.push_back(newToken);
                i += j;
                continue;
            }
            else
            {
                j = textLength - i;
                Token newToken(a_text.mid(i, j), i, j, TokenType::String);
                tokens.push_back(newToken);
                setCurrentBlockState(static_cast<int>(BlockState::LongStringSingleStart));
                break;
            }
        }

//------Long string, double quotes----------------------------------------------

        if((((a_text[i].toLower() == 'r') || (a_text[i].toLower() == 'u')) &&
            (a_text.mid(i + 1, 3) == "\"\"\"")) ||
            (a_text.mid(i, 3) == "\"\"\""))
        {
            if(a_text[i] == '\"')
                j = i + 3;
            else
                j = i + 4;

            bool foundMatchingQuotes = false;
            for(; j < textLength - 2; ++j)
            {
                if((a_text.mid(j, 3) == "\"\"\"") &&
                    ((j == 0) || ((j != 0) && (a_text[j - 1] != '\\'))))
                {
                    foundMatchingQuotes = true;
                    break;
                }
            }

            if(foundMatchingQuotes)
            {
                j += 3 - i;
                Token newToken(a_text.mid(i, j), i, j, TokenType::String);
                tokens.push_back(newToken);
                i += j;
                continue;
            }
            else
            {
                j = textLength - i;
                Token newToken(a_text.mid(i, j), i, j, TokenType::String);
                tokens.push_back(newToken);
                setCurrentBlockState(static_cast<int>(BlockState::LongStringDoubleStart));
                break;
            }
        }

//------Short string, single quotes---------------------------------------------

        if((a_text[i] == '\'') || (a_text.mid(i, 2).toLower() == "r'") ||
            (a_text.mid(i, 2).toLower() == "u'"))
        {
            if(a_text[i] == '\'')
                j = i + 1;
            else
                j = i + 2;

            for(; j < textLength; ++j)
            {
                if((a_text[j] == '\'') &&
                    ((j == 0) || ((j != 0) && (a_text[j - 1] != '\\'))))
                    break;
            }

            j += 1 - i;
            Token newToken(a_text.mid(i, j), i, j, TokenType::String);
            tokens.push_back(newToken);
            i += j;
            continue;
        }

//------Short string, double quotes---------------------------------------------

        if((a_text[i] == '\"') || (a_text.mid(i, 2).toLower() == "r\"") ||
            (a_text.mid(i, 2).toLower() == "u\""))
        {
            if(a_text[i] == '\"')
                j = i + 1;
            else
                j = i + 2;

            for(; j < textLength; ++j)
            {
                if((a_text[j] == '\"') &&
                    ((j == 0) || ((j != 0) && (a_text[j - 1] != '\\'))))
                    break;
            }

            j += 1 - i;
            Token newToken(a_text.mid(i, j), i, j, TokenType::String);
            tokens.push_back(newToken);
            i += j;
            continue;
        }

//------Comment-----------------------------------------------------------------

        if(a_text[i] == '#')
        {
            j = a_text.length();
            Token newToken(a_text.mid(i, j-i), i, j, TokenType::Comment);
            tokens.push_back(newToken);
            break;
        }

//------Keyword or unknown word-------------------------------------------------

        if((a_text[i].isLetter()) || (a_text[i] == '_'))
        {
            for(j = i; j < textLength; ++j)
            {
                if(!(a_text[j].isLetterOrNumber() || (a_text[j] == '_')))
                    break;
            }

            j = j - i;
            QString word = a_text.mid(i, j);
            Token newToken(word, i, j , TokenType::Undecided);
            for(const QString & keyword : m_keywordsList)
            {
                if(word == keyword)
                {
                    newToken.type = TokenType::Keyword;
                    break;
                }
            }
            tokens.push_back(newToken);
            i += j;
            continue;
        }

//------Number------------------------------------------------------------------

        NumberMatcher matcher;
        if(matcher.beginsWithNumber(a_text, i))
        {
            j = matcher.matchedLength();
            Token newToken(a_text.mid(i, j), i, j, TokenType::Number);
            tokens.push_back(newToken);
            i += j;
            continue;
        }

//------Operator----------------------------------------------------------------

        goToNextToken = false;
        for(const QString & operatorString : m_operatorsList)
        {
            if(goToNextToken)
                break;

            j = operatorString.length();
            QString substring = a_text.mid(i, j);
            if(substring == operatorString)
            {
                Token newToken(substring, i, j, TokenType::Operator);
                tokens.push_back(newToken);
                i += j;
                goToNextToken = true;
            }
        }
        if(goToNextToken)
            continue;

//------------------------------------------------------------------------------

        i++;
    }
    size_t tokensNumber = tokens.size();

    if(tokensNumber == 0)
        setCurrentBlockState(previousBlockState());


    for(size_t k = 0; k < tokensNumber; ++k)
    {
        Token & token = tokens[k];

        if(token.type == TokenType::Keyword)
            setFormat(token.start, token.length, m_keywordFormat);
        else if(token.type == TokenType::Operator)
            setFormat(token.start, token.length, m_operatorFormat);
        else if(token.type == TokenType::String)
            setFormat(token.start, token.length, m_stringFormat);
        else if(token.type == TokenType::Number)
            setFormat(token.start, token.length, m_numberFormat);
        else if(token.type == TokenType::Comment)
            setFormat(token.start, token.length, m_commentFormat);
    }
}

void SyntaxHighlighter::addSyntaxKeywords(const QStringList& a_keywords, const QTextCharFormat& a_format)
{
    HighlightingRule rule;

    for(QString keyword : a_keywords)
    {
        rule.pattern = QRegularExpression(QString("\\b%1\\b").arg(keyword));
        rule.format = a_format.isEmpty() ? m_keywordFormat : a_format;
        m_highlightingRules.append(rule);
    }
}

void SyntaxHighlighter::addSyntaxComment(const ECOMMENT_TYPE& a_type, const QTextCharFormat& a_format)
{
    HighlightingRule rule;
    QString pattern;

    if(a_type == eCOMMENT_TYPE_DOBULE_SLASH)
    {
        pattern = "//[^\n]*";
    }
    else
    {
        pattern = "#[^\n]*";
    }
    rule.pattern = QRegularExpression(pattern);
    rule.format = a_format.isEmpty() ? m_commentFormat : a_format;
    m_highlightingRules.append(rule);
}

void SyntaxHighlighter::addSyntaxFunction(const QTextCharFormat& a_format)
{
    HighlightingRule rule;

    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_.]+(?=\\()");
    rule.format = a_format.isEmpty() ? m_functionFormat : a_format;
    m_highlightingRules.append(rule);
}

void SyntaxHighlighter::addSyntax(const QString& a_pattern, const QTextCharFormat& a_format)
{
    HighlightingRule rule;

    rule.pattern = QRegularExpression(a_pattern);
    rule.format = a_format;
    m_highlightingRules.append(rule);
}

void SyntaxHighlighter::clear(void)
{
    m_highlightingRules.clear();
}

