#!/bin/bash

mvn package &&\
  mkdir -p ./deb_install_files/usr/lib/jgalaxian &&\
  mkdir -p ./deb_install_files/usr/lib/jgalaxian/dep-jars &&\
  cp target/jgalaxian-1.0-SNAPSHOT.jar ./deb_install_files/usr/lib/jgalaxian/. &&\
  cp target/dep-jars/AudioCue*jar ./deb_install_files/usr/lib/jgalaxian/dep-jars/. &&\
  dpkg-buildpackage

