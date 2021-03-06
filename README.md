# quantumVerb

[![Build status](https://ci.appveyor.com/api/projects/status/79vsij3o2i341rde/branch/master?svg=true)](https://ci.appveyor.com/project/segwin/quantumverb/branch/master)

A free and open-source convolution reverb plugin developed for [Quantum Music](http://www.quantum-music.ca/) (and the rest of the world) by
4th-year engineering students at [Polytechnique Montréal](http://www.polymtl.ca/en).

## Installing the plugin (tl;dr version)

1. Download plugin [here](https://github.com/QVbDev/quantumVerb/releases)
2. Install to a directory your DAW recognises (see [here](https://github.com/QVbDev/quantumVerb/wiki/Plugin-installation-guide-for-Reaper) for instructions with Reaper)


## Working with the plugin (developer's version)

## Getting the code

1. Clone repository
2. Run from git bash in the repo: `git submodule update --init --recursive` (ensures submodules are initialised)
3. Open Builds\VisualStudio2017\quantumVERB.sln (Visual Studio 2017)

## Working with the project

* Plugin classes and methods are located under the quantumVERB_SharedCode project
  * To run plugin in standalone config: build and execute quantumVERB_StandalonePlugin project
  * To build plugin in VST3 format: build and execute quantumVERB_VST3 project
* Unit tests are located under the Tests project
  * To run unit tests: build and execute Tests project


## Useful links

* [Class documentation](https://qvbdev.github.io/quantumVerb/docs/)
* [Contribution guidelines](CONTRIBUTING.md)
* [Known issues](https://github.com/QVbDev/quantumVerb/wiki/Known-bugs-&-limitations)
