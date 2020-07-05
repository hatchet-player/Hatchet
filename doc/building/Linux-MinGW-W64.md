# Linux MinGW-w64 Cross Build
this file contains instructions for cross compiling Hatchet
for windows using MinGW64-w64.

---

## Setup Build OS
before following these instructions to set up a MinGW cross
toolchain, you must follow the instructions for setting up
your Linux Build OS. Please refer to the build recipe
in this directory that corresponds to your Installed OS.

---

## Install MinGW
the first requirement is installing the GCC MinGW-W64 compiler. The MinGW compiler is required to cross compile

### Ubuntu/debian
```
apt install gcc-mingw-w64-x86-64
apt install g++-mingw-w64-x86-64
apt intsall gobjc-mingw-w64-x86-64
apt intsall gobjc++-mingw-w64-x86-64
```

### Arch
```

```

### Fedora
```

```

---

# Install Boost
Boost is a C++ library required by Hatchet. To build, first grab the source
tarball & unpack.

```
wget  https://dl.bintray.com/boostorg/release/1.73.0/source/boost_1_73_0.tar.gz
tar -xf boost_1_73_0.tar.gz
cd boost_1_73_0
```

For boost to compile correctly for the toolchain, it requires a couple of patches.
install them by running the following:

```
# https://svn.boost.org/trac/boost/ticket/7262
patch -p1 -d libs/context -i "${srcdir}"/context-cross.patch

# bypass libbacktrace detection
patch -p1 -d libs/stacktrace -i "${srcdir}"/stacktrace-cross.patch

# https://github.com/boostorg/context/issues/136
curl -L https://github.com/boostorg/context/commit/85783e8cbba03804e13b3d314112df6b089ed2c0.patch | patch -p1 -R -d libs/context
```


next, configure boost for cross compilation
```
cat > user-config.jam << EOF
using gcc :
    mingw64 :
    x86_64-w64-mingw32-g++ :
    <rc>x86_64-w64-mingw32-windres
    <archiver>x86_64-w64-mingw32-ar ;
EOF

./bootstrap.sh --with-toolset=gcc
```

```
./b2 -d2 \
  target-os=windows \
  variant=release \
  threading=multi \
  threadapi=win32 \
  link=shared,static \
  runtime-link=shared \
  --prefix=/usr/x86_64-w64-mingw32 \
  --user-config=user-config.jam \
  --without-python --without-mpi --without-graph_parallel \
  cxxflags="-std=c++14 -D_FORTIFY_SOURCE=2 -O2 -pipe -fno-plt -fexceptions  --param=ssp-buffer-size=4" \
  linkflags="-Wl,-O1,--sort-common,--as-needed -fstack-protector" \
  address-model=64 \
  architecture=x86 \
  binary-format=pe \
  --layout=system stage
```








