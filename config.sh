#!/bin/bash

name='raw_data'
ts=$(date +"%Y-%m-%d_%H%M%S")

sed 's/\r$//' $name.txt > database/$name.cr
awk 'NF' database/$name.cr > database/$name.nl
awk 'NF>=7' database/$name.nl > database/data-$ts.txt

cat database/data-$ts.txt > latest-data

rm -r database/$name.*

rsync -avzr /home/xxxx/MyProject/database/ xxxx@xxx.xxx.xxx.xxx:/home/master/applications/xxxx/private_html/
rsync -avzr /home/xxxx/MyProject/latest-data xxxx@xxx.xxx.xxx.xxx:/home/master/applications/xxxx/public_html/iot/

