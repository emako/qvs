/**
 * @license
 * Copyright 2012 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @fileoverview Object representing a mutator dialog.  A mutator allows the
 * user to change the shape of a block using a nested blocks editor.
 * @author fraser@google.com (Neil Fraser)
 */
'use strict';

goog.provide('Blockly.Mutator');

goog.require('Blockly.Bubble');
goog.require('Blockly.Events');
goog.require('Blockly.Events.BlockChange');
goog.require('Blockly.Events.Ui');
goog.require('Blockly.Icon');
goog.require('Blockly.navigation');
goog.require('Blockly.utils');
goog.require('Blockly.utils.dom');
goog.require('Blockly.utils.global');
goog.require('Blockly.utils.object');
goog.require('Blockly.utils.xml');
goog.require('Blockly.WorkspaceSvg');
goog.require('Blockly.Xml');

goog.requireType('Blockly.utils.Metrics');


/**
 * Class for a mutator dialog.
 * @param {!Array.<string>} quarkNames List of names of sub-blocks for flyout.
 * @extends {Blockly.Icon}
 * @constructor
 */
Blockly.Mutator = function(quarkNames) {
  Blockly.Mutator.superClass_.constructor.call(this, null);
  this.quarkNames_ = quarkNames;
};
Blockly.utils.object.inherits(Blockly.Mutator, Blockly.Icon);

/**
 * Width of workspace.
 * @private
 */
Blockly.Mutator.prototype.workspaceWidth_ = 0;

/**
 * Height of workspace.
 * @private
 */
Blockly.Mutator.prototype.workspaceHeight_ = 0;

/**
 * Set the block this mutator is associated with.
 * @param {Blockly.BlockSvg} block The block associated with this mutator.
 * @package
 */
Blockly.Mutator.prototype.setBlock = function(block) {
  this.block_ = block;
};

/**
 * Returns the workspace inside this mutator icon's bubble.
 * @return {Blockly.WorkspaceSvg} The workspace inside this mutator icon's
 *     bubble.
 * @package
 */
Blockly.Mutator.prototype.getWorkspace = function() {
  return this.workspace_;
};

/**
 * Draw the mutator icon.
 * @param {!Element} group The icon group.
 * @protected
 */
Blockly.Mutator.prototype.drawIcon_ = function(group) {
  // Square with rounded corners.
  Blockly.utils.dom.createSvgElement('rect',
      {
        'class': 'blocklyIconShape',
        'rx': '4',
        'ry': '4',
        'height': '16',
        'width': '16'
      },
      group);
  // Gear teeth.
  Blockly.utils.dom.createSvgElement('path',
      {
        'class': 'blocklyIconSymbol',
        'd': 'm4.203,7.296 0,1.368 -0.92,0.677 -0.11,0.41 0.9,1.559 0.41,' +
             '0.11 1.043,-0.457 1.187,0.683 0.127,1.134 0.3,0.3 1.8,0 0.3,' +
             '-0.299 0.127,-1.138 1.185,-0.682 1.046,0.458 0.409,-0.11 0.9,' +
             '-1.559 -0.11,-0.41 -0.92,-0.677 0,-1.366 0.92,-0.677 0.11,' +
             '-0.41 -0.9,-1.559 -0.409,-0.109 -1.046,0.458 -1.185,-0.682 ' +
             '-0.127,-1.138 -0.3,-0.299 -1.8,0 -0.3,0.3 -0.126,1.135 -1.187,' +
             '0.682 -1.043,-0.457 -0.41,0.11 -0.899,1.559 0.108,0.409z'
      },
      group);
  // Axle hole.
  Blockly.utils.dom.createSvgElement(
      'circle',
      {
        'class': 'blocklyIconShape',
        'r': '2.7',
        'cx': '8',
        'cy': '8'
      },
      group);
};

/**
 * Clicking on the icon toggles if the mutator bubble is visible.
 * Disable if block is uneditable.
 * @param {!Event} e Mouse click event.
 * @private
 * @override
 */
Blockly.Mutator.prototype.iconClick_ = function(e) {
  if (this.block_.isEditable()) {
    Blockly.Icon.prototype.iconClick_.call(this, e);
  }
};

/**
 * Create the editor for the mutator's bubble.
 * @return {!SVGElement} The top-level node of the editor.
 * @private
 */
Blockly.Mutator.prototype.createEditor_ = function() {
  /* Create the editor.  Here's the markup that will be generated:
  <svg>
    [Workspace]
  </svg>
  */
  this.svgDialog_ = Blockly.utils.dom.createSvgElement('svg',
      {'x': Blockly.Bubble.BORDER_WIDTH, 'y': Blockly.Bubble.BORDER_WIDTH},
      null);
  // Convert the list of names into a list of XML objects for the flyout.
  if (this.quarkNames_.length) {
    var quarkXml = Blockly.utils.xml.createElement('xml');
    for (var i = 0, quarkName; (quarkName = this.quarkNames_[i]); i++) {
      var element = Blockly.utils.xml.createElement('block');
      element.setAttribute('type', quarkName);
      quarkXml.appendChild(element);
    }
  } else {
    var quarkXml = null;
  }
  var workspaceOptions = new Blockly.Options(
      /** @type {!Blockly.BlocklyOptions} */
      ({
        // If you want to enable disabling, also remove the
        // event filter from workspaceChanged_ .
        'disable': false,
        'parentWorkspace': this.block_.workspace,
        'media': this.block_.workspace.options.pathToMedia,
        'rtl': this.block_.RTL,
        'horizontalLayout': false,
        'renderer': this.block_.workspace.options.renderer,
        'rendererOverrides': this.block_.workspace.options.rendererOverrides
      }));
  workspaceOptions.toolboxPosition = this.block_.RTL ? Blockly.TOOLBOX_AT_RIGHT :
      Blockly.TOOLBOX_AT_LEFT;
  var hasFlyout = !!quarkXml;
  if (hasFlyout) {
    workspaceOptions.languageTree =
        Blockly.utils.toolbox.convertToolboxToJSON(quarkXml);
    workspaceOptions.getMetrics = this.getFlyoutMetrics_.bind(this);
  }
  this.workspace_ = new Blockly.WorkspaceSvg(workspaceOptions);
  this.workspace_.isMutator = true;
  this.workspace_.addChangeListener(Blockly.Events.disableOrphans);

  // Mutator flyouts go inside the mutator workspace's <g> rather than in
  // a top level svg. Instead of handling scale themselves, mutators
  // inherit scale from the parent workspace.
  // To fix this, scale needs to be applied at a different level in the dom.
  var flyoutSvg = hasFlyout ? this.workspace_.addFlyout('g') : null;
  var background = this.workspace_.createDom('blocklyMutatorBackground');

  if (flyoutSvg) {
    // Insert the flyout after the <rect> but before the block canvas so that
    // the flyout is underneath in z-order.  This makes blocks layering during
    // dragging work properly.
    background.insertBefore(flyoutSvg, this.workspace_.svgBlockCanvas_);
  }
  this.svgDialog_.appendChild(background);

  return this.svgDialog_;
};

/**
 * Add or remove the UI indicating if this icon may be clicked or not.
 */
Blockly.Mutator.prototype.updateEditable = function() {
  Blockly.Mutator.superClass_.updateEditable.call(this);
  if (!this.block_.isInFlyout) {
    if (this.block_.isEditable()) {
      if (this.iconGroup_) {
        Blockly.utils.dom.removeClass(
            /** @type {!Element} */ (this.iconGroup_),
            'blocklyIconGroupReadonly');
      }
    } else {
      // Close any mutator bubble.  Icon is not clickable.
      this.setVisible(false);
      if (this.iconGroup_) {
        Blockly.utils.dom.addClass(
            /** @type {!Element} */ (this.iconGroup_),
            'blocklyIconGroupReadonly');
      }
    }
  }
};

/**
 * Resize the bubble to match the size of the workspace.
 * @private
 */
Blockly.Mutator.prototype.resizeBubble_ = function() {
  var doubleBorderWidth = 2 * Blockly.Bubble.BORDER_WIDTH;
  var workspaceSize = this.workspace_.getCanvas().getBBox();
  var width;
  if (this.block_.RTL) {
    width = -workspaceSize.x;
  } else {
    width = workspaceSize.width + workspaceSize.x;
  }
  var height = workspaceSize.height + doubleBorderWidth * 3;
  var flyout = this.workspace_.getFlyout();
  if (flyout) {
    var flyoutMetrics = flyout.getMetrics_();
    height = Math.max(height, flyoutMetrics.contentHeight + 20);
  }
  width += doubleBorderWidth * 3;
  // Only resize if the size difference is significant.  Eliminates shuddering.
  if (Math.abs(this.workspaceWidth_ - width) > doubleBorderWidth ||
      Math.abs(this.workspaceHeight_ - height) > doubleBorderWidth) {
    // Record some layout information for getFlyoutMetrics_.
    this.workspaceWidth_ = width;
    this.workspaceHeight_ = height;
    // Resize the bubble.
    this.bubble_.setBubbleSize(
        width + doubleBorderWidth, height + doubleBorderWidth);
    this.svgDialog_.setAttribute('width', this.workspaceWidth_);
    this.svgDialog_.setAttribute('height', this.workspaceHeight_);
  }

  if (this.block_.RTL) {
    // Scroll the workspace to always left-align.
    var translation = 'translate(' + this.workspaceWidth_ + ',0)';
    this.workspace_.getCanvas().setAttribute('transform', translation);
  }
  this.workspace_.resize();
};

/**
 * A method handler for when the bubble is moved.
 * @private
 */
Blockly.Mutator.prototype.onBubbleMove_ = function() {
  if (this.workspace_) {
    this.workspace_.recordDeleteAreas();
  }
};

/**
 * Show or hide the mutator bubble.
 * @param {boolean} visible True if the bubble should be visible.
 */
Blockly.Mutator.prototype.setVisible = function(visible) {
  if (visible == this.isVisible()) {
    // No change.
    return;
  }
  Blockly.Events.fire(
      new Blockly.Events.Ui(this.block_, 'mutatorOpen', !visible, visible));
  if (visible) {
    // Create the bubble.
    this.bubble_ = new Blockly.Bubble(
        /** @type {!Blockly.WorkspaceSvg} */ (this.block_.workspace),
        this.createEditor_(), this.block_.pathObject.svgPath,
        /** @type {!Blockly.utils.Coordinate} */ (this.iconXY_), null, null);
    // Expose this mutator's block's ID on its top-level SVG group.
    this.bubble_.setSvgId(this.block_.id);
    this.bubble_.registerMoveEvent(this.onBubbleMove_.bind(this));
    var tree = this.workspace_.options.languageTree;
    var flyout = this.workspace_.getFlyout();
    if (tree) {
      flyout.init(this.workspace_);
      flyout.show(tree);
    }

    this.rootBlock_ = this.block_.decompose(this.workspace_);
    var blocks = this.rootBlock_.getDescendants(false);
    for (var i = 0, child; (child = blocks[i]); i++) {
      child.render();
    }
    // The root block should not be draggable or deletable.
    this.rootBlock_.setMovable(false);
    this.rootBlock_.setDeletable(false);
    if (flyout) {
      var margin = flyout.CORNER_RADIUS * 2;
      var x = flyout.getWidth() + margin;
    } else {
      var margin = 16;
      var x = margin;
    }
    if (this.block_.RTL) {
      x = -x;
    }
    this.rootBlock_.moveBy(x, margin);
    // Save the initial connections, then listen for further changes.
    if (this.block_.saveConnections) {
      var thisMutator = this;
      var mutatorBlock =
        /** @type {{saveConnections: function(!Blockly.Block)}} */ (
          this.block_);
      mutatorBlock.saveConnections(this.rootBlock_);
      this.sourceListener_ = function() {
        mutatorBlock.saveConnections(thisMutator.rootBlock_);
      };
      this.block_.workspace.addChangeListener(this.sourceListener_);
    }
    this.resizeBubble_();
    // When the mutator's workspace changes, update the source block.
    this.workspace_.addChangeListener(this.workspaceChanged_.bind(this));
    this.applyColour();
  } else {
    // Dispose of the bubble.
    this.svgDialog_ = null;
    this.workspace_.dispose();
    this.workspace_ = null;
    this.rootBlock_ = null;
    this.bubble_.dispose();
    this.bubble_ = null;
    this.workspaceWidth_ = 0;
    this.workspaceHeight_ = 0;
    if (this.sourceListener_) {
      this.block_.workspace.removeChangeListener(this.sourceListener_);
      this.sourceListener_ = null;
    }
  }
};

/**
 * Update the source block when the mutator's blocks are changed.
 * Bump down any block that's too high.
 * Fired whenever a change is made to the mutator's workspace.
 * @param {!Blockly.Events.Abstract} e Custom data for event.
 * @private
 */
Blockly.Mutator.prototype.workspaceChanged_ = function(e) {
  if (e.type == Blockly.Events.UI ||
      (e.type == Blockly.Events.CHANGE && e.element == 'disabled')) {
    return;
  }

  if (!this.workspace_.isDragging()) {
    var blocks = this.workspace_.getTopBlocks(false);
    var MARGIN = 20;
    for (var b = 0, block; (block = blocks[b]); b++) {
      var blockXY = block.getRelativeToSurfaceXY();
      var blockHW = block.getHeightWidth();
      if (blockXY.y + blockHW.height < MARGIN) {
        // Bump any block that's above the top back inside.
        block.moveBy(0, MARGIN - blockHW.height - blockXY.y);
      }
    }
  }

  // When the mutator's workspace changes, update the source block.
  if (this.rootBlock_.workspace == this.workspace_) {
    Blockly.Events.setGroup(true);
    var block = this.block_;
    var oldMutationDom = block.mutationToDom();
    var oldMutation = oldMutationDom && Blockly.Xml.domToText(oldMutationDom);
    // Allow the source block to rebuild itself.
    block.compose(this.rootBlock_);
    block.initSvg();
    block.render();

    if ((/** @type {!Blockly.WorkspaceSvg} */ (Blockly.getMainWorkspace()))
        .keyboardAccessibilityMode) {
      Blockly.navigation.moveCursorOnBlockMutation(block);
    }
    var newMutationDom = block.mutationToDom();
    var newMutation = newMutationDom && Blockly.Xml.domToText(newMutationDom);
    if (oldMutation != newMutation) {
      Blockly.Events.fire(new Blockly.Events.BlockChange(
          block, 'mutation', null, oldMutation, newMutation));
    }

    // Don't update the bubble until the drag has ended, to avoid moving blocks
    // under the cursor.
    if (!this.workspace_.isDragging()) {
      this.resizeBubble_();
    }
    Blockly.Events.setGroup(false);
  }
};

/**
 * Return an object with all the metrics required to size scrollbars for the
 * mutator flyout.  The following properties are computed:
 * .viewHeight: Height of the visible rectangle,
 * .viewWidth: Width of the visible rectangle,
 * .absoluteTop: Top-edge of view.
 * .absoluteLeft: Left-edge of view.
 * @return {!Blockly.utils.Metrics} Contains size and position metrics of
 *     mutator dialog's workspace.
 * @private
 */
Blockly.Mutator.prototype.getFlyoutMetrics_ = function() {
  // The mutator workspace only uses a subset of Blockly.utils.Metrics
  // properties as features such as scroll and zoom are unsupported.
  var unsupported = 0;
  return {
    contentHeight: unsupported,
    contentWidth: unsupported,
    contentTop: unsupported,
    contentLeft: unsupported,

    viewHeight: this.workspaceHeight_,
    viewWidth: this.workspaceWidth_ - this.workspace_.getFlyout().getWidth(),
    viewTop: unsupported,
    viewLeft: unsupported,

    absoluteTop: unsupported,
    absoluteLeft: this.workspace_.RTL ? 0 :
        this.workspace_.getFlyout().getWidth()
  };
};

/**
 * Dispose of this mutator.
 */
Blockly.Mutator.prototype.dispose = function() {
  this.block_.mutator = null;
  Blockly.Icon.prototype.dispose.call(this);
};

/**
 * Update the styles on all blocks in the mutator.
 * @public
 */
Blockly.Mutator.prototype.updateBlockStyle = function() {
  var ws = this.workspace_;

  if (ws && ws.getAllBlocks(false)) {
    var workspaceBlocks = ws.getAllBlocks(false);
    for (var i = 0; i < workspaceBlocks.length; i++) {
      var block = workspaceBlocks[i];
      block.setStyle(block.getStyleName());
    }

    var flyoutBlocks = ws.getFlyout().workspace_.getAllBlocks(false);
    for (var i = 0; i < flyoutBlocks.length; i++) {
      var block = flyoutBlocks[i];
      block.setStyle(block.getStyleName());
    }
  }
};

/**
 * Reconnect an block to a mutated input.
 * @param {Blockly.Connection} connectionChild Connection on child block.
 * @param {!Blockly.Block} block Parent block.
 * @param {string} inputName Name of input on parent block.
 * @return {boolean} True iff a reconnection was made, false otherwise.
 */
Blockly.Mutator.reconnect = function(connectionChild, block, inputName) {
  if (!connectionChild || !connectionChild.getSourceBlock().workspace) {
    return false;  // No connection or block has been deleted.
  }
  var connectionParent = block.getInput(inputName).connection;
  var currentParent = connectionChild.targetBlock();
  if ((!currentParent || currentParent == block) &&
      connectionParent.targetConnection != connectionChild) {
    if (connectionParent.isConnected()) {
      // There's already something connected here.  Get rid of it.
      connectionParent.disconnect();
    }
    connectionParent.connect(connectionChild);
    return true;
  }
  return false;
};

/**
 * Get the parent workspace of a workspace that is inside a mutator, taking into
 * account whether it is a flyout.
 * @param {Blockly.Workspace} workspace The workspace that is inside a mutator.
 * @return {Blockly.Workspace} The mutator's parent workspace or null.
 * @public
 */
Blockly.Mutator.findParentWs = function(workspace) {
  var outerWs = null;
  if (workspace && workspace.options) {
    var parent = workspace.options.parentWorkspace;
    // If we were in a flyout in a mutator, need to go up two levels to find
    // the actual parent.
    if (workspace.isFlyout) {
      if (parent && parent.options) {
        outerWs = parent.options.parentWorkspace;
      }
    } else if (parent) {
      outerWs = parent;
    }
  }
  return outerWs;
};
