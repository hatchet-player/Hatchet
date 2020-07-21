# install Required programs
```
sudo pacman -S git
sudo pacman -S python
sudo pacman -S meson
sudo pacman -S cmake
sudo pacman -S pkgconf
sudo pacman -S autoconf
sudo pacman -S automake
```


# Install Compiler
```
sudo pacman -S gcc
sudo pacman -S gcc-objc
```

# Install dependencies
```
sudo pacman -S boost
sudo pacman -S gnutls
sudo pacman -S sparsehash
sudo pacman -S lucene++
sudo pacman -S vlc

sudo pacman -S qt5-base
sudo pacman -S qt5-svg
sudo pacman -S qt5-tools
sudo pacman -S qt5-webengine
sudo pacman -S qt5-webkit
sudo pacman -S qt5-x11extras
sudo pacman -S liblastfm-qt5
sudo pacman -S telepathy-qt

sudo pacman -S qca
sudo pacman -S quazip
sudo pacman -S qtkeychain
```

# Install Hatchet
```
git clone https://github.com/hatchet-player/hatchet

cd hatchet
./bootstrap.sh
cd build
sudo ninja install
```