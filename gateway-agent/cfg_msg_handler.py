import socket_server
import os
from flags import *

def callback(bytedata):
    if bytedata[0] != CONFIGURATION:
        return
    pos = 6
    msg_len = len(bytedata)
    while pos < msg_len:
        if bytedata[pos] == ELEMENT_RULE:
            handle_rule(bytedata[pos+1:pos+12])
            pos += 12
        elif bytedata[pos] == ELEMENT_CONFIGURATION:
            cfg_len = bytedata[pos+1] * 256 + bytedata[pos+2]
            handle_cfg(bytedata[pos+3:pos+3+cfg_len])
            pos += (3 + cfg_len)
        elif bytedata[pos] == ELEMENT_SECRET:
            # no secret
            break
        else:
            break
    return bytearray((bytedata[0], bytedata[1], SUCCESS))

def handle_rule(rulebytes):
    src = str(rulebytes[0:4])
    src_pre = int(rulebytes[4])
    dst = str(rulebytes[5:9])
    dst_pre = int(rulebytes[9])
    action = rulebytes[10]
    if action == RULE_BYPASS:
        pass
    elif action == RULE_DISCARD:
        pass
    elif action == RULE_PROTECT:
        pass

def handle_cfg(cfgbytes):
    cfgstr = str(cfgbytes)
    # write to profile
    ipsec_conf = open('ipsec.conf', 'a')
    ipsec_conf.write(cfgstr)
    ipsec_conf.write('\n')
    ipsec_conf.close()
    # strongswan operations
    conn_name = cfgstr[5:cfgstr.find('\n')]
    print "ipsec reload && ipsec up " + conn_name
    # os.system("ipsec reload && ipsec up " + conn_name)

myserver = socket_server.socket_server(2020, callback)
print "Server is running..."
myserver.start()

while True:
    if str(raw_input()) == "END":
        break

myserver.stop()
print "Server has been closed."
exit()

