FROM alpine:3.18

RUN adduser -D hakim

RUN apk update && apk add gcc g++ make inetutils-telnet

COPY . /app

WORKDIR /app

RUN chmod +x ./container.sh

RUN make

# USER hakim

# CMD ["./Matt_daemon"]
CMD ["./container.sh"]