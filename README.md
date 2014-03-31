digger-mate-panel-monitor
=========================

Description
===========
Main target of this application should be monitoring of some machines. Monitor would be always 
visible right on mate panel as applet.

Server side
===========
On server which will be monitored should be digger-server running. This application serve simple 
socket server and periodically generate some stats from machine. There are some scripts for 
generating statistics. Application run all scripts from specified folder in unknown order, but 
sequentially.

Scripts are written mainly in BASH, but would be written in almost anything. Important is 
correctness of output which they generate - corectness is not checked by server side.

When some log is generated, it sends this xml file to client through network.

Client side
===========
Client application lives mainly in mate panel. Its pooling server which is under monitoring and 
shows some statistics to user.
