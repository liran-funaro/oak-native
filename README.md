# oakcpp

## dependencies
```shell
sudo yum group install "Development Tools"
sudo yum install jni-dev scl-utils devtoolset-9
pip3 install cmake -U
```

### folly
clone:
```shell
git clone git@github.com:facebook/folly.git
```

Follow the compilation instruction with one difference. Use:
```shell
./build.sh --extra-cmake-defines '{"BUILD_SHARED_LIBS": "ON", "FOLLY_SUPPORT_SHARED_LIBRARY": "ON", "CMAKE_POSITION_INDEPENDENT_CODE": "ON", "BUILD_TESTS": "OFF"}'
```

Change the include/libs folder to the build output folder.

## configure

```shell
rm -rf cmake-build-release
mkdir -p cmake-build-release
cd cmake-build-release
scl enable devtoolset-9 cmake -DCMAKE_BUILD_TYPE=Release ..
```

## compile

```shell
cmake --build .
```

## development install

```bash
sudo ln -s $(pwd)/cmake-build-release/liboakcpp.so  /usr/local/lib/liboakcpp.so 
```
