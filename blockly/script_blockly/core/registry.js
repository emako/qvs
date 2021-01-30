/**
 * @license
 * Copyright 2020 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @fileoverview This file is a universal registry that provides generic methods
 *    for registering and unregistering different types of classes.
 * @author aschmiedt@google.com (Abby Schmiedt)
 */
'use strict';

goog.provide('Blockly.registry');

goog.requireType('Blockly.blockRendering.Renderer');
goog.requireType('Blockly.Field');
goog.requireType('Blockly.IToolbox');
goog.requireType('Blockly.Theme');
goog.requireType('Blockly.utils.toolbox');


/**
 * A map of maps. With the keys being the type and name of the class we are
 * registering and the value being the constructor function.
 * e.g. {'field': {'field_angle': Blockly.FieldAngle}}
 *
 * @type {Object<string, Object<string, function(new:?)>>}
 */
Blockly.registry.typeMap_ = {};

/**
 * The string used to register the default class for a type of plugin.
 * @type {string}
 */
Blockly.registry.DEFAULT = 'default';

/**
 * A name with the type of the element stored in the generic.
 * @param {string} name The name of the registry type.
 * @constructor
 * @template T
 */
Blockly.registry.Type = function(name) {
  /**
   * @type {string}
   * @private
   */
  this.name_ = name;
};

/**
 * Returns the name of the type.
 * @return {string} The name.
 * @override
 */
Blockly.registry.Type.prototype.toString = function() {
  return this.name_;
};

/** @type {!Blockly.registry.Type<Blockly.blockRendering.Renderer>} */
Blockly.registry.Type.RENDERER = new Blockly.registry.Type('renderer');

/** @type {!Blockly.registry.Type<Blockly.Field>} */
Blockly.registry.Type.FIELD = new Blockly.registry.Type('field');

/** @type {!Blockly.registry.Type<Blockly.IToolbox>} */
Blockly.registry.Type.TOOLBOX = new Blockly.registry.Type('toolbox');

/** @type {!Blockly.registry.Type<Blockly.Theme>} */
Blockly.registry.Type.THEME = new Blockly.registry.Type('theme');

/**
 * Registers a class based on a type and name.
 * @param {string|Blockly.registry.Type<T>} type The type of the plugin.
 *     (e.g. Field, Renderer)
 * @param {string} name The plugin's name. (Ex. field_angle, geras)
 * @param {?function(new:T, ...?)|Object} registryItem The class or object to
 *     register.
 * @throws {Error} if the type or name is empty, a name with the given type has
 *     already been registered, or if the given class or object is not valid for it's type.
 * @template T
 */
Blockly.registry.register = function(type, name, registryItem) {
  if ((!(type instanceof Blockly.registry.Type) && typeof type != 'string') || String(type).trim() == '') {
    throw Error('Invalid type "' + type + '". The type must be a' +
      ' non-empty string or a Blockly.registry.Type.');
  }
  type = String(type).toLowerCase();

  if ((typeof name != 'string') || (name.trim() == '')) {
    throw Error('Invalid name "' + name + '". The name must be a' +
      ' non-empty string.');
  }
  name = name.toLowerCase();
  if (!registryItem) {
    throw Error('Can not register a null value');
  }
  var typeRegistry = Blockly.registry.typeMap_[type];
  // If the type registry has not been created, create it.
  if (!typeRegistry) {
    typeRegistry = Blockly.registry.typeMap_[type] = {};
  }

  // Validate that the given class has all the required properties.
  Blockly.registry.validate_(type, registryItem);

  // If the name already exists throw an error.
  if (typeRegistry[name]) {
    throw Error('Name "' + name + '" with type "' + type + '" already registered.');
  }
  typeRegistry[name] = registryItem;
};

/**
 * Checks the given registry item for properties that are required based on the
 * type.
 * @param {string} type The type of the plugin. (e.g. Field, Renderer)
 * @param {Function|Object} registryItem A class or object that we are checking
 *     for the required properties.
 * @private
 */
Blockly.registry.validate_ = function(type, registryItem) {
  switch (type) {
    case String(Blockly.registry.Type.FIELD):
      if (typeof registryItem.fromJson != 'function') {
        throw Error('Type "' + type + '" must have a fromJson function');
      }
      break;
  }
};

/**
 * Unregisters the registry item with the given type and name.
 * @param {string|Blockly.registry.Type<T>} type The type of the plugin.
 *     (e.g. Field, Renderer)
 * @param {string} name The plugin's name. (Ex. field_angle, geras)
 * @template T
 */
Blockly.registry.unregister = function(type, name) {
  type = String(type).toLowerCase();
  name = name.toLowerCase();
  var typeRegistry = Blockly.registry.typeMap_[type];
  if (!typeRegistry) {
    console.warn('No type "' + type + '" found');
    return;
  }
  if (!typeRegistry[name]) {
    console.warn('No name "' + name + '" with type "' + type + '" found');
    return;
  }
  delete Blockly.registry.typeMap_[type][name];
};

/**
 * Gets the registry item for the given name and type. This can be either a
 * class or an object.l
 * @param {string|Blockly.registry.Type<T>} type The type of the plugin.
 *     (e.g. Field, Renderer)
 * @param {string} name The plugin's name. (Ex. field_angle, geras)
 * @return {?function(new:T, ...?)|Object} The class or object with the given
 *     name and type or null if none exists.
 * @template T
 */
Blockly.registry.getItem_ = function(type, name) {
  type = String(type).toLowerCase();
  name = name.toLowerCase();
  var typeRegistry = Blockly.registry.typeMap_[type];
  if (!typeRegistry) {
    console.warn('No type "' + type + '" found');
    return null;
  }
  if (!typeRegistry[name]) {
    console.warn('No name "' + name + '" with type "' + type + '" found');
    return null;
  }
  return typeRegistry[name];
};

/**
 * Gets the class for the given name and type.
 * @param {string|Blockly.registry.Type<T>} type The type of the plugin.
 *     (e.g. Field, Renderer)
 * @param {string} name The plugin's name. (Ex. field_angle, geras)
 * @return {?function(new:T, ...?)} The class with the given name and type or
 *     null if none exists.
 * @template T
 */
Blockly.registry.getClass = function(type, name) {
  return /** @type {?function(new:T, ...?)} */ (Blockly.registry.getItem_(type, name));
};

/**
 * Gets the object for the given name and type.
 * @param {string|Blockly.registry.Type<T>} type The type of the plugin.
 *     (e.g. Category)
 * @param {string} name The plugin's name. (Ex. logic_category)
 * @returns {T} The object with the given name and type or null if none exists.
 * @template T
 */
Blockly.registry.getObject = function(type, name) {
  return /** @type {T} */ (Blockly.registry.getItem_(type, name));
};

/**
 * Gets the class from Blockly options for the given type.
 * This is used for plugins that override a built in feature. (e.g. Toolbox)
 * @param {Blockly.registry.Type<T>} type The type of the plugin.
 * @param {!Blockly.Options} options The option object to check for the given
 *     plugin.
 * @return {?function(new:T, ...?)} The class for the plugin.
 * @template T
 */
Blockly.registry.getClassFromOptions = function(type, options) {
  var typeName = type.toString();
  var plugin = options.plugins[typeName] || Blockly.registry.DEFAULT;

  // If the user passed in a plugin class instead of a registered plugin name.
  if (typeof plugin == 'function') {
    return plugin;
  }
  return Blockly.registry.getClass(type, plugin);
};
