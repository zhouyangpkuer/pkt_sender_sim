g++ -o pkt_sender pkt_sender.cpp

you need to set TSC_FREQ according to the cpu frequencu

usage: ./pkt_sender pkt_rate pkt_num
pkt_rate: unit is Mpps.
pkt_num: pkt number that you want to send.

./pkt_sender 38 100000000



