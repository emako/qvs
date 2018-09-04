#ifndef STYLE_SHEET_H
#define STYLE_SHEET_H

static const char *c_qss_slider_white_circle =
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

#endif // STYLE_SHEET_H
