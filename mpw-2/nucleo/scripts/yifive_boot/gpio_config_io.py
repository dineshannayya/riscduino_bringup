# number of IO in the configuration stream for each chain
NUM_IO = 19

# defines these values for IO configurations
C_MGMT_OUT = 0
C_MGMT_IN = 1
C_USER_BIDIR = 2
C_DISABLE = 3
C_ALL_ONES = 4
C_USER_BIDIR_WPU = 5
C_USER_BIDIR_WPD = 6
C_USER_IN_NOPULL = 7
C_USER_OUT = 8

config_h = [
    C_USER_BIDIR,  #37
    C_USER_BIDIR,  #36
    C_USER_BIDIR,  #35
    C_USER_BIDIR,  #34
    C_USER_BIDIR,  #33
    C_USER_BIDIR,  #32
    C_USER_BIDIR,  #31
    C_USER_BIDIR,  #30
    C_USER_BIDIR,  #29
    C_USER_BIDIR,  #28
    C_USER_BIDIR,  #27
    C_USER_BIDIR,  #26
    C_USER_BIDIR,  #25
    C_USER_BIDIR,  #24
    C_USER_BIDIR,  #23
    C_USER_BIDIR,  #22
    C_USER_BIDIR,  #21
    C_USER_BIDIR,  #20
    C_USER_BIDIR,  #19
]

del config_h[NUM_IO:]

config_l = [
    C_MGMT_OUT,   #0
    C_MGMT_OUT,   #1
    C_MGMT_OUT,   #2
    C_MGMT_OUT,   #3
    C_MGMT_OUT,   #4
    C_MGMT_OUT,   #5
    C_MGMT_OUT,   #6
    C_MGMT_OUT,   #7
    C_MGMT_OUT,   #8
    C_MGMT_OUT,   #9
    C_MGMT_OUT,   #10
    C_MGMT_OUT,   #11
    C_MGMT_OUT,   #12
    C_MGMT_OUT,   #13
    C_MGMT_OUT,   #14
    C_MGMT_OUT,   #15
    C_MGMT_OUT,   #16
    C_MGMT_OUT,   #17
    C_MGMT_OUT,   #18
]

del config_l[NUM_IO:]
