FROM debian:squeeze

RUN echo "deb http://archive.debian.org/debian squeeze main" > /etc/apt/sources.list
RUN echo "deb http://archive.debian.org/debian squeeze-lts main" >> /etc/apt/sources.list
RUN echo "Acquire::Check-Valid-Until false;" > /etc/apt/apt.conf

RUN apt-get update -y --force-yes

RUN apt-get install -y complearn-tools zlib1g-dev --force-yes

RUN apt-get install -y qsearch-tools --force-yes

RUN apt-get install -y vim --force-yes
