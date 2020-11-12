#!/bin/sh
PANDOC_BIN=pandoc
ZIP_BIN=zip
PROJECT_NAME=TP1
SOURCE=README.md
FILES="TP1.c Exercise1.c Exercise1.h Exercise2.c Exercise2.h"
OUTPUT_FOLDER=out/
PLANTUML_IMAGES=Diagrammes/
ZIP_LOCATION=${OUTPUT_FOLDER}/${PROJECT_NAME}_HALDI_Hugo.zip

if [ ! -d "${OUTPUT_FOLDER}" ]; then
    mkdir ${OUTPUT_FOLDER}
fi

${PANDOC_BIN} -o ${OUTPUT_FOLDER}/${PROJECT_NAME}.pdf -F pandoc-plantuml -V geometry:margin=1in ${SOURCE}

mv plantuml-images/ ${OUTPUT_FOLDER}/${PLANTUML_IMAGES}/

${ZIP_BIN} -j ${ZIP_LOCATION} ${OUTPUT_FOLDER}/${PROJECT_NAME}.pdf ${SOURCE} ${FILES}
cd ${OUTPUT_FOLDER} && ${ZIP_BIN} ${PROJECT_NAME}_HALDI_Hugo.zip ${PLANTUML_IMAGES}/*.png