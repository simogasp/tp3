# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Changed
- [ci] update to vcpkg 2023.11.20
- [doc] update README.md with warnings and notes

## [2023.1.0] - 2023-05-16

### Added
- warning flags for gcc, clang and msvc
- use of studentipy tags in the code
- script to make release with studentipy
- CI on GitHub for linux, windows and osx
- clang format file
- added IPO support
- teapot sample (not give to the students)
- cmake option to build the code with warnings as errors

### Changed
- modernize and refactoring cmake
- switched to c++17

### Fixed
- all warnings on linux and windows

### Removed
- appveyor ci support

## [2021.0.0] - 2021-05-05

### Changed
- everything to float
- [cmake] using targets for glut

## [2020.1.0] - 2020-05-05

First release on GitHub

### Added
- cross-platform support
- freeglut for windows
- appveyor ci support


