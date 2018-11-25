/* Protocol 1 (Utopia) provides for data transmission in one direction only, from
sender to receiver. The communication channel is assumed to be error free
and the receiver is assumed to be able to process all the input infinitely quickly.
Consequently, the sender just sits in a loop pumping data out onto the line as
fast as it can. */
typedef enum {frame_arrival} event_type;
#include "protocol.h"
void sender1(void)
{
	frame s;                               /* buffer for an outbound frame */
	packet buffer;                         /* buffer for an outbound packet */
	while(true) {
		from_network_layer(&buffer);       /* go get something to send */
		s.info = buffer;                   /* copy it into s for transmission */
		to_physical_layer(&s);             /* send it on its way */
	}
	/* Tomorrow, and tomorrow, and tomorrow, Creeps in this petty pace from day to day to the last syllable of recorded time.
	– Macbeth, V, v */
}
void receiver1(void)
{
	frame r;
	event_type event;                      /* filled in by wait, but not used here */
	while(true) {
		wait_for_event(&event);            /* only possibility is frame_arrival */
		from_physical_layer(&r);           /* go get the inbound frame */
		to_network_layer(&r.info);         /* pass the data to the network layer */
	}
}


/* Protocol 2 (Stop-and-wait) also provides for a one-directional flow of data from
sender to receiver. The communication channel is once again assumed to be error
free, as in protocol 1. However, this time the receiver has only a finite buffer
capacity and a finite processing speed, so the protocol must explicitly prevent
the sender from flooding the receiver with data faster than it can be handled. */
typedef enum {frame_arrival} event_type;
#include "protocol.h"
void sender2(void)
{
	frame s;                                         /* buffer for an outbound frame */
	packet buffer;                                   /* buffer for an outbound packet */
	event_type event;                                /* frame_arrival is the only possibility */
	while(true) {
		from_network_layer(&buffer);                 /* go get something to send */
		s.info = buffer;                             /* copy it into s for transmission */
		to_physical_layer(&s);                       /* bye-bye little frame */
		wait_for_event(&event);                      /* do not proceed until given the go ahead */
	}
}
void receiver2(void)
{
	frame r, s;                                      /* buffers for frames */
	event_type event;                                /* frame_arrival is the only possibility */
	while(true) {
		wait_for_event(&event);                      /* only possibility is frame_arrival */
		from_physical_layer(&r);                     /* go get the inbound frame */
		to_network_layer(&r.info);                   /* pass the data to the network layer */
		to_physical_layer(&s);                       /* send a dummy frame to awaken sender */
	}
}


/* Protocol 3 (PAR) allows unidirectional data flow over an unreliable channel. */
#define MAX_SEQ 1                               /* must be 1 for protocol 3 */
typedef enum {frame_arrival, cksum_err, timeout} event_type;
#include "protocol.h"
void sender3(void)
{
	seq_nr next_frame_to_send;                  /* seq number of next outgoing frame */
	frame s;                                    /* scratch variable */
	packet buffer;                              /* buffer for an outbound packet */
	event_type event;
	next_frame_to_send = 0;                     /* initialize outbound sequence numbers */
	from_network_layer(&buffer);                /* fetch first packet */
	while(true) {
		s.info = buffer;                        /* construct a frame for transmission */
		s.seq = next_frame_to_send;             /* insert sequence number in frame */
		to_physical_layer(&s);                  /* send it on its way */
		start_timer(s.seq);                     /* if answer takes too long, time out */
		wait_for_event(&event);                 /* frame_arrival, cksum_err, timeout */
		if(event == frame_arrival) {
			from_physical_layer(&s);            /* get the acknowledgement */
			if(s.ack == next_frame_to_send) {
				stop_timer(s.ack);              /* turn the timer off */
				from_network_layer(&buffer);    /* get the next one to send */
				inc(next_frame_to_send);        /* invert next frame to send */
			}
		}
	}
}
void receiver3(void)
{
	seq_nr frame_expected;
	frame r, s;
	event_type event;
	frame_expected = 0;
	while(true) {
		wait_for_event(&event);                 /* possibilities: frame_arrival, cksum_err */
		if(event == frame_arrival) {           /* a valid frame has arrived */
			from_physical_layer(&r);            /* go get the newly arrived frame */
			if(r.seq == frame_expected) {      /* this is what we have been waiting for */
				to_network_layer(&r.info);      /* pass the data to the network_layer */
				inc(frame_expected);            /* next time expect the other sequence nr */
			}
			s.ack = 1 − frame_expected;         /* tell which frame is being acked */
			to_physical_layer(&s);              /* send acknowledgement */
		}
	}
}


/* Protocol 4 (Sliding window) is bidirectional. */
#define MAX_SEQ 1		                    /*must be 1 for protocol 4*/
typedef enum {frame_arrival, cksum_err, timeout} event_type;
#include "protocol.h"
void protocol4(void)
{
	seq_nr next frame_to_send;                     /* 0 or 1 only */
	seq_nr frame_expected;                         /* 0 or 1 only */
	frame r, s;                                    /* scratch variables */
	packet buffer;                                 /* current packet being sent */
	event_type event;
	next_frame_to_send = 0;                        /* next frame on the outbound stream */
	frame_expected = 0;                            /* frame_expected next */
	from_network_layer(&buffer);                   /* fetch a packet from the network_layer */
	s.info = buffer;                               /* prepare to send the initial frame */
	s.seq = next_frame_to_send;                    /* insert sequence number into frame */
	s.ack = 1 − frame_expected;                    /* piggybacked ack */
	to_physical_layer(&s);                         /* transmit the frame */
	start_timer(s.seq);                            /* start_the timer running */
	while(true) {
		wait_for_event(&event);                    /* frame_arrival, cksum_err, or timeout */
		if(event == frame_arrival) {              /* a frame has arrived undamaged */
			from_physical_layer(&r);               /* go get it */
			if(r.seq == frame_expected) {         /* handle inbound frame stream */
				to_network_layer(&r.info);         /* pass packet to_network_layer */
				inc(frame_expected);               /* invert seq number expected next */
			}
			if(r.ack == next_frame_to_send) {     /* handle outbound frame stream */
				stop_timer(r.ack);                 /* turn the timer off */
				from_network_layer(&buffer);       /* fetch new pkt from_network_layer */
				inc(next_frame_to_send);           /* invert sender’s sequence number */
			}
		}
		s.info = buffer;                           /* construct outbound frame */
		s.seq = next_frame_to_send;                /* insert sequence number into it */
		s.ack = 1 − frame_expected;                /* seq number of last received frame */
		to_physical_layer(&s);                     /* transmit a frame */
		start_timer(s.seq);                        /* start_the timer running */
	}
}


/* Protocol 5 (Go-back-n) allows multiple outstanding frames. The sender may transmit up
to MAX_SEQ frames without waiting for an ack. In addition, unlike in the previous
protocols, the network layer is not assumed to have a new packet all the time. Instead,
the network layer causes a network_layer_ready event when there is a packet to send. */
#define MAX_SEQ 7
typedef enum {frame_arrival, cksum_err, timeout, network_layer_ready} event_type;
#include "protocol.h"
static boolean between(seq_nr a, seq_nr b, seq_nr c)
{
	/* Return true if a <= b < c circularly; false otherwise. */
	if(((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a)))
		return(true);
	else
		return(false);
}
static void send_data(seq_nr frame_nr, seq_nr frame_expected, packet buffer[])
{
	/* Construct and send a data frame. */
	frame s;                                                                           /* scratch variable */
	s.info = buffer[frame_nr];                                                         /* insert packet into frame */
	s.seq = frame_nr;                                                                  /* insert sequence number into frame */
	s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);                                /* piggyback ack */
	to_physical_layer(&s);                                                             /* transmit the frame */
	start_timer(frame_nr);                                                             /* start the timer running */
}
void protocol5(void)
{
	seq_nr next_frame_to_send;                                                         /* MAX_SEQ > 1; used for outbound stream */
	seq_nr ack_expected;                                                               /* oldest frame as yet unacknowledged */
	seq_nr frame_expected;                                                             /* next frame_expected on inbound stream */
	frame r;                                                                           /* scratch variable */
	packet buffer[MAX_SEQ + 1];                                                        /* buffers for the outbound stream */
	seq_nr nbuffered;                                                                  /* number of output buffers currently in use */
	seq_nr i;                                                                          /* used to index into the buffer array */
	event_type event;
	enable_network_layer();                                                            /* allow network_layer_ready events */
	ack_expected = 0;                                                                  /* next ack_expected inbound */
	next_frame_to_send = 0;                                                            /* next frame going out */
	frame_expected = 0;                                                                /* number of frame_expected inbound */
	nbuffered = 0;                                                                     /* initially no packets are buffered */
	while(true) {
		wait_for_event(&event);                                                        /* four possibilities: see event_type above */

		switch(event) {
			case network_layer_ready:                                                  /* the network layer has a packet to send */
			/* Accept, save, and transmit a new frame. */
				from_network_layer(&buffer[next_frame_to_send]);                       /* fetch new packet */
				nbuffered = nbuffered + 1;                                             /* expand the sender’s window */
				send_data(next_frame_to_send, frame_expected, buffer);                 /* transmit the frame */
				inc(next_frame_to_send);                                               /* advance sender’s upper window edge */
				break;
			case frame_arrival:                                                        /* a data or control frame has arrived */
				from_physical_layer(&r);                                               /* get incoming frame from_physical_layer */
				if(r.seq == frame_expected) {
				/* Frames are accepted only in order. */
					to_network_layer(&r.info);                                         /* pass packet to_network_layer */
					inc(frame_expected);                                               /* advance lower edge of receiver’s window */
				}
				/* Ack n implies n − 1, n − 2, etc. Check for this. */
				while(between(ack_expected, r.ack, next_frame_to_send)) {
				/* Handle piggybacked ack. */
					nbuffered = nbuffered − 1;                                         /* one frame fewer buffered */
					stop_timer(ack_expected);                                          /* frame_arrived intact; stop_timer */
					inc(ack_expected);                                                 /* contract sender’s window */
				}
				break;
			case cksum_err: break;                                                     /* just ignore bad frames */
			case timeout:                                                              /* trouble; retransmit all outstanding frames */
				next_frame_to_send = ack_expected;                                     /* start retransmitting here */
				for (i = 1; i <= nbuffered; i++) {
					send_data(next_frame_to_send, frame_expected, buffer);             /* resend frame */
					inc(next_frame_to_send);                                           /* prepare to send the next one */
				}
		}
		if(nbuffered < MAX_SEQ)
			enable_network_layer();
		else
			disable_network_layer();
	}
}