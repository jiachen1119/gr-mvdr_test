#!/usr/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir="/home/tang/CLionProjects/OOT_test/gr-mvdr_test/python/mvdr_test"
export GR_CONF_CONTROLPORT_ON=False
export PATH="/home/tang/CLionProjects/OOT_test/gr-mvdr_test/build/python/mvdr_test":"$PATH"
export LD_LIBRARY_PATH="":$LD_LIBRARY_PATH
export PYTHONPATH=/home/tang/CLionProjects/OOT_test/gr-mvdr_test/build/test_modules:$PYTHONPATH
/usr/bin/python3 /home/tang/CLionProjects/OOT_test/gr-mvdr_test/python/mvdr_test/qa_mvdr.py 
