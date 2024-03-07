FROM ubuntu:latest

RUN apt-get update && apt-get install -y g++ && apt-get clean
RUN apt install libsctp-dev -y

COPY server.cpp /app/server.cpp

WORKDIR /app

RUN g++ -o server server.cpp  -lsctp
EXPOSE 12345/sctp
CMD ["./server"]
