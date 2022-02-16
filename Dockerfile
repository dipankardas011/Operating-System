FROM gcc:latest

COPY . /myKernel

# WORKDIR /myKernel

WORKDIR /myKernel/CPU/

# RUN apt-get update && apt-get upgrade -y

CMD ["ls"]
