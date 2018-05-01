# -*- coding: utf-8 -*-
import serial
import sys
import os
import struct
import json
import time
import threading
import signal
import binascii

from util import NestProcess
from util import NestErrCode
from util import NestOpcode
from util import NestSerialProcess
from lib.projutil import ProjectUtil

class NestTerminateProcess(NestProcess):
    def __init__(self, port, ipaddr, path):
        NestProcess.__init__(self)
        util = ProjectUtil()
        self.nsp = None
        self.conf_content = util.load_conf(path, True)
        self.short_uuid = self.conf_content['short_uuid']
        self.app_name = self.conf_content['name']

        if port is not '':
            self.nsp = NestSerialProcess(NestSerialProcess.NEST_INTERFACE_COM, port, self.data_received)
        elif ipaddr is not '':
            self.nsp = NestSerialProcess(NestSerialProcess.NEST_INTERFACE_TCP, ipaddr, self.data_received)

        # initiate run packetes
        command = self.nsp.command_pack(None, NestOpcode.LUNCHR_KILL)
        self.nsp.send(command)

    def data_received(self, data):
        command = self.nsp.command_unpack(data)
        if not command == None:
            if command.opcode == (NestOpcode.LUNCHR_KILL | 0x80):
                if command.data_len == 1:
                    #　Get the BFTP Init response, start to issue the first raw packets
                    if command.data[0] == 0x00:
                        print 'Process {} exited.'.format(self.app_name)
                    else:
                        print 'Invalid state'
                    self.dispose()

    def abort_handler(self):
        if self.nsp is not None:
            self.nsp.close()
        exit()
