#!/bin/env python3
#
# gpio_config_builder.py
#          Build a pair of configuration bit streams for GPIO on MPW-2 accounting for
#          hold violations between gpio blocks.
#
# Input:   Hold violations between each GPIO and desired
# Output:  Configuration bitsteams for upper and lower gpio chains
#

# import gpio and configuration definitions
# from gpio_config_def import NUM_IO, C_MGMT_IN, C_MGMT_OUT, C_USER_BIDIR, C_DISABLE, C_ALL_ONES, \
#                             H_DEPENDENT, H_INDEPENDENT, H_NONE, H_SPECIAL, config_h, config_l, gpio_h, gpio_l, \
#                             C_USER_BIDIR_WPU, C_USER_BIDIR_WPD, C_USER_IN_NP, C_USER_OUT

# from gpio_config_def import *

# number of IO in the configuration stream for each chain
NUM_IO = 19

# defines these cases of hold violations
H_NONE = 0
H_DEPENDENT = 1
H_INDEPENDENT = 2
H_SPECIAL = 3

# defines these values for IO configurations
C_MGMT_OUT = 0
C_MGMT_IN = 1
C_USER_BIDIR = 2
C_DISABLE = 3
C_ALL_ONES = 4
C_USER_BIDIR_WPU = 5
C_USER_BIDIR_WPD = 6
C_USER_IN_NP = 7
C_USER_OUT = 8

# ------------------------------------------


def setup(arg_gpio_h, arg_gpio_l):

    gpio_h=list()
    gpio_l=list()
    # arg_gpio_h = args.gpio_h
    arg_gpio_h = arg_gpio_h.replace('[','').replace(']','')
    arg_gpio_h = arg_gpio_h.split(',')
    for i,violation in enumerate(arg_gpio_h):
        if violation == 'H_NONE': violation_type = H_NONE
        elif violation == 'H_INDEPENDENT': violation_type = H_INDEPENDENT
        elif violation == 'H_DEPENDENT': violation_type = H_DEPENDENT
        else :
            print (f"incorrect violation type inside provided argument gpio_h {arg_gpio_h} it has to be H_NONE or H_INDEPENDENT or H_DEPENDENT")
        #     sys.exit()
        gpio_h.append([f'IO[{37-i}]',violation_type])
    # del gpio_h[args.num_io:]
    # if (args.debug):
    #     print(f"gpio_h {gpio_h}")
    # arg_gpio_l = args.gpio_l
    arg_gpio_l = arg_gpio_l.replace('[','').replace(']','')
    arg_gpio_l = arg_gpio_l.split(',')
    # python gpio_config_builder.py -gpio_h [H_NONE,H_DEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_DEPENDENT,H_INDEPENDENT,H_DEPENDENT,H_DEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT]  -gpio_l [H_NONE,H_DEPENDENT,H_DEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_DEPENDENT,H_DEPENDENT,H_INDEPENDENT,H_DEPENDENT,H_DEPENDENT,H_INDEPENDENT,H_DEPENDENT,H_DEPENDENT,H_INDEPENDENT,H_DEPENDENT,H_DEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT,H_INDEPENDENT] -n 8
    for i,violation in enumerate(arg_gpio_l):
        if violation == 'H_NONE': violation_type = H_NONE
        elif violation == 'H_INDEPENDENT': violation_type = H_INDEPENDENT
        elif violation == 'H_DEPENDENT': violation_type = H_DEPENDENT
        else :
            print (f"incorrect violation type inside provided argument gpio_l {arg_gpio_l} it has to be H_NONE or H_INDEPENDENT or H_DEPENDENT")
        #     sys.exit()
        gpio_l.append([f'IO[{i}]',violation_type])
    # del gpio_l[args.num_io:]
    # if (args.debug):
    #     print(f"gpio_l {gpio_l}")
    return gpio_h, gpio_l


def build_stream_none():
    s = 0x00;
    return s




def correct_dd_holds(stream, bpos):
    stream = stream | (1 << bpos);
    return stream

# ------------------------------------------


def build_config(arg_gpio_h, arg_gpio_l):
    stream_h = arg_gpio_h.channel_status
    stream_l = arg_gpio_l.channel_status
    config_stream = []

    config_stream.append(stream_l & 0xFF)
    config_stream.append((stream_l >> 8) & 0xFF)
    config_stream.append((stream_l >> 16) & 0xFF)
    config_stream.append((stream_l >> 24) & 0xFF)

    config_stream.append(stream_h & 0xFF)
    config_stream.append((stream_h >> 8) & 0xFF)
    config_stream.append((stream_h >> 16) & 0xFF)
    config_stream.append((stream_h >> 24) & 0xFF)

    config_stream.append(arg_gpio_l.fail_count & 0xFF)
    config_stream.append(arg_gpio_h.fail_count & 0xFF)


    config_stream.append(0x01)
    config_stream.append(0x18)
    config_stream.append(0x00)
    config_stream.append(0x00)

    config_stream.append(0x01)
    config_stream.append(0x18)
    config_stream.append(0x00)
    config_stream.append(0x00)

    print("Config Stream : {}".format(config_stream))

    return config_stream

