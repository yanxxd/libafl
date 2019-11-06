# afl-fuzz-one
## build
`make`

## test
`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.`
`../test_fuzz_one in/README`

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
