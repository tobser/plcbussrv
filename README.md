# plcbussrv
small TCP server to transparently write/read  data to/from the PLCBUS via  plc2pc interface 1141+

    * reads data from the connected TCP clients in chunks of 8 Bytes and writes those as they where received to the serial interface of the 1141+
    * reads data in chunks of 9 Bytes from the serial interface of the 1141 and distributes it to all connected TCP clients.

This server is intended to be used with the PLCBUS module of misterhouse. It was created because the 1141+ is quiet touchy about the read/write timings and doesn't seem to like the timing of the misterhouse loop...

The device still seem to behave rather strange if there are lots of command send to/from the bus. it seems to be a known problem according to some entries in the http://plcbus.info forum.
Maybe its the fault of my phase coupler 4825, which also does no behave..

still not sure whos fault failing commands actually are... maybe mine :-)

any way, here is how to get it up and running:

# INSTALL
currently the project requires to use qt5 qmake. It's located in /usr/lib/qt5/bin on my system (gentoo).

To install the server run:

 /usr/lib/qt5/bin/qmake
 make
 sudo make install

# USAGE

    plcbussrv <serial_device> <tcp_port>

example:

    plcbussrv /dev/ttyplcbus 3234


# About

All code is based on the Qt samples with some clue added.. nothing new here.
So for licensing issues, the license probably depends on what Qt says.. In case this is not the case, WTFPL shall be used.
