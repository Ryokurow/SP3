FROM ubuntu
RUN apt-get update
RUN apt-get install gcc-multilib -y
COPY sp3.c sp3.c
RUN chmod ugo+x sp3.c
RUN gcc -m32 sp3.c -o sp3.
CMD ./sp3.


