# oakcpp

## dependencies
```shell
sudo yum group install "Development Tools"
sudo yum install jni-dev scl-utils devtoolset-9
pip3 install cmake -U
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
