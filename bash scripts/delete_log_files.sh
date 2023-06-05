#!/bin/bash

n=15
free=$(free | awk 'NR==2{print $2}') # получаем общую память в байтах

for file in $(find . -name "*.log")
do
    size=$(du $file | awk '{print $1}') # получаем размер файла в байтах
    limit=$((free/n)) # вычисляем ограничение на размер файла
    if [ "$size" -gt "$limit" ]; then # проверяем размер файла на ограничение
        rm $file # удалить файл
    fi
done
