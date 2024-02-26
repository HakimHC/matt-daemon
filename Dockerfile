FROM alpine:3.18

RUN adduser -D hakim

RUN apk update && apk add gcc g++ make

COPY . /app

WORKDIR /app

RUN make

# USER hakim

CMD ["./Matt_daemon"]