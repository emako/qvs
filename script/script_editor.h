#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QWidget>
#include <QSize>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QWheelEvent>
#include <QKeyEvent>

namespace EditorColor
{
    namespace ColorLineNumArea
    {
        enum Color
        {
            r = 240,
            g = 240,
            b = 240,
        };
    };

    namespace ColorLineNum
    {
        enum Color
        {
            r = 140,
            g = 140,
            b = 140,
        };
    };

    namespace ColorHighlight
    {
        enum Color
        {
            r = 232,
            g = 232,
            b = 255,
        };
    };
}

using namespace EditorColor;

class ScriptEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    ScriptEditor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    QString getCurrentCursorText(void);
    void resizeFont(int a_pointSize);

signals:
    void fontPointSizeUpdated(int);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *m_pLineNumberArea;
    bool m_isKeyCtrlPressed;
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(ScriptEditor *editor) : QWidget(editor)
    {
        m_pScriptEditor = editor;
    }

    QSize sizeHint() const override
    {
        return QSize(m_pScriptEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        m_pScriptEditor->lineNumberAreaPaintEvent(event);
    }

private:
    ScriptEditor *m_pScriptEditor;
};

#endif
