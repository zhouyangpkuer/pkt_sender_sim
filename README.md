You need to set TSC_FREQ according to the cpu frequency. 

Note the maximun controlled rate of this tool is 38Mpps. 

## Compiling: g++ -o pkt_sender pkt_sender.cpp

## usage: ./pkt_sender pkt_rate pkt_num

### pkt_rate: unit is Mpps.

### pkt_num: pkt number that you want to send.

## eg: ./pkt_sender 38 100000000
