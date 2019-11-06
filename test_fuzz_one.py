#!/usr/bin/env python
# coding: utf-8


import ctypes



def main():
    libafl = ctypes.cdll.LoadLibrary("./libafl.so")

    ret = libafl.afl_init(b"-o out -S S1 -- ./objdump -g @@")

    if ret:
        print("afl_init failed! error code:%d" % ret)
        return


    print("======test1======")
    libafl.afl_fuzz_one(b"in/seed", 1)

    libafl.afl_get_result()

    afl_get_result = libafl.afl_get_result
    afl_get_result.restype = ctypes.POINTER(ctypes.c_int)
    result = afl_get_result()
    print("coverage=%d" % result[0]);
    print("crash=%d" % result[1]);
    print("exec_us=%dus" % result[2]);
    print("new_path=%d\n" % result[3]);



    print("======test2======")
    libafl.afl_fuzz_one(b"in/seed", 1)

    libafl.afl_get_result()

    afl_get_result = libafl.afl_get_result
    afl_get_result.restype = ctypes.POINTER(ctypes.c_int)
    result = afl_get_result()
    print("coverage=%d" % result[0]);
    print("crash=%d" % result[1]);
    print("exec_us=%dus" % result[2]);
    print("new_path=%d\n" % result[3]);


if __name__ == "__main__":
    main()
