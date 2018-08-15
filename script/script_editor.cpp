#include "script_editor.h"

#include <QtWidgets>


ScriptEditor::ScriptEditor(QWidget *parent)
    : QPlainTextEdit(parent)
{
    m_pLineNumberArea = new LineNumberArea(this);
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateLineNumberArea(QRect, int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int ScriptEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }
    if(digits < 2)
    {
        digits = 2;
    }
    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;
    return space;
}

void ScriptEditor::updateLineNumberAreaWidth(int)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void ScriptEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        m_pLineNumberArea->scroll(0, dy);
    else
        m_pLineNumberArea->update(0, rect.y(), m_pLineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void ScriptEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    m_pLineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void ScriptEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor((int)ColorHighlight::r, (int)ColorHighlight::g, (int)ColorHighlight::b);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}


void ScriptEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(m_pLineNumberArea);
    painter.fillRect(event->rect(), QColor((int)ColorLineNumArea::r, (int)ColorLineNumArea::g, (int)ColorLineNumArea::b));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor((int)ColorLineNum::r, (int)ColorLineNum::g, (int)ColorLineNum::b));
            painter.drawText(0, top, m_pLineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

QString ScriptEditor::getCurrentCursorText(void)
{
    QTextCursor cur = this->textCursor();
    return cur.block().text();
}
