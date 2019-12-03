#!/bin/bash

# --- [WARNING]: ONLY RUN THIS FROM '../src/' DIRECTORY! ---
# To use, starting from src/ directory, use commands:
#
#	cd ..
#	cp src/submitprep.sh .
#	chmod +x submitprep.sh
#	./submitprep.sh
#
#	:-/
#
#

rm *.tar.gz;
cd src;
make clean;
cd ..
tar -czf pa3.tar.gz src/;
