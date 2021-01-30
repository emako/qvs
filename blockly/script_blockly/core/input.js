/**
 * @license
 * Copyright 2012 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @fileoverview Object representing an input (value, statement, or dummy).
 * @author fraser@google.com (Neil Fraser)
 */
'use strict';

goog.provide('Blockly.Input');

goog.require('Blockly.Connection');
goog.require('Blockly.FieldLabel');


/**
 * Class for an input with an optional field.
 * @param {number} type The type of the input.
 * @param {string} name Language-neutral identifier which may used to find this
 *     input again.
 * @param {!Blockly.Block} block The block containing this input.
 * @param {Blockly.Connection} connection Optional connection for this input.
 * @constructor
 */
Blockly.Input = function(type, name, block, connection) {
  if (type != Blockly.DUMMY_INPUT && !name) {
    throw Error('Value inputs and statement inputs must have non-empty name.');
  }
  /** @type {number} */
  this.type = type;
  /** @type {string} */
  this.name = name;
  /**
   * @type {!Blockly.Block}
   * @private
   */
  this.sourceBlock_ = block;
  /** @type {Blockly.Connection} */
  this.connection = connection;
  /** @type {!Array.<!Blockly.Field>} */
  this.fieldRow = [];
};

/**
 * Alignment of input's fields (left, right or centre).
 * @type {number}
 */
Blockly.Input.prototype.align = Blockly.ALIGN_LEFT;

/**
 * Is the input visible?
 * @type {boolean}
 * @private
 */
Blockly.Input.prototype.visible_ = true;

/**
 * Get the source block for this input.
 * @return {Blockly.Block} The source block, or null if there is none.
 */
Blockly.Input.prototype.getSourceBlock = function() {
  return this.sourceBlock_;
};

/**
 * Add a field (or label from string), and all prefix and suffix fields, to the
 * end of the input's field row.
 * @param {string|!Blockly.Field} field Something to add as a field.
 * @param {string=} opt_name Language-neutral identifier which may used to find
 *     this field again.  Should be unique to the host block.
 * @return {!Blockly.Input} The input being append to (to allow chaining).
 */
Blockly.Input.prototype.appendField = function(field, opt_name) {
  this.insertFieldAt(this.fieldRow.length, field, opt_name);
  return this;
};

/**
 * Inserts a field (or label from string), and all prefix and suffix fields, at
 * the location of the input's field row.
 * @param {number} index The index at which to insert field.
 * @param {string|!Blockly.Field} field Something to add as a field.
 * @param {string=} opt_name Language-neutral identifier which may used to find
 *     this field again.  Should be unique to the host block.
 * @return {number} The index following the last inserted field.
 */
Blockly.Input.prototype.insertFieldAt = function(index, field, opt_name) {
  if (index < 0 || index > this.fieldRow.length) {
    throw Error('index ' + index + ' out of bounds.');
  }
  // Falsy field values don't generate a field, unless the field is an empty
  // string and named.
  if (!field && !(field == '' && opt_name)) {
    return index;
  }

  // Generate a FieldLabel when given a plain text field.
  if (typeof field == 'string') {
    field = new Blockly.FieldLabel(/** @type {string} */ (field));
  }

  field.setSourceBlock(this.sourceBlock_);
  if (this.sourceBlock_.rendered) {
    field.init();
  }
  field.name = opt_name;
  field.setVisible(this.isVisible());

  var fieldDropdown = /** @type {Blockly.FieldDropdown} */ (field);
  if (fieldDropdown.prefixField) {
    // Add any prefix.
    index = this.insertFieldAt(index, fieldDropdown.prefixField);
  }
  // Add the field to the field row.
  this.fieldRow.splice(index, 0, field);
  ++index;
  if (fieldDropdown.suffixField) {
    // Add any suffix.
    index = this.insertFieldAt(index, fieldDropdown.suffixField);
  }

  if (this.sourceBlock_.rendered) {
    this.sourceBlock_ = /** @type {!Blockly.BlockSvg} */ (this.sourceBlock_);
    this.sourceBlock_.render();
    // Adding a field will cause the block to change shape.
    this.sourceBlock_.bumpNeighbours();
  }
  return index;
};

/**
 * Remove a field from this input.
 * @param {string} name The name of the field.
 * @param {boolean=} opt_quiet True to prevent an error if field is not present.
 * @return {boolean} True if operation succeeds, false if field is not present
 *     and opt_quiet is true.
 * @throws {Error} if the field is not present and opt_quiet is false.
 */
Blockly.Input.prototype.removeField = function(name, opt_quiet) {
  for (var i = 0, field; (field = this.fieldRow[i]); i++) {
    if (field.name === name) {
      field.dispose();
      this.fieldRow.splice(i, 1);
      if (this.sourceBlock_.rendered) {
        this.sourceBlock_ = /** @type {!Blockly.BlockSvg} */ (this.sourceBlock_);
        this.sourceBlock_.render();
        // Removing a field will cause the block to change shape.
        this.sourceBlock_.bumpNeighbours();
      }
      return true;
    }
  }
  if (opt_quiet) {
    return false;
  } else {
    throw Error('Field "' + name + '" not found.');
  }
};

/**
 * Gets whether this input is visible or not.
 * @return {boolean} True if visible.
 */
Blockly.Input.prototype.isVisible = function() {
  return this.visible_;
};

/**
 * Sets whether this input is visible or not.
 * Should only be used to collapse/uncollapse a block.
 * @param {boolean} visible True if visible.
 * @return {!Array.<!Blockly.BlockSvg>} List of blocks to render.
 * @package
 */
Blockly.Input.prototype.setVisible = function(visible) {
  // Note: Currently there are only unit tests for block.setCollapsed()
  // because this function is package. If this function goes back to being a
  // public API tests (lots of tests) should be added.
  var renderList = [];
  if (this.visible_ == visible) {
    return renderList;
  }
  this.visible_ = visible;

  for (var y = 0, field; (field = this.fieldRow[y]); y++) {
    field.setVisible(visible);
  }
  if (this.connection) {
    this.connection =
      /** @type {!Blockly.RenderedConnection} */ (this.connection);
    // Has a connection.
    if (visible) {
      renderList = this.connection.startTrackingAll();
    } else {
      this.connection.stopTrackingAll();
    }
    var child = this.connection.targetBlock();
    if (child) {
      child.getSvgRoot().style.display = visible ? 'block' : 'none';
    }
  }
  return renderList;
};

/**
 * Mark all fields on this input as dirty.
 * @package
 */
Blockly.Input.prototype.markDirty = function() {
  for (var y = 0, field; (field = this.fieldRow[y]); y++) {
    field.markDirty();
  }
};

/**
 * Change a connection's compatibility.
 * @param {string|Array.<string>|null} check Compatible value type or
 *     list of value types.  Null if all types are compatible.
 * @return {!Blockly.Input} The input being modified (to allow chaining).
 */
Blockly.Input.prototype.setCheck = function(check) {
  if (!this.connection) {
    throw Error('This input does not have a connection.');
  }
  this.connection.setCheck(check);
  return this;
};

/**
 * Change the alignment of the connection's field(s).
 * @param {number} align One of Blockly.ALIGN_LEFT, ALIGN_CENTRE, ALIGN_RIGHT.
 *   In RTL mode directions are reversed, and ALIGN_RIGHT aligns to the left.
 * @return {!Blockly.Input} The input being modified (to allow chaining).
 */
Blockly.Input.prototype.setAlign = function(align) {
  this.align = align;
  if (this.sourceBlock_.rendered) {
    this.sourceBlock_ = /** @type {!Blockly.BlockSvg} */ (this.sourceBlock_);
    this.sourceBlock_.render();
  }
  return this;
};

/**
 * Initialize the fields on this input.
 */
Blockly.Input.prototype.init = function() {
  if (!this.sourceBlock_.workspace.rendered) {
    return;  // Headless blocks don't need fields initialized.
  }
  for (var i = 0; i < this.fieldRow.length; i++) {
    this.fieldRow[i].init();
  }
};

/**
 * Sever all links to this input.
 * @suppress {checkTypes}
 */
Blockly.Input.prototype.dispose = function() {
  for (var i = 0, field; (field = this.fieldRow[i]); i++) {
    field.dispose();
  }
  if (this.connection) {
    this.connection.dispose();
  }
  this.sourceBlock_ = null;
};
