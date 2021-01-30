'use strict';

/**
 * Create a namespace for the application.
 */
var Code = {};

/**
 * Lookup for names of supported languages.	Keys should be in ISO 639 format.
 */
Code.LANGUAGE_NAME = {
	'en': 'English',
	'ja': '日本語',
	'zh-hans': '简体中文',
};

/**
 * Blockly's main workspace.
 * @type {Blockly.WorkspaceSvg}
 */
Code.workspace = null;

/**
 * Extracts a parameter from the URL.
 * If the parameter is absent default_value is returned.
 * @param {string} name The name of the parameter.
 * @param {string} defaultValue Value to return if parameter not found.
 * @return {string} The parameter value or the default value if not found.
 */
Code.getStringParamFromUrl = function(name, defaultValue) {
	var val = location.search.match(new RegExp('[?&]' + name + '=([^&]+)'));
	return val ? decodeURIComponent(val[1].replace(/\+/g, '%20')) : defaultValue;
};

/**
 * Get the language of this user from the URL.
 * @return {string} User's language.
 */
Code.getLang = function() {
	var lang = Code.getStringParamFromUrl('lang', '');
	if (Code.LANGUAGE_NAME[lang] === undefined) {
		// Default to English.
		lang = 'en';
	}
	return lang;
};

/**
 * Load blocks saved on App Engine Storage or in session/local storage.
 * @param {string} defaultXml Text representation of default blocks.
 */
Code.loadBlocks = function(defaultXml) {
	try {
		var loadOnce = window.sessionStorage.loadOnceBlocks;
	} catch(e) {
		// Firefox sometimes throws a SecurityError when accessing sessionStorage.
		// Restarting Firefox fixes this, so it looks like a bug.
		var loadOnce = null;
	}
	if ('BlocklyStorage' in window && window.location.hash.length > 1) {
		// An href with #key trigers an AJAX call to retrieve saved blocks.
		BlocklyStorage.retrieveXml(window.location.hash.substring(1));
	} else if (loadOnce) {
		// Language switching stores the blocks during the reload.
		delete window.sessionStorage.loadOnceBlocks;
		var xml = Blockly.Xml.textToDom(loadOnce);
		Blockly.Xml.domToWorkspace(xml, Code.workspace);
	} else if (defaultXml) {
		// Load the editor with default starting blocks.
		var xml = Blockly.Xml.textToDom(defaultXml);
		Blockly.Xml.domToWorkspace(xml, Code.workspace);
	} else if ('BlocklyStorage' in window) {
		// Restore saved blocks in a separate thread so that subsequent
		// initialization is not affected from a failed load.
		window.setTimeout(BlocklyStorage.restoreBlocks, 0);
	}
};

/**
 * Save the blocks and reload with a different language.
 */
Code.changeLanguage = function() {
	// Store the blocks for the duration of the reload.
	// MSIE 11 does not support sessionStorage on file:// URLs.
	if (window.sessionStorage) {
		var xml = Blockly.Xml.workspaceToDom(Code.workspace);
		var text = Blockly.Xml.domToText(xml);
		window.sessionStorage.loadOnceBlocks = text;
	}

	var search = window.location.search;
	if (search.length <= 1) {
		search = '?lang=' + newLang;
	} else if (search.match(/[?&]lang=[^&]*/)) {
		search = search.replace(/([?&]lang=)[^&]*/, '$1' + newLang);
	} else {
		search = search.replace(/\?/, '?lang=' + newLang + '&');
	}

	window.location = window.location.protocol + '//' +
			window.location.host + window.location.pathname + search;
};

/**
 * Bind a function to a button's click event.
 * On touch enabled browsers, ontouchend is treated as equivalent to onclick.
 * @param {!Element|string} el Button element or ID thereof.
 * @param {!Function} func Event handler to bind.
 */
Code.bindClick = function(el, func) {
	if (typeof el == 'string') {
		el = document.getElementById(el);
	}
	el.addEventListener('click', func, true);
	el.addEventListener('touchend', func, true);
};

/**
 * Compute the absolute coordinates and dimensions of an HTML element.
 * @param {!Element} element Element to match.
 * @return {!Object} Contains height, width, x, and y properties.
 * @private
 */
Code.getBBox_ = function(element) {
	var height = element.offsetHeight;
	var width = element.offsetWidth;
	var x = 0;
	var y = 0;
	do {
		x += element.offsetLeft;
		y += element.offsetTop;
		element = element.offsetParent;
	} while (element);
	return {
		height: height,
		width: width,
		x: x,
		y: y
	};
};

/**
 * User's language (e.g. "en").
 * @type {string}
 */
Code.LANG = Code.getLang();

/**
 * List of tab names.
 * @private
 */
Code.TABS_ = ['blocks', 'python'];

Code.selected = 'blocks';

/**
 * Switch the visible pane when a tab is clicked.
 * @param {string} clickedName Name of tab clicked.
 */

Code.tabClick = function(clickedName) {
	// If the XML tab was open, save and render the content.
	if (document.getElementById('tab_blocks').className == 'tabon') {
		Code.workspace.setVisible(false);
	}
	// Deselect all tabs and hide all panes.
	for (var i = 0; i < Code.TABS_.length; i++) {
		var name = Code.TABS_[i];
		document.getElementById('tab_' + name).className = 'taboff';
		document.getElementById('content_' + name).style.visibility = 'hidden';
	}

	// Select the active tab.
	Code.selected = clickedName;
	document.getElementById('tab_' + clickedName).className = 'tabon';
	// Show the selected pane.
	document.getElementById('content_' + clickedName).style.visibility =
			'visible';
	Code.renderContent();
	if (clickedName == 'blocks') {
		Code.workspace.setVisible(true);
	}
	Blockly.svgResize(Code.workspace);
};
/**
 * Populate the currently selected pane with content generated from the blocks.
 */
Code.renderContent = function() {
	var content = document.getElementById('content_' + Code.selected);
	// Initialize the pane.
	if (content.id == 'content_python') {
		Code.attemptCodeGeneration(Blockly.Python);
	}
	if (typeof PR == 'object') {
		PR.prettyPrint();
	}
};

/**
 * Attempt to generate the code and display it in the UI, pretty printed.
 * @param generator {!Blockly.Generator} The generator to use.
 */
Code.attemptCodeGeneration = function(generator) {
	var content = document.getElementById('content_' + Code.selected);
	content.textContent = '';
	if (Code.checkAllGeneratorFunctionsDefined(generator)) {
		var code = qvs.code();
		content.textContent = code;
		// Remove the 'prettyprinted' class, so that Prettify will recalculate.
		content.className = content.className.replace('prettyprinted', '');
	}
};

/**
 * Check whether all blocks in use have generator functions.
 * @param generator {!Blockly.Generator} The generator to use.
 */
Code.checkAllGeneratorFunctionsDefined = function(generator) {
	var blocks = Code.workspace.getAllBlocks(false);
	var missingBlockGenerators = [];
	for (var i = 0; i < blocks.length; i++) {
		var blockType = blocks[i].type;
		if (!generator[blockType]) {
			if (missingBlockGenerators.indexOf(blockType) == -1) {
				missingBlockGenerators.push(blockType);
			}
		}
	}

	var valid = missingBlockGenerators.length == 0;
	if (!valid) {
		var msg = 'The generator code for the following blocks not specified for ' +
				generator.name_ + ':\n - ' + missingBlockGenerators.join('\n - ');
		Blockly.alert(msg);	// Assuming synchronous. No callback.
	}
	return valid;
};

/**
 * Initialize Blockly.	Called on page load.
 */
Code.init = function() {
	Code.initLanguage();

	var container = document.getElementById('content_area');
	var onresize = function(e) {
		var bBox = Code.getBBox_(container);
		for (var i = 0; i < Code.TABS_.length; i++) {
			var el = document.getElementById('content_' + Code.TABS_[i]);
			el.style.top = bBox.y + 'px';
			el.style.left = bBox.x + 'px';
			// Height and width need to be set, read back, then set again to
			// compensate for scrollbars.
			el.style.height = bBox.height + 'px';
			el.style.height = (2 * bBox.height - el.offsetHeight) + 'px';
			el.style.width = bBox.width + 'px';
			el.style.width = (2 * bBox.width - el.offsetWidth) + 'px';
		}
		// Make the 'Blocks' tab line up with the toolbox.
		if (Code.workspace && Code.workspace.toolbox_.width) {
			document.getElementById('tab_blocks').style.minWidth =
					(Code.workspace.toolbox_.width - 38) + 'px';
					// Account for the 19 pixel margin and on each side.
		}
	};
	window.addEventListener('resize', onresize, false);

	// The toolbox XML specifies each category name using Blockly's messaging
	// format (eg. `<category name="%{BKY_CATLOGIC}">`).
	// These message keys need to be defined in `Blockly.Msg` in order to
	// be decoded by the library. Therefore, we'll use the `MSG` dictionary that's
	// been defined for each language to import each category name message
	// into `Blockly.Msg`.
	// TODO: Clean up the message files so this is done explicitly instead of
	// through this for-loop.
	for (var messageKey in MSG) {
		if (messageKey.indexOf('cat') == 0) {
			Blockly.Msg[messageKey.toUpperCase()] = MSG[messageKey];
		}
	}

	// Construct the toolbox XML, replacing translated variable names.
	var toolboxText = document.getElementById('toolbox').outerHTML;
	toolboxText = toolboxText.replace(/(^|[^%]){(\w+)}/g,
			function(m, p1, p2) {return p1 + MSG[p2];});
	var toolboxXml = Blockly.Xml.textToDom(toolboxText);

	Code.workspace = Blockly.inject('content_blocks',
			{grid:
					{spacing: 25,
					 length: 3,
					 colour: '#ccc',
					 snap: true},
			 media: '../media/',
			 toolbox: toolboxXml,
			 zoom:
					 {controls: true,
						wheel: true}
			});

	Code.workspace.addChangeListener((e) => {
		if (Blockly.selected && Blockly.selected.type == 'open' && !Blockly.selected.disabled) {
			selectedBlock.enabled;
		}
		if (e.element != null) {
			if (e.element == 'field' || e.element == 'dragStop') {
				qvs.updateCode();
			}
			if (qvs.enabled) {
				qvs.debug(qvs.format("Changed event {0} triggered."), e.element);
			}
		}
	});

	// Add to reserved word list: Local variables in execution environment (runJS)
	// and the infinite loop detection function.
	Blockly.JavaScript.addReservedWords('code,timeouts,checkTimeout');

	Code.loadBlocks('');

	if ('BlocklyStorage' in window) {
		// Hook a save function onto unload.
		BlocklyStorage.backupOnUnload(Code.workspace);
	}

	Code.tabClick(Code.selected);

	for (var i = 0; i < Code.TABS_.length; i++) {
		var name = Code.TABS_[i];
		Code.bindClick('tab_' + name,
				function(name_) {return function() {Code.tabClick(name_);};}(name));
	}
	onresize();
	Blockly.svgResize(Code.workspace);

	// Lazy-load the syntax-highlighting.
	window.setTimeout(Code.importPrettify, 1);

	// Add custom variables
	Blockly.getMainWorkspace().createVariable("src", "", Blockly.utils.genUid());
};

/**
 * Initialize the page language.
 */
Code.initLanguage = function() {

	document.head.parentElement.setAttribute('lang', Code.LANG);
	document.getElementById('tab_blocks').textContent = MSG['blocks'];
	/*
	var categories = [];
	for (var i = 0, cat; cat = categories[i]; i++) {
		document.getElementById(cat).setAttribute('name', Blockly.Msg[cat]);
	}
	*/
};


// Load the VapourSynth Script Code language strings.
document.write('<script src="msg/' + Code.LANG + '.js"></script>\n');
// Load Blockly's language strings.
// document.write('<script src="../msg/messages.js"></script>\n');
document.write('<script src="../msg/js/' + Code.LANG + '.js"></script>\n');
// Load the VapourSynth Script Code block scripts.
document.write('<script src="blocks/__init__.js"></script>');
// Load the VapourSynth Script Code other scripts.
document.write('<script src="vs/expr.js"></script>');
document.write('<script src="vs/format.js"></script>');

window.addEventListener('load', Code.init);
