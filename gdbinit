target remote localhost:2000
monitor reset halt
load
monitor reset init
layout src
b USCI0RX_ISR
b main
