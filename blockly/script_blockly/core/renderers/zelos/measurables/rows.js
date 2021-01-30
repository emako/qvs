/**
 * @license
 * Copyright 2019 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @fileoverview An object representing a single row on a rendered block and all
 * of its subcomponents.
 * @author samelh@google.com (Sam El-Husseini)
 */
'use strict';

goog.provide('Blockly.zelos.BottomRow');
goog.provide('Blockly.zelos.TopRow');

goog.require('Blockly.blockRendering.BottomRow');
goog.require('Blockly.blockRendering.TopRow');
goog.require('Blockly.blockRendering.SpacerRow');
goog.require('Blockly.utils.object');


/**
 * An object containing information about what elements are in the top row of a
 * block as well as sizing information for the top row.
 * Elements in a top row can consist of corners, hats, spacers, and previous
 * connections.
 * After this constructor is called, the row will contain all non-spacer
 * elements it needs.
 * @param {!Blockly.blockRendering.ConstantProvider} constants The rendering
 *   constants provider.
 * @package
 * @constructor
 * @extends {Blockly.blockRendering.TopRow}
 */
Blockly.zelos.TopRow = function(constants) {
  Blockly.zelos.TopRow.superClass_.constructor.call(this, constants);
};
Blockly.utils.object.inherits(Blockly.zelos.TopRow,
    Blockly.blockRendering.TopRow);

/**
 * @override
 */
Blockly.zelos.TopRow.prototype.endsWithElemSpacer = function() {
  return false;
};

/**
 * Render a round corner unless the block has an output connection.
 * @override
 */
Blockly.zelos.TopRow.prototype.hasLeftSquareCorner = function(block) {
  var hasHat = (block.hat ?
      block.hat === 'cap' : this.constants_.ADD_START_HATS) &&
      !block.outputConnection && !block.previousConnection;
  return !!block.outputConnection || hasHat;
};

/**
 * Render a round corner unless the block has an output connection.
 * @override
 */
Blockly.zelos.TopRow.prototype.hasRightSquareCorner = function(block) {
  return !!block.outputConnection && !block.statementInputCount &&
    !block.nextConnection;
};

/**
 * An object containing information about what elements are in the bottom row of
 * a block as well as spacing information for the top row.
 * Elements in a bottom row can consist of corners, spacers and next
 * connections.
 * @param {!Blockly.blockRendering.ConstantProvider} constants The rendering
 *   constants provider.
 * @package
 * @constructor
 * @extends {Blockly.blockRendering.BottomRow}
 */
Blockly.zelos.BottomRow = function(constants) {
  Blockly.zelos.BottomRow.superClass_.constructor.call(this, constants);
};
Blockly.utils.object.inherits(Blockly.zelos.BottomRow,
    Blockly.blockRendering.BottomRow);

/**
 * @override
 */
Blockly.zelos.BottomRow.prototype.endsWithElemSpacer = function() {
  return false;
};

/**
 * Render a round corner unless the block has an output connection.
 * @override
 */
Blockly.zelos.BottomRow.prototype.hasLeftSquareCorner = function(block) {
  return !!block.outputConnection;
};

/**
 * Render a round corner unless the block has an output connection.
 * @override
 */
Blockly.zelos.BottomRow.prototype.hasRightSquareCorner = function(block) {
  return !!block.outputConnection && !block.statementInputCount &&
    !block.nextConnection;
};
