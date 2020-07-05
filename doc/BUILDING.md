## BUILD Hatchet

you can compile Hatchet yourself

NT like :
    $ .\bootstrap.cmd

UNIX like :
    $ ./bootstrap.sh

UNIX Like -> NT like Cross Compilation:
    $ ./nt_bootstrap.sh

### Detailed Build Instructions

| Linux: | [Arch](#) **-** [Debian](#) **-** [Fedora](#) **-** [openSUSE](#) **-** [Ubuntu](#) |
|------:|:------|
| **Windows**: | [**Windows**](#) |
| **Mac**: | [**OS X**](#) |

### UNIX-like dependencies

Required dependencies:

* [Meson](https://mesonbuild.com/)
* [CMake 3](https://www.cmake.org/)
* [VLC 2.1.0](https://videolan.org/vlc/)
* [SQLite 3.6.22](https://www.sqlite.org/)
* [TagLib 1.8](https://taglib.github.io/)
* [Boost 1.3](https://www.boost.org/)
* [Lucene++ 3.0.6](https://github.com/luceneplusplus/LucenePlusPlus/)
* [Attica 5.6.0](http://ftp.kde.org/stable/attica/)
* [LibLastFM 1.0.9](https://github.com/lastfm/liblastfm/)
* [Sparsehash](https://code.google.com/p/sparsehash/)
* [GnuTLS](http://gnutls.org/)
* [Qt >= 5.4.0](http://qt-project.org/)
* [QuaZip 0.4.3](http://quazip.sourceforge.net/)
* [QtKeychain 0.1](https://github.com/frankosterfeld/qtkeychain/)
* [TelepathyQT >= 0.9.8](https://cgit.freedesktop.org/telepathy/telepathy-qt/)
* [Echonest-QT5 >= 2.3.1](https://cgit.kde.org/libechonest.git)


The following dependencies are optional (but *recommended*):
* [Jreen 1.1.1](http://qutim.org/jreen/)
* [Snorenotify 0.5.2](https://github.com/Snorenotify/Snorenotify/)


If you are using Qt>5.6 you need to build and install QtWebKit
* [QtWebKit](https://github.com/qt/qtwebkit)


the following required dependencies are built in-project:
* [Qocoa](https://github.com/mikemcquaid/Qocoa/)
* [libqxt](http://libqxt.org/) (QxtWeb module)
* [MiniUPnP 1.6](http://miniupnp.free.fr/)
* [kdSingleApplicationGuard](http://www.kdab.com/)

the following optional dependencies can be built in-project:
* [libqnetwm](https://code.google.com/p/libqnetwm/)
* [SPMediaKeyTap](https://github.com/nevyn/SPMediaKeyTap/)



###  NT-Like Dependencies

Required dependencies:
* [Meson](https://mesonbuild.com/)
* [CMake 3](https://www.cmake.org/)
* [VLC 2.1.0](https://videolan.org/vlc/)
* [MinGW](https://sourceforge.net/projects/mingw)
<!-- * [GnuWin](https://sourceforge.net/projects/gnuwin32/) -->
* [SQLite 3.6.22](https://www.sqlite.org/)
* [TagLib 1.8](https://taglib.github.io/)
* [Boost 1.3](https://www.boost.org/)
* [Lucene++ 3.0.6](https://github.com/luceneplusplus/LucenePlusPlus/)
* [Attica 5.6.0](http://ftp.kde.org/stable/attica/)
* [LibLastFM 1.0.9](https://github.com/lastfm/liblastfm/)
* [Sparsehash](https://code.google.com/p/sparsehash/)
* [GnuTLS](http://gnutls.org/)
* [Qt-Win >= 5.4.0](https://www.qt.io/download-qt-installer)
* [QuaZip 0.4.3](http://quazip.sourceforge.net/)
* [QtKeychain 0.1](https://github.com/frankosterfeld/qtkeychain/)
* [TelepathyQT >= 0.9.8](https://cgit.freedesktop.org/telepathy/telepathy-qt/)
* [Echonest-QT5 >= 2.3.1](https://cgit.kde.org/libechonest.git)


The following dependencies are optional (but *recommended*):
* [Jreen 1.1.1](http://qutim.org/jreen/)
* [Snorenotify 0.5.2](https://github.com/Snorenotify/Snorenotify/)


If you are using Qt>5.6 you need to build and install QtWebKit
* [QtWebKit](https://github.com/qt/qtwebkit)


the following required dependencies are built in-project:
* [Qocoa](https://github.com/mikemcquaid/Qocoa/)
* [libqxt](http://libqxt.org/) (QxtWeb module)
* [MiniUPnP 1.6](http://miniupnp.free.fr/)
* [kdSingleApplicationGuard](http://www.kdab.com/)

the following optional dependencies can be built in-project:
* [libqnetwm](https://code.google.com/p/libqnetwm/)
* [SPMediaKeyTap](https://github.com/nevyn/SPMediaKeyTap/)



## Cross Compilation

~~ the Hatchet project can be cross compiled from a Unix-Like
environment for NT-Like environments ~~ THIS FEAUTURE IS CURRENTLY
NOT WORKING