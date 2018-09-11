//-------------------------------------------------
//
// Qt Style Sheet Source File.
// At present, only a few widgets use this style file,
// so the resource file CSS is not used.
// ->@#include "style_sheet.h"
//
//-------------------------------------------------

#include "style_sheet.h"

//////////////////////////////
/// QLineEdit
///
const char *c_qss_line_edit_read_only =
"QLineEdit"
"{"
    "background-color: rgb(243, 243, 243);"
"}";

//////////////////////////////
/// QLabel
///
const char *c_qss_label_under_line =
"QLabel"
"{"
    "color: rgb(0, 0, 255);"
"}";

const char *c_qss_label_bk_dot_grid =
"QLabel"
"{"
    "background-image:url(:/buttons/dot_grid.png)"
"}";

//////////////////////////////
/// QProgressBar
///
const char *c_qss_process_bar_pink_lady =
"QProgressBar"
"{"
    "border: 1px solid grey;"
    "border-radius: 0px;"
    "background-color: #FFFFFF;"
"}"
"QProgressBar::chunk"
"{"
    "background-color: #FDCFE6;"
    "width: 20px;"
"}";

//////////////////////////////
/// QScrollBar
///
const char *c_qss_horizontal_scroll_bar_alpha_gray =
"QScrollBar"
"{"
    "background:transparent;"
    "height:10px;"
"}"
"QScrollBar::handle"
"{"
    "background:lightgray;"
    "border:2px solid transparent;"
    "border-radius:5px;"
"}"
"QScrollBar::handle:hover"
"{"
    "background:gray;"
"}"
"QScrollBar::sub-line"
"{"
    "background:transparent;"
"}"
"QScrollBar::add-line"
"{"
    "background:transparent;"
"}";

const char *c_qss_vertical_scroll_bar_alpha_gray =
"QScrollBar"
"{"
    "background:transparent;"
    "width: 10px;"
"}"
"QScrollBar::handle"
"{"
    "background:lightgray;"
    "border:2px solid transparent;"
    "border-radius:5px;"
"}"
"QScrollBar::handle:hover"
"{"
    "background:gray;"
"}"
"QScrollBar::sub-line"
"{"
    "background:transparent;"
"}"
"QScrollBar::add-line"
"{"
    "background:transparent;"
"}";

//////////////////////////////
/// QSlider
///
const char *c_qss_slider_white_circle =
"QSlider"
"{"
    "border-color: #bcbcbc;"
"}"
"QSlider::groove:horizontal,QSlider::groove:vertical"
"{"
    "border: 1px solid #999999;"
    "height: 1px;"
    "margin: 0px 0;"
    "left: 5px; right: 5px;"
 "}"
"QSlider::handle:horizontal,QSlider::handle:vertical"
"{"
    "border: 0px;"
    "border-image:  url(:/style/white_circle.png);"
    "width: 15px;"
    "margin: -7px -7px -7px -7px;"
"}"
"QSlider::add-page:horizontal,QSlider::add-page:vertical"
"{"
    "background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #bcbcbc, stop:0.25 #bcbcbc, stop:0.5 #bcbcbc, stop:1 #bcbcbc);"
"}"
"QSlider::sub-page:horizontal,QSlider::sub-page:vertical"
"{"
    "background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #F48EC2, stop:0.25 #F48EC2, stop:0.5 #F48EC2, stop:1 #F48EC2);"
"}";

//////////////////////////////
/// QSpinBox, QDoubleSpinBox
///
const char *c_qss_spin_box_background_alpha_half =
"QSpinBox,QDoubleSpinBox"
"{"
    "background-color: rgba(255, 255, 255, 128);"
"}";

//////////////////////////////
/// QTableWidget
///
const char *c_qss_table_widget_selection_bk_focus_in =
"QTableWidget"
"{"
    "selection-background-color:#FDCFE6;"
    "selection-color:#023019;"
"}";

const char *c_qss_table_widget_selection_bk_focus_out =
"QTableWidget"
"{"
    "selection-background-color:#F0F0F0;"
    "selection-color:#023019;"
"}";
