#!/bin/sh

trap "exit 0" SIGTERM

tail -f&

wait $!
