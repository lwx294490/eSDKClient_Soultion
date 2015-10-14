#!/bin/sh

OPERATEDIR=log4cpp
echo "---------compile the log4cpp of Linux---------------"

sleep 2

read -p "Copy the /log4cpp To /usr/local, Press AnyKey To Continue!" var
cp -r $OPERATEDIR /usr/local/
cd /usr/local/$OPERATEDIR/

read -p "./configure, Press AnyKey To Continue!" var
./configure
echo "------ ./configure --end--------"

read -p "make, Press AnyKey To Continue!" var
cd /usr/local/$OPERATEDIR/
make
echo "------ make ---------end--------"

read -p "make check, Press AnyKey To Continue!" var
cd /usr/local/$OPERATEDIR/
make check
echo "------ make check ---end--------"

read -p "make install, Press AnyKey To Continue!" var
cd /usr/local/$OPERATEDIR/
make install
echo "------ make install -end--------"

sleep 2
read -p "Install OK ,Delete The Log4Cpp Which Be Copied Just Now, Press AnyKey To Continue!" var
rm -r -f /usr/local/$OPERATEDIR/

sleep 2
echo "---------compile the log4cpp of Linux Finish in success---------------"
