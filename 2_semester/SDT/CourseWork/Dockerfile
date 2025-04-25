FROM ubuntu

RUN apt-get update
RUN apt-get install g++ -y
RUN apt-get install cmake -y
RUN apt-get install clang-format -y
RUN apt-get install git -y
RUN apt-get install libsfml-dev -y
RUN apt-get install ninja-build -y
RUN apt-get install libgtest-dev -y

WORKDIR /app
COPY include /app/include
COPY src /app/src
COPY test /app/test
COPY CMakeLists.txt /app/CMakeLists.txt 

# RUN cmake . -G Ninja
# RUN cmake --build .
# RUN ./GameOfLifeTests
