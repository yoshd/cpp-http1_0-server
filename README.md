# cpp-http1_0-server

C++で雑にHTTP1.0サーバーを実装する

# Development environment

```
$ docker build . -t mygcc
$ docker run --rm -it -p 8080:8080 -v $(pwd):/usr/src/myapp mygcc /bin/bash
```

# Get gtest

```
$ git submodule init
$ git submodule update
```

# Test execution

```
$ cd make
$ make check
```

# Start server

```
$ make start-server
```
