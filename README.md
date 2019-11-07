# afl-fuzz-one
Only test one time use AFL's havoc.  
Print [coverage, is_crash, exec_us, is_new_path].  
Testcase is `new_seed`.  

## 1. build
`make`

## 2. test

### 2.1 C
`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.`
`../test_fuzz_one in/seed`

output
```
======test1======
coverage=77
crash=0
exec_us=743us
new_path=1

======test2======
coverage=77
crash=0
exec_us=577us
new_path=0
```
### 2.2 python3
`python3 test_fuzz_one.py`

output
```
======test1======
coverage=77
crash=0
exec_us=1004us
new_path=1

======test2======
coverage=77
crash=0
exec_us=799us
new_path=0
```
