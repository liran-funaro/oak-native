# oak-native

## Dependencies
These are oak-native dependencies (redhat):
```shell
sudo yum groupinstall "Development Tools"
sudo yum install jni-dev scl-utils devtoolset-9
pip3 install cmake -U
```

### folly
Folly is required for oak-native.

For other OS, clone:
```shell
git clone https://github.com/facebook/folly.git
```

Install dependencies (redhat):
```shell
sudo yum install\
    gcc\
    gcc-c++\
    automake\
    boost-devel\
    libtool\
    lz4-devel\
    lzma-devel\
    snappy-devel\
    zlib-devel\
    glog-devel\
    gflags-devel\
    scons\
    double-conversion-devel\
    openssl-devel\
    libevent-devel\
    fmt-devel\
    libsodium-devel\
    python3-devel\
    libatomic
```

Then, build as follows (redhat):
```shell
scl enable devtoolset-9 sh
gcc --version
# Should output version 9
export CPLUS_INCLUDE_PATH=$(find /usr/inc -type d -name "python3*" | head -1)
echo $CPLUS_INCLUDE_PATH
./build.sh --scratch-path ../folly-build --extra-cmake-defines '{"CMAKE_POSITION_INDEPENDENT_CODE": "ON", "BUILD_TESTS": "OFF"}'
```

If build fails, before trying again, first delete:
```shell
rm -r ../folly-build/build
```

## Configure

```shell
rm -rf cmake-build-release
mkdir -p cmake-build-release
cd cmake-build-release
scl enable devtoolset-9 cmake -DCMAKE_BUILD_TYPE=Release ..
```

## Compile

```shell
cmake --build .
```

## Development install

```bash
sudo ln -s $(pwd)/cmake-build-release/liboakcpp.so  /usr/local/lib/liboakcpp.so 
```
