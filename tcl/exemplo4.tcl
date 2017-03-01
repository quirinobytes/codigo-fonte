#!/usr/bin/expect
#
#



set nome "GETTING SSH SLOGAN"

spawn nc localhost 22

expect ".*"

puts $expect_out(buffer)

puts "$expect_out(0,string)"
