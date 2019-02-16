/*
 * cs330_perf.h
 *
 *  Created on: Jan 25, 2019
 *      Author: sleepwalker
 */

#ifndef CS330_PERF_H_
#define CS330_PERF_H_

#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>


typedef struct{
	uint16_t rxport;
	uint16_t txport;
	int rx_socket;
	int tx_socket;
	size_t packet_size;
	size_t count;
	size_t delay;
	size_t tx_delay;
}connection_t;


const char usage_longstr[] = "Usage: cs330_perf [-s|-c host] [options]\n"
                           "  -p  <port> Receiving port \n"
						   "  -t  <port> Transmitting port \n"
                           "  -i  <size> Packet size. Default 1024   \n"
						   "  -d  <msec> Delay (in milliseconds) to start transmitting\n"
                           "  -c  <count> Number of packets to transmit. If argument not included, will send unlimited packets \n"
			   "  -m  <usec>  Delay in microseconds between each transmission\n>";
#endif /* CS330_PERF_H_ */
