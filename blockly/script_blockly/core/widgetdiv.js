/**
 * @license
 * Copyright 2013 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @fileoverview A div that floats on top of Blockly.  This singleton contains
 *     temporary HTML UI widgets that the user is currently interacting with.
 *     E.g. text input areas, colour pickers, context menus.
 * @author fraser@google.com (Neil Fraser)
 */
'use strict';

/**
 * @name Blockly.WidgetDiv
 * @namespace
 */
goog.provide('Blockly.WidgetDiv');

goog.require('Blockly.utils.style');

goog.requireType('Blockly.utils.Rect');
goog.requireType('Blockly.utils.Size');


/**
 * The object currently using this container.
 * @type {Object}
 * @private
 */
Blockly.WidgetDiv.owner_ = null;

/**
 * Optional cleanup function set by whichever object uses the widget.
 * @type {Function}
 * @private
 */
Blockly.WidgetDiv.dispose_ = null;

/**
 * A class name representing the current owner's workspace renderer.
 * @type {string}
 * @private
 */
Blockly.WidgetDiv.rendererClassName_ = '';

/**
 * A class name representing the current owner's workspace theme.
 * @type {string}
 * @private
 */
Blockly.WidgetDiv.themeClassName_ = '';

/**
 * Create the widget div and inject it onto the page.
 */
Blockly.WidgetDiv.createDom = function() {
  if (Blockly.WidgetDiv.DIV) {
    return;  // Already created.
  }
  /**
   * The HTML container for popup overlays (e.g. editor widgets).
   * @type {!Element}
   */
  Blockly.WidgetDiv.DIV = document.createElement('div');
  Blockly.WidgetDiv.DIV.className = 'blocklyWidgetDiv';
  var container = Blockly.parentContainer || document.body;
  container.appendChild(Blockly.WidgetDiv.DIV);
};

/**
 * Initialize and display the widget div.  Close the old one if needed.
 * @param {!Object} newOwner The object that will be using this container.
 * @param {boolean} rtl Right-to-left (true) or left-to-right (false).
 * @param {Function} dispose Optional cleanup function to be run when the
 *     widget is closed.
 */
Blockly.WidgetDiv.show = function(newOwner, rtl, dispose) {
  Blockly.WidgetDiv.hide();
  Blockly.WidgetDiv.owner_ = newOwner;
  Blockly.WidgetDiv.dispose_ = dispose;
  var div = Blockly.WidgetDiv.DIV;
  div.style.direction = rtl ? 'rtl' : 'ltr';
  div.style.display = 'block';
  var mainWorkspace =
    /** @type {!Blockly.WorkspaceSvg} */ (Blockly.getMainWorkspace());
  Blockly.WidgetDiv.rendererClassName_ =
      mainWorkspace.getRenderer().getClassName();
  Blockly.WidgetDiv.themeClassName_ = mainWorkspace.getTheme().getClassName();
  Blockly.utils.dom.addClass(div, Blockly.WidgetDiv.rendererClassName_);
  Blockly.utils.dom.addClass(div, Blockly.WidgetDiv.themeClassName_);
};

/**
 * Destroy the widget and hide the div.
 */
Blockly.WidgetDiv.hide = function() {
  if (!Blockly.WidgetDiv.isVisible()) {
    return;
  }
  Blockly.WidgetDiv.owner_ = null;

  var div = Blockly.WidgetDiv.DIV;
  div.style.display = 'none';
  div.style.left = '';
  div.style.top = '';
  Blockly.WidgetDiv.dispose_ && Blockly.WidgetDiv.dispose_();
  Blockly.WidgetDiv.dispose_ = null;
  div.textContent = '';

  if (Blockly.WidgetDiv.rendererClassName_) {
    Blockly.utils.dom.removeClass(div, Blockly.WidgetDiv.rendererClassName_);
    Blockly.WidgetDiv.rendererClassName_ = '';
  }
  if (Blockly.WidgetDiv.themeClassName_) {
    Blockly.utils.dom.removeClass(div, Blockly.WidgetDiv.themeClassName_);
    Blockly.WidgetDiv.themeClassName_ = '';
  }
  (/** @type {!Blockly.WorkspaceSvg} */ (
    Blockly.getMainWorkspace())).markFocused();
};

/**
 * Is the container visible?
 * @return {boolean} True if visible.
 */
Blockly.WidgetDiv.isVisible = function() {
  return !!Blockly.WidgetDiv.owner_;
};

/**
 * Destroy the widget and hide the div if it is being used by the specified
 * object.
 * @param {!Object} oldOwner The object that was using this container.
 */
Blockly.WidgetDiv.hideIfOwner = function(oldOwner) {
  if (Blockly.WidgetDiv.owner_ == oldOwner) {
    Blockly.WidgetDiv.hide();
  }
};

/**
 * Set the widget div's position and height.  This function does nothing clever:
 * it will not ensure that your widget div ends up in the visible window.
 * @param {number} x Horizontal location (window coordinates, not body).
 * @param {number} y Vertical location (window coordinates, not body).
 * @param {number} height The height of the widget div (pixels).
 * @private
 */
Blockly.WidgetDiv.positionInternal_ = function(x, y, height) {
  Blockly.WidgetDiv.DIV.style.left = x + 'px';
  Blockly.WidgetDiv.DIV.style.top = y + 'px';
  Blockly.WidgetDiv.DIV.style.height = height + 'px';
};

/**
 * Position the widget div based on an anchor rectangle.
 * The widget should be placed adjacent to but not overlapping the anchor
 * rectangle.  The preferred position is directly below and aligned to the left
 * (LTR) or right (RTL) side of the anchor.
 * @param {!Blockly.utils.Rect} viewportBBox The bounding rectangle of the
 *     current viewport, in window coordinates.
 * @param {!Blockly.utils.Rect} anchorBBox The bounding rectangle of the anchor,
 *     in window coordinates.
 * @param {!Blockly.utils.Size} widgetSize The size of the widget that is inside
 *     the widget div, in window coordinates.
 * @param {boolean} rtl Whether the workspace is in RTL mode.  This determines
 *     horizontal alignment.
 * @package
 */
Blockly.WidgetDiv.positionWithAnchor = function(viewportBBox, anchorBBox,
    widgetSize, rtl) {
  var y = Blockly.WidgetDiv.calculateY_(viewportBBox, anchorBBox, widgetSize);
  var x = Blockly.WidgetDiv.calculateX_(viewportBBox, anchorBBox, widgetSize,
      rtl);

  if (y < 0) {
    Blockly.WidgetDiv.positionInternal_(x, 0, widgetSize.height + y);
  } else {
    Blockly.WidgetDiv.positionInternal_(x, y, widgetSize.height);
  }
};

/**
 * Calculate an x position (in window coordinates) such that the widget will not
 * be offscreen on the right or left.
 * @param {!Blockly.utils.Rect} viewportBBox The bounding rectangle of the
 *     current viewport, in window coordinates.
 * @param {!Blockly.utils.Rect} anchorBBox The bounding rectangle of the anchor,
 *     in window coordinates.
 * @param {Blockly.utils.Size} widgetSize The dimensions of the widget inside the
 *     widget div.
 * @param {boolean} rtl Whether the Blockly workspace is in RTL mode.
 * @return {number} A valid x-coordinate for the top left corner of the widget
 *     div, in window coordinates.
 * @private
 */
Blockly.WidgetDiv.calculateX_ = function(viewportBBox, anchorBBox, widgetSize,
    rtl) {
  if (rtl) {
    // Try to align the right side of the field and the right side of widget.
    var widgetLeft = anchorBBox.right - widgetSize.width;
    // Don't go offscreen left.
    var x = Math.max(widgetLeft, viewportBBox.left);
    // But really don't go offscreen right:
    return Math.min(x, viewportBBox.right - widgetSize.width);
  } else {
    // Try to align the left side of the field and the left side of widget.
    // Don't go offscreen right.
    var x = Math.min(anchorBBox.left, viewportBBox.right - widgetSize.width);
    // But left is more important, because that's where the text is.
    return Math.max(x, viewportBBox.left);
  }
};

/**
 * Calculate a y position (in window coordinates) such that the widget will not
 * be offscreen on the top or bottom.
 * @param {!Blockly.utils.Rect} viewportBBox The bounding rectangle of the
 *     current viewport, in window coordinates.
 * @param {!Blockly.utils.Rect} anchorBBox The bounding rectangle of the anchor,
 *     in window coordinates.
 * @param {Blockly.utils.Size} widgetSize The dimensions of the widget inside the
 *     widget div.
 * @return {number} A valid y-coordinate for the top left corner of the widget
 *     div, in window coordinates.
 * @private
 */
Blockly.WidgetDiv.calculateY_ = function(viewportBBox, anchorBBox, widgetSize) {
  // Flip the widget vertically if off the bottom.
  if (anchorBBox.bottom + widgetSize.height >= viewportBBox.bottom) {
    // The bottom of the widget is at the top of the field.
    return anchorBBox.top - widgetSize.height;
    // The widget could go off the top of the window, but it would also go off
    // the bottom.  The window is just too small.
  } else {
    // The top of the widget is at the bottom of the field.
    return anchorBBox.bottom;
  }
};
