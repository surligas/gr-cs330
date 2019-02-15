/*
 * cs330_perf.c
 *
 *  Created on: Jan 25, 2019
 *      Author: sleepwalker
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>


#include "cs330_perf.h"

connection_t conn;
uint32_t packets_sent = 0;
uint32_t seq_num = 0;
uint32_t seq_buf = 0;
uint32_t lost_packets = 0;
uint32_t last_count = 0;
struct timespec ts1, ts2;
double bytes =0;

void
get_args(int argc, char **argv)
{
	int flag;
	while((flag = getopt(argc, argv,"p:i:c:t:d:m:")) != -1)
	{
		switch(flag){
		case 'p':
			conn.rxport = atoi(optarg);
			break;
		case 't':
			conn.txport = atoi(optarg);
			break;
		case 'i':
			conn.packet_size = atoi(optarg);
			break;
		case 'c':
			conn.count = atoi(optarg);
			break;
		case 'd':
			conn.delay = 1000 * atoi(optarg);
			break;
		case 'm':
			conn.tx_delay = atoi(optarg);
			break;
		default:
			fprintf(stdout, usage_longstr);
			exit(0);
			break;
		}
	}

}


void*
run_client() {
	struct sockaddr_in client, server;

	server.sin_family = AF_INET;
	server.sin_port = htons(conn.txport);
	server.sin_addr.s_addr = INADDR_ANY;

	uint32_t counter = 0;
	uint8_t* buffer = (uint8_t*) malloc(conn.packet_size * sizeof(uint8_t));
	uint32_t div_size = (conn.packet_size - 4)/sizeof(usage_longstr);
	for(size_t i=0; i < div_size ; i++){
	  memcpy(&buffer[4+i*sizeof(usage_longstr)], usage_longstr, sizeof(usage_longstr)*sizeof(uint8_t));
	}
	uint32_t mod_size = (conn.packet_size - 4)%sizeof(usage_longstr);
	memcpy(&buffer[4 + div_size*sizeof(usage_longstr)], usage_longstr, mod_size*sizeof(uint8_t));
	uint32_t network_counter = 0;
	int32_t npackets = 0;
	usleep(conn.delay);
	if (conn.count) {
		while (counter++ < conn.count) {
			network_counter = htonl(counter);
			memcpy(&buffer[0], &network_counter, sizeof(uint32_t));
			if (sendto(conn.tx_socket, buffer, conn.packet_size, 0,
					(struct sockaddr *) &server, sizeof(server)) < 0) {
				fprintf(stderr, "send to error");
				exit(1);
			}
			packets_sent++;
			usleep(conn.tx_delay);
		}
	} else {
		while (1) {
			network_counter = htonl(counter);
			memcpy(&buffer[0], &network_counter, sizeof(uint32_t));
			if (sendto(conn.tx_socket, buffer, 1024, 0,
					(struct sockaddr *) &server, sizeof(server)) < 0) {
				fprintf(stderr, "send to error");
				exit(1);
			}
			usleep(conn.tx_delay);
			packets_sent++;
			counter++;
		}
	}

}

void*
run_server()
{
	struct sockaddr_in client, server;
	server.sin_family      = AF_INET;
	server.sin_port        = htons(conn.rxport);
	server.sin_addr.s_addr = INADDR_ANY;

	uint8_t *rx_buffer = (uint8_t *)malloc(65536*sizeof(uint8_t));


    if ( bind(conn.rx_socket, (const struct sockaddr *)&server,
            sizeof(server)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

	int client_size = sizeof(client);
    clock_gettime(CLOCK_MONOTONIC, &ts1);
	while (1) {
		if (recvfrom(conn.rx_socket, rx_buffer, 65536*sizeof(uint8_t), 0, (struct sockaddr *) &client,
				&client_size) < 0) {
			fprintf(stderr, "Receive error\n");
			exit(1);
		}
		memcpy(&seq_buf, &rx_buffer[0], sizeof(uint32_t));
		seq_buf = ntohl(seq_buf);
		if (seq_buf == seq_num +1){
			seq_num++;
		}
		else if (seq_buf > seq_num +1){ // Lost packets
			lost_packets += (seq_buf - seq_num - 1);
			seq_num = seq_buf;
		}
		else if(seq_buf < seq_num + 1){ // Out of order packet
			if(lost_packets){
				lost_packets--;
			}
		}
	}

}

void*
print_statistics()
{
	uint64_t total_bytes = 0;
	uint32_t total_counts = 0;
	uint32_t seconds = 0;
	float throughput = 0;
	while(1){
		total_bytes = (seq_num - last_count)*conn.packet_size;
		clock_gettime(CLOCK_MONOTONIC, &ts2);

		throughput = 1.0*total_bytes/(1000000*(1.0*((ts2.tv_sec - ts1.tv_sec))));
		total_counts++;
		if(total_bytes > 0){
		  seconds++;
		  bytes += 1.0*total_bytes/(1000000*(1.0*((ts2.tv_sec - ts1.tv_sec))));
		  printf("Packet loss = %f "
				"Throughput = %lf MB/s " 
				"Mean throughput = %f MB/s \r",
				(100*lost_packets*1.0)/seq_num, throughput, 
				bytes/seconds);
		  fflush(stdout);
	          last_count = seq_num;
		}
		clock_gettime(CLOCK_MONOTONIC, &ts1);
		sleep(1);
	}
}

int main(int argc, char **argv) {
	conn.txport = 0;
	conn.rxport = 0;
	conn.packet_size = 1024;
	pthread_t tid, rid, sid;
	get_args(argc, argv);
	if((conn.rxport == 0) || (conn.txport == 0)){
		fprintf(stdout, usage_longstr);
		exit(0);
	}
	if ((conn.rx_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "socket error\n");
		exit(1);
	}
	if ((conn.tx_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "socket error\n");
		exit(1);
	}
	pthread_create(&tid, NULL, run_server, NULL);
	sleep(1);
	pthread_create(&rid, NULL, run_client, NULL);
	pthread_create(&sid, NULL, print_statistics, NULL);
	pthread_join(tid, NULL);
	pthread_join(sid, NULL);
	pthread_join(rid, NULL);
	pthread_exit(NULL);

	return 1;
}
