FROM gcc:7.3.0
ADD . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN apt-get update && apt-get -y install cmake
RUN cd /usr/src/myapp && \
    git submodule init && \
    git submodule update

CMD ["/bin/bash"]
