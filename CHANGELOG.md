# Changelog

All notable changes to this project will be documented in this file.

## [0.3.0] - 2026-10-28

This release introduces major breaking changes to the language and runtime. 
Scripts written for previous versions will have to be migrated. 

### Breaking Changes
 
* Removed the generic `noise()` constructor function (use specific constructor functions instead, see below)  
* Removed `setNoiseType()` which was no longer needed
* Removed `setExponent()` function (use `pow()` instead, see below)
* Removed `setNoiseStyle() function (use new modifiers instead, see below)
* Functions setting FBM parameters now operate on a new fbmParameters value type instead of on a noise 
* Changed default values of FBM parameters. The new defaults are: 
	* NumberOfOctaves = 1
	* Lacunarity = 1.0f
	* Persistence = 1.0f
	* StartFrequency = 1.0f
	* Normalize = false
* Fixed a bug in Perlin noise that prevented one gradient from ever being selected. As a result the output of the Perlin Noise function now differs from previous versions.

### Added 

* Added specific constructor functions for each type of noise: 
	* `perlinNoise()` for Perlin Noise 
	* `valueNoise()` for Value Noise 
	* `whiteNoise()` for White Noise
* These new constructor functions can take a seed as an optional argument
* Added functions for modifying noise to create a more flexible system
	* `abs()` replaces the old billow noise style 
	* `ridge()` replaces the old ridge noise style 
	* `pow()' replaces `setExponent`
	* `fbm()' is now a modifier instead of being built into the noise object
* Added new builtin `fbmParameters` value type.
* Added new builtin `fbmParameters()` function for creating a fbmParameters value 

### Changed 

* All example scripts have been migrated to the new language version.
* Switched to a new oop/polymorphic Noise implementation. 
* Worked on improving modularity and encapsulation of runtime.

## [0.2.0] - 2026-10-07

This release introduces major breaking changes to the language and runtime. 
Scripts written for previous versions will have to be migrated. 

### Breaking Changes 

* Builtin functions operating on noise now take a noise object as an argument instead of operating on a global noise object. 
* The builtin `resetNoise()` function has been removed.

### Added

* Added a new builtin `noise` value type.
* Added a new builtin `noise()` function for creating a noise objects.
* An output path can now be specified as an optional command-line argument.
* Added utility for extracting and validating builtin function arguments.
* Added utility functions for value type conversions.
* Added an automated test suite for checking of a set of example scripts.

### Changed 

* All example scripts have been migrated to the new language version.
* The `Value` class now stores complex builtin types directly instead of storing pointers. For example, it now stores `Mesh` instead of `Mesh*`.
* Builtin functions now use the new utility functions for argument extraction, validation, and value type conversion.

## [0.1.0] - 2026-06-30

### Added

* Initial release using Semantic Versioning.
* Existing functionality developed prior to versioning.