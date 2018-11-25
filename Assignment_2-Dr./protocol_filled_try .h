#define MAX_PKT 1024                                   /* determines packet size in bytes */
typedef enum {false, true} boolean;                    /* boolean type */
typedef unsigned int seq_nr;                           /* sequence or ack numbers */
typedef struct {unsigned char data[MAX_PKT];} packet;  /* packet definition */
typedef enum {data, ack, nak} frame_kind;              /* frame_kind definition */
typedef struct {                                       /* frames are transported in this layer */
	frame_kind kind;                                   /* what kind of frame is it? */
	seq_nr seq;                                        /* sequence number */
	seq_nr ack;                                        /* acknowledgement number */
	packet info;                                       /* the network layer packet */
} frame;
static clock_t end_t=0;
static clock_t start_t=0;
static clock_t end_t_ack=0;
static clock_t start_t_ack=0;
/* Wait for an event to happen; return its type in event. */
void wait_for_event(event_type * event);
/* Fetch a packet from the network layer for transmission on the channel. */
void from_network_layer(packet * p);
/* Deliver information from an inbound frame to the network layer. */
void to_network_layer(packet * p);
/* Go get an inbound frame from the physical layer and copy it to r. */
void from_physical_layer(frame * r);
/* Pass the frame to the physical layer for transmission. */
void to_physical_layer(frame * s);
/* Start the clock running and enable the timeout event. */
void start_timer(seq_nr k);
/* Stop the clock and disable the timeout event. */
void stop_timer(seq_nr k);
/* Start an auxiliary timer and enable the ack timeout event. */
void start_ack_timer(void);
/* Stop the auxiliary timer and disable the ack timeout event. */
void stop ack timer(void);
/* Allow the network layer to cause a network layer ready event. */
void enable_network_layer(void);
/* Forbid the network layer from causing a network layer ready event. */
void disable_network_layer(void);
/* Macro inc is expanded in-line: increment k circularly. */
#define inc(k) if(k < MAX_SEQ) k = k + 1; else k = 0
