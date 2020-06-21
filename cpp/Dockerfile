FROM ubuntu:18.04

RUN apt-get update && apt-get install -y build-essential libgl1-mesa-glx freeglut3
RUN useradd -ms /bin/bash demo

USER demo

WORKDIR /home/demo/cpp

CMD /bin/bash