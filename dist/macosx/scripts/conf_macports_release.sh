#! /bin/bash

prefix="/opt/local"
WX_CONF="${prefix}/Library/Frameworks/wxWidgets.framework/Versions/wxPython/3.0/bin/wx-config"

MYCC=`${WX_CONF} --cc`
MYCXX=`${WX_CONF} --cxx`
MYLD=`${WX_CONF} --ld`

config_args="--with-wx-config=${WX_CONF} \
             --disable-dependency-tracking \
             --with-biosiglite"
#              --with-lapack-lib=/opt/local/lib/libatlas.a \
#              --enable-debug \

../../configure ${config_args} CC="${MYCC} -I${prefix}/include" CXX="${MYCXX} -I${prefix}/include" LD="${MYLD}" LDFLAGS="-headerpad_max_install_names -L${prefix}/lib" PYTHON="${prefix}/bin/python2.7"
