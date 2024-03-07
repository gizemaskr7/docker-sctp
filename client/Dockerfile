FROM ubuntu:latest

RUN apt-get update && apt-get install -y g++ && apt-get clean
RUN apt install libsctp-dev -y
COPY client.cpp /app/client.cpp 

WORKDIR /app

RUN g++ -o client client.cpp  -lsctp
EXPOSE 12345/sctp
CMD ["./client"]
