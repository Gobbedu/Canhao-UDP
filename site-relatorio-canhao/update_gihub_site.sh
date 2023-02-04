#!/bin/bash

rm -rf ../docs/*; # remove os arquivos atuais do github
hugo --minify --theme hugo-book; # faz o build do site 
cp -vR public/* ../docs/*; # copia os arquivos para o site github