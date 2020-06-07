FROM ubuntu
RUN apt-get update
RUN apt-get install gcc-multilib -y
RUN apt install git -y
apt install build-essential -y  
RUN git clone https://github.com/Ryokurow/SP3 
COPY sp3.c sp3.c
RUN chmod ugo+x sp3.c
RUN gcc -m32 sp3.c -o sp3.
CMD ./sp3.


