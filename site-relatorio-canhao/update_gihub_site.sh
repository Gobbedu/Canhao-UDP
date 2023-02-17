#!/bin/bash

rm -rf ../docs/*; # remove os arquivos atuais do github
hugo --minify --theme hugo-book; # faz o build do site 
mv public/* ../docs/; # move os arquivos da pasta public para o github


# cp -vR public/* ../docs/*; # copia os arquivos para o site github
# rm -rf public/
