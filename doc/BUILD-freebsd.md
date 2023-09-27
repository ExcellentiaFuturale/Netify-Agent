# FreeBSD Build Notes

1. Clone source (recursive) via HTTP/S:
```sh
git clone --recursive https://gitlab.com/netify.ai/public/netify-agent.git
```

2. [ALTERNATIVE] Clone source (recursive) via SSH:

```sh
git clone --recursive git@gitlab.com:netify.ai/public/netify-agent.git
```

## FreeBSD 10/11:

### Manual Builds

1. Install required build packages:
```sh
pkg add http://pkg.freebsd.org/freebsd:11:x86:64/release_2/All/json-c-0.13.txz
pkg install auto-tools git gmake pkgconf google-perftools
```
2. Configure source:

```sh
cd netify-agent
./autogen.sh && ./configure --disable-conntrack --disable-inotify CC=clang CXX=clang++ MAKE=gmake
```
To build a debug version with AddressSanitizer:
```sh
./autogen.sh && ./configure --disable-conntrack --disable-inotify --disable-libtcmalloc CC=clang CXX=clang++ CFLAGS='-O1 -fsanitize=address -fno-omit-frame-pointer' CXXFLAGS='-O1 -fsanitize=address -fno-omit-frame-pointer' MAKE=gmake
```
3. Build (optionally adjust jobs for number of CPUs + 1):
```sh
gmake -j 5
```

### Package (txz)

1. Follow manual build steps 1 - 3 above if not already done.

2. Build package:
```sh
gmake deploy-freebsd
```
To build a debug version with AddressSanitizer:
```sh
gmake deploy-freebsd-debug
```

## FreeBSD 13.x, 14.x+

### Manual Builds

1. Install required build packages:
```sh
pkg install autoconf automake bison curl flex git gmake gtar libltdl libpcap libtool pkgconf
```

2. Configure source:

```sh
cd netify-agent
./autogen.sh && ./configure MAKE=gmake YACC=bison --with-pic=inih --disable-libtcmalloc
```

3. Build (optionally adjust jobs for number of CPUs + 1):
```sh
# Assuming 4 CPUs...
gmake -j 5
```

### Package (pkg)

1. Follow manual build steps 1 - 2 above if not already done.

2. Create full source archive:
```sh
gmake dist-git
```

3. Create required ports directories:
```sh
mkdir -vp /usr/ports/distfiles /usr/ports/security/netify-agent
```

4. Copy source archvie:
```sh
cp netifyd-*.tar.gz /usr/ports/distfiles
```

5. Create required symbolic links:
```sh
cd /usr/ports/security/netify-agent
ln -s $HOME/netify-agent/deploy/freebsd/Makefile .
ln -s $HOME/netify-agent/deploy/freebsd/files .
ln -s $HOME/netify-agent/deploy/freebsd/pkg-descr .
ln -s $HOME/netify-agent/deploy/freebsd/pkg-plist .
ln -s $HOME/netify-agent/deploy/freebsd/distinfo .
```

6. Make package
```sh
make package
```
