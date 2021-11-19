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

Install dependencies according to provided instruction in folly's readme file.
Then, build using:
```shell
export CPLUS_INCLUDE_PATH=/usr/include/python3.8
./build.sh --scratch-path ../folly-build --extra-cmake-defines '{"CMAKE_POSITION_INDEPENDENT_CODE": "ON", "BUILD_TESTS": "OFF"}'
```

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
