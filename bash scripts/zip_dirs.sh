#!/bin/bash

files=$(find . -type d)
for file in $files
do
    zip $file-$(date "+%F").zip $file
    mv $file-$(date "+%F").zip /home/kali
done
