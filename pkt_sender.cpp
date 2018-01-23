#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "mytime.h"


using namespace std;

#define MAX_DISTINCT_PKT 1000
#define PKT_SIZE 84
#define BURST_SIZE 32

struct tuple
{
	u32 sip, dip;
	u16 sp, dp;
	u16 type;
};

struct tuple pkts[MAX_DISTINCT_PKT];

// unit is nano second;
u64 cal_gap(double pkt_rate, u64 hz)
{
	// return (int)(1.0 * BURST_SIZE / pkt_rate * 1000.0);
	u64 gap = (double)(hz * BURST_SIZE) / pkt_rate;
	return gap;
}

int main(int argc, char ** argv)
{
	double pkt_rate = atof(argv[1]) * 1e6; // Mpps
	int npkts = atoi(argv[2]); // pkt number that you want to sent;

	FILE * f_trace = fopen("trace.dat", "r");
	int pkt_cnt = 0;
	while(fscanf(f_trace, "%u %u %hu %hu %hu\n", &pkts[pkt_cnt].sip, &pkts[pkt_cnt].dip, &pkts[pkt_cnt].sp, &pkts[pkt_cnt].dp, &pkts[pkt_cnt].type) != EOF)
	{
		pkt_cnt++;
		// printf("pkt_cnt = %d\n", pkt_cnt);
	}

	u64 gap_cycle = cal_gap(pkt_rate, TSC_FREQ);
	printf("gapcycle = %lu\n", gap_cycle);

  	

	u64 base_cycle = get_tsc_cycles();
	u64 start_cycle = base_cycle + TSC_FREQ / 10;
	u64 next_cycle = start_cycle;
	u64 now_cycle;
	
	u64 pkt_sent = 0;
	while(pkt_sent < npkts)
	{
		now_cycle = get_tsc_cycles();
		while (now_cycle < next_cycle)
		{
			u64 tmp_cycle = get_tsc_cycles();
			now_cycle = tmp_cycle;
		}

		int i, pkt_index;
		for(i = 0; i < BURST_SIZE; i++)
		{
			pkt_index = (pkt_sent + i) % pkt_cnt;
			// sending pkts[pkt_index];
			pkts[pkt_index].sip ++;
			pkts[pkt_index].dip --;
			pkts[pkt_index].sp *= 2;
			pkts[pkt_index].dp /= 2.0;
			pkts[pkt_index].type |= 0xFFFF;
		}

		// update next_cycle
		next_cycle += gap_cycle;
		if (next_cycle + 100000 < now_cycle) // this is to avoid scheduling cause large burst
			next_cycle = now_cycle + gap_cycle;
	

		pkt_sent += BURST_SIZE;
	}
	double duration = (double)(get_tsc_cycles() - start_cycle) / TSC_FREQ;
	printf("%lu pkt sent, %.4lf Mpps\n", pkt_sent, (double)(pkt_sent) * 1e-6 / duration);
	
	return 0;
}
