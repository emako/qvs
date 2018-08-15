#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;


class ScriptEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    ScriptEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    QString getCurrentCursorText(void);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *m_pLineNumberArea;
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(ScriptEditor *editor) : QWidget(editor) {
        m_pScriptEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(m_pScriptEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        m_pScriptEditor->lineNumberAreaPaintEvent(event);
    }

private:
    ScriptEditor *m_pScriptEditor;
};

enum class ColorLineNumArea{
    r = 240,
    g = 240,
    b = 240,
};

enum class ColorLineNum{
    r = 140,
    g = 140,
    b = 140,
};

enum class ColorHighlight{
    r = 232,
    g = 232,
    b = 255,
};


#endif
