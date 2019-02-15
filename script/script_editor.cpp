#include "script_editor.h"

#include <QtWidgets>

ScriptEditor::ScriptEditor(QWidget *parent)
    : QPlainTextEdit(parent),
      m_pLineNumberArea(new LineNumberArea(this)),
      m_isKeyCtrlPressed(false)
{
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

void ScriptEditor::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control)
    {
        m_isKeyCtrlPressed = true;
    }
    QPlainTextEdit::keyPressEvent(e);
    e->accept();
}

void ScriptEditor::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control)
    {
        m_isKeyCtrlPressed = false;
    }
    QPlainTextEdit::keyReleaseEvent(e);
    e->accept();
}

void ScriptEditor::wheelEvent(QWheelEvent* e)
{
    if(m_isKeyCtrlPressed)
    {
        auto resizeFont = [](QWidget *a_pWidget, int a_size) -> void
        {
            QFont font(a_pWidget->font());

            font.setPointSize(a_pWidget->font().pointSize() + a_size);
            a_pWidget->setFont(font);
        };

        if(e->delta() > 0)
        {
            resizeFont(this, 1);
        }
        else
        {
            resizeFont(this, -1);
        }
        emit fontPointSizeUpdated(this->font().pointSize());
    }
    QPlainTextEdit::wheelEvent(e);
    e->accept();
}

void ScriptEditor::resizeFont(int a_pointSize)
{
    QFont font(this->font());

    font.setPointSize(a_pointSize);
    this->setFont(font);
}

void ScriptEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(ColorHighlight::r, ColorHighlight::g, ColorHighlight::b);

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
    painter.fillRect(event->rect(), QColor(ColorLineNumArea::r, ColorLineNumArea::g, ColorLineNumArea::b));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = static_cast<int>(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + static_cast<int>(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(ColorLineNum::r, ColorLineNum::g, ColorLineNum::b));
            painter.drawText(0, top, m_pLineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + static_cast<int>(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

QString ScriptEditor::getCurrentCursorText(void)
{
    QTextCursor cur = this->textCursor();
    return cur.block().text();
}
