FROM gcc:latest

COPY . /myKernel

WORKDIR /myKernel

RUN apt-get update && apt-get upgrade -y

CMD ["make"]
