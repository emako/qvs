/**
 * @license
 * Copyright 2019 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @fileoverview Blockly menu similar to Closure's goog.ui.Menu
 * @author samelh@google.com (Sam El-Husseini)
 */
'use strict';

goog.provide('Blockly.Menu');

goog.require('Blockly.utils.aria');
goog.require('Blockly.utils.Coordinate');
goog.require('Blockly.utils.dom');
goog.require('Blockly.utils.KeyCodes');
goog.require('Blockly.utils.style');


/**
 * A basic menu class.
 * @constructor
 */
Blockly.Menu = function() {
  /**
   * Array of menu items.
   * (Nulls are never in the array, but typing the array as nullable prevents
   * the compiler from objecting to .indexOf(null))
   * @type {!Array.<Blockly.MenuItem>}
   * @private
   */
  this.menuItems_ = [];

  /**
   * Coordinates of the mousedown event that caused this menu to open. Used to
   * prevent the consequent mouseup event due to a simple click from activating
   * a menu item immediately.
   * @type {?Blockly.utils.Coordinate}
   * @package
   */
  this.openingCoords = null;

  /**
   * This is the element that we will listen to the real focus events on.
   * A value of null means no menu item is highlighted.
   * @type {Blockly.MenuItem}
   * @private
   */
  this.highlightedItem_ = null;

  /**
   * Mouse over event data.
   * @type {?Blockly.EventData}
   * @private
   */
  this.mouseOverHandler_ = null;

  /**
   * Click event data.
   * @type {?Blockly.EventData}
   * @private
   */
  this.clickHandler_ = null;

  /**
   * Mouse enter event data.
   * @type {?Blockly.EventData}
   * @private
   */
  this.mouseEnterHandler_ = null;

  /**
   * Mouse leave event data.
   * @type {?Blockly.EventData}
   * @private
   */
  this.mouseLeaveHandler_ = null;

  /**
   * Key down event data.
   * @type {?Blockly.EventData}
   * @private
   */
  this.onKeyDownHandler_ = null;

  /**
   * The menu's root DOM element.
   * @type {Element}
   * @private
   */
  this.element_ = null;

  /**
   * ARIA name for this menu.
   * @type {?Blockly.utils.aria.Role}
   * @private
   */
  this.roleName_ = null;
};


/**
 * Add a new menu item to the bottom of this menu.
 * @param {!Blockly.MenuItem} menuItem Menu item to append.
 */
Blockly.Menu.prototype.addChild = function(menuItem) {
  this.menuItems_.push(menuItem);
};

/**
 * Creates the menu DOM.
 * @param {!Element} container Element upon which to append this menu.
 */
Blockly.Menu.prototype.render = function(container) {
  var element = /** @type {!HTMLDivElement} */ (document.createElement('div'));
  // goog-menu is deprecated, use blocklyMenu.  May 2020.
  element.className = 'blocklyMenu goog-menu blocklyNonSelectable';
  element.tabIndex = 0;
  if (this.roleName_) {
    Blockly.utils.aria.setRole(element, this.roleName_);
  }
  this.element_ = element;

  // Add menu items.
  for (var i = 0, menuItem; (menuItem = this.menuItems_[i]); i++) {
    element.appendChild(menuItem.createDom());
  }

  // Add event handlers.
  this.mouseOverHandler_ = Blockly.bindEventWithChecks_(element,
      'mouseover', this, this.handleMouseOver_, true);
  this.clickHandler_ = Blockly.bindEventWithChecks_(element,
      'click', this, this.handleClick_, true);
  this.mouseEnterHandler_ = Blockly.bindEventWithChecks_(element,
      'mouseenter', this, this.handleMouseEnter_, true);
  this.mouseLeaveHandler_ = Blockly.bindEventWithChecks_(element,
      'mouseleave', this, this.handleMouseLeave_, true);
  this.onKeyDownHandler_ = Blockly.bindEventWithChecks_(element,
      'keydown', this, this.handleKeyEvent_);

  container.appendChild(element);
};

/**
 * Gets the menu's element.
 * @return {Element} The DOM element.
 * @package
 */
Blockly.Menu.prototype.getElement = function() {
  return this.element_;
};

/**
 * Focus the menu element.
 * @package
 */
Blockly.Menu.prototype.focus = function() {
  var el = this.getElement();
  if (el) {
    el.focus({preventScroll:true});
    Blockly.utils.dom.addClass(el, 'blocklyFocused');
  }
};

/**
 * Blur the menu element.
 * @private
 */
Blockly.Menu.prototype.blur_ = function() {
  var el = this.getElement();
  if (el) {
    el.blur();
    Blockly.utils.dom.removeClass(el, 'blocklyFocused');
  }
};

/**
 * Set the menu accessibility role.
 * @param {!Blockly.utils.aria.Role} roleName role name.
 * @package
 */
Blockly.Menu.prototype.setRole = function(roleName) {
  this.roleName_ = roleName;
};

/**
 * Dispose of this menu.
 */
Blockly.Menu.prototype.dispose = function() {
  // Remove event handlers.
  if (this.mouseOverHandler_) {
    Blockly.unbindEvent_(this.mouseOverHandler_);
    this.mouseOverHandler_ = null;
  }
  if (this.clickHandler_) {
    Blockly.unbindEvent_(this.clickHandler_);
    this.clickHandler_ = null;
  }
  if (this.mouseEnterHandler_) {
    Blockly.unbindEvent_(this.mouseEnterHandler_);
    this.mouseEnterHandler_ = null;
  }
  if (this.mouseLeaveHandler_) {
    Blockly.unbindEvent_(this.mouseLeaveHandler_);
    this.mouseLeaveHandler_ = null;
  }
  if (this.onKeyDownHandler_) {
    Blockly.unbindEvent_(this.onKeyDownHandler_);
    this.onKeyDownHandler_ = null;
  }

  // Remove menu items.
  for (var i = 0, menuItem; (menuItem = this.menuItems_[i]); i++) {
    menuItem.dispose();
  }
  this.element_ = null;
};

// Child component management.

/**
 * Returns the child menu item that owns the given DOM element,
 * or null if no such menu item is found.
 * @param {Element} elem DOM element whose owner is to be returned.
 * @return {?Blockly.MenuItem} Menu item for which the DOM element belongs to.
 * @private
 */
Blockly.Menu.prototype.getMenuItem_ = function(elem) {
  var menuElem = this.getElement();
  // Node might be the menu border (resulting in no associated menu item), or
  // a menu item's div, or some element within the menu item.
  // Walk up parents until one meets either the menu's root element, or
  // a menu item's div.
  while (elem && elem != menuElem) {
    if (Blockly.utils.dom.hasClass(elem, 'blocklyMenuItem')) {
      // Having found a menu item's div, locate that menu item in this menu.
      for (var i = 0, menuItem; (menuItem = this.menuItems_[i]); i++) {
        if (menuItem.getElement() == elem) {
          return menuItem;
        }
      }
    }
    elem = elem.parentElement;
  }
  return null;
};

// Highlight management.

/**
 * Highlights the given menu item, or clears highlighting if null.
 * @param {Blockly.MenuItem} item Item to highlight, or null.
 * @package
 */
Blockly.Menu.prototype.setHighlighted = function(item) {
  var currentHighlighted = this.highlightedItem_;
  if (currentHighlighted) {
    currentHighlighted.setHighlighted(false);
    this.highlightedItem_ = null;
  }
  if (item) {
    item.setHighlighted(true);
    this.highlightedItem_ = item;
    // Bring the highlighted item into view. This has no effect if the menu is
    // not scrollable.
    var el = /** @type {!Element} */ (this.getElement());
    Blockly.utils.style.scrollIntoContainerView(
        /** @type {!Element} */ (item.getElement()), el);

    Blockly.utils.aria.setState(el, Blockly.utils.aria.State.ACTIVEDESCENDANT,
        item.getId());
  }
};

/**
 * Highlights the next highlightable item (or the first if nothing is currently
 * highlighted).
 * @package
 */
Blockly.Menu.prototype.highlightNext = function() {
  var index = this.menuItems_.indexOf(this.highlightedItem_);
  this.highlightHelper_(index, 1);
};

/**
 * Highlights the previous highlightable item (or the last if nothing is
 * currently highlighted).
 * @package
 */
Blockly.Menu.prototype.highlightPrevious = function() {
  var index = this.menuItems_.indexOf(this.highlightedItem_);
  this.highlightHelper_(index < 0 ? this.menuItems_.length : index, -1);
};

/**
 * Highlights the first highlightable item.
 * @private
 */
Blockly.Menu.prototype.highlightFirst_ = function() {
  this.highlightHelper_(-1, 1);
};

/**
 * Highlights the last highlightable item.
 * @private
 */
Blockly.Menu.prototype.highlightLast_ = function() {
  this.highlightHelper_(this.menuItems_.length, -1);
};

/**
 * Helper function that manages the details of moving the highlight among
 * child menuitems in response to keyboard events.
 * @param {number} startIndex Start index.
 * @param {number} delta Step direction: 1 to go down, -1 to go up.
 * @private
 */
Blockly.Menu.prototype.highlightHelper_ = function(startIndex, delta) {
  var index = startIndex + delta;
  var menuItem;
  while ((menuItem = this.menuItems_[index])) {
    if (menuItem.isEnabled()) {
      this.setHighlighted(menuItem);
      break;
    }
    index += delta;
  }
};

// Mouse events.

/**
 * Handles mouseover events. Highlight menuitems as the user hovers over them.
 * @param {!Event} e Mouse event to handle.
 * @private
 */
Blockly.Menu.prototype.handleMouseOver_ = function(e) {
  var menuItem = this.getMenuItem_(/** @type {Element} */ (e.target));

  if (menuItem) {
    if (menuItem.isEnabled()) {
      if (this.highlightedItem_ != menuItem) {
        this.setHighlighted(menuItem);
      }
    } else {
      this.setHighlighted(null);
    }
  }
};

/**
 * Handles click events. Pass the event onto the child menuitem to handle.
 * @param {!Event} e Click event to handle.
 * @private
 */
Blockly.Menu.prototype.handleClick_ = function(e) {
  var oldCoords = this.openingCoords;
  // Clear out the saved opening coords immediately so they're not used twice.
  this.openingCoords = null;
  if (oldCoords && typeof e.clientX == 'number') {
    var newCoords = new Blockly.utils.Coordinate(e.clientX, e.clientY);
    if (Blockly.utils.Coordinate.distance(oldCoords, newCoords) < 1) {
      // This menu was opened by a mousedown and we're handling the consequent
      // click event. The coords haven't changed, meaning this was the same
      // opening event. Don't do the usual behavior because the menu just popped
      // up under the mouse and the user didn't mean to activate this item.
      return;
    }
  }

  var menuItem = this.getMenuItem_(/** @type {Element} */ (e.target));
  if (menuItem) {
    menuItem.performAction();
  }
};

/**
 * Handles mouse enter events. Focus the element.
 * @param {Event} _e Mouse event to handle.
 * @private
 */
Blockly.Menu.prototype.handleMouseEnter_ = function(_e) {
  this.focus();
};

/**
 * Handles mouse leave events. Blur and clear highlight.
 * @param {Event} _e Mouse event to handle.
 * @private
 */
Blockly.Menu.prototype.handleMouseLeave_ = function(_e) {
  if (this.getElement()) {
    this.blur_();
    this.setHighlighted(null);
  }
};

// Keyboard events.

/**
 * Attempts to handle a keyboard event, if the menu item is enabled, by calling
 * {@link handleKeyEventInternal_}.
 * @param {!Event} e Key event to handle.
 * @private
 */
Blockly.Menu.prototype.handleKeyEvent_ = function(e) {
  if (!this.menuItems_.length) {
    // Empty menu.
    return;
  }
  if (e.shiftKey || e.ctrlKey || e.metaKey || e.altKey) {
    // Do not handle the key event if any modifier key is pressed.
    return;
  }

  var highlighted = this.highlightedItem_;
  switch (e.keyCode) {
    case Blockly.utils.KeyCodes.ENTER:
    case Blockly.utils.KeyCodes.SPACE:
      if (highlighted) {
        highlighted.performAction();
      }
      break;

    case Blockly.utils.KeyCodes.UP:
      this.highlightPrevious();
      break;

    case Blockly.utils.KeyCodes.DOWN:
      this.highlightNext();
      break;

    case Blockly.utils.KeyCodes.PAGE_UP:
    case Blockly.utils.KeyCodes.HOME:
      this.highlightFirst_();
      break;

    case Blockly.utils.KeyCodes.PAGE_DOWN:
    case Blockly.utils.KeyCodes.END:
      this.highlightLast_();
      break;

    default:
      // Not a key the menu is interested in.
      return;
  }
  // The menu used this key, don't let it have secondary effects.
  e.preventDefault();
  e.stopPropagation();
};

/**
 * Get the size of a rendered menu.
 * @return {!Blockly.utils.Size} Object with width and height properties.
 * @package
 */
Blockly.Menu.prototype.getSize = function() {
  var menuDom = this.getElement();
  var menuSize = Blockly.utils.style.getSize(/** @type {!Element} */ (menuDom));
  // Recalculate height for the total content, not only box height.
  menuSize.height = menuDom.scrollHeight;
  return menuSize;
};
