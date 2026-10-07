# Changelog

All notable changes to this project will be documented in this file.

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
* Added an automated test suite forchecking of a set of example scripts.

### Changed 

* All example scripts have been migrated to the new language version.
* The `Value` class now stores complex builtin types directly instead of storing pointers. For example, it now stores `Mesh` instead of `Mesh*`.
* Builtin functions now use the new utility functions for argument extraction, validation, and value type conversion.

## [0.1.0] - 2026-06-30

### Added

* Initial release using Semantic Versioning.
* Existing functionality developed prior to versioning.