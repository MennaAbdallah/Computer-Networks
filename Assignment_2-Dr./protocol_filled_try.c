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
/* Wait for an event to happen; return its type in event. */
void wait_for_event(event_type * event)
{
	while(event!=frame_arrival|| event!=cksum_err|| event!=timeout|| event!=network_layer_ready);
	
}
/* Fetch a packet from the network layer for transmission on the channel. */
void from_network_layer(packet * p)
{
	//assume getting input from user command line
	cout<<"please enter packet from upper layers"<<endl;
	cin>>p;
	// to be sent to link layer
	
}
/* Deliver information from an inbound frame to the network layer. */
void to_network_layer(packet * p)
{
	frame temp;
	from_physical_layer(&temp);
	p=temp.info;
}
/* Go get an inbound frame from the physical layer and copy it to r. */
void from_physical_layer(frame * r)
{
	cout<<"please enter frame received during transmission"<<endl;
	cout<<"enter frame kind"<<endl;
	cin>>r->kind;
	cout<<"enter frame seq"<<endl;
	cin>>r->seq;
	cout<<"enter frame ack"<<endl;
	cin>>r->ack;
	cout<<"enter frame data"<<endl;
	cin>>r->data;
	// to network 
}
/* Pass the frame to the physical layer for transmission. */
void to_physical_layer(frame * s)
{
	// assume it's received on command
	cout<<"frame kind ="<<s->kind;
	cout<<"frame seq ="<<s->seq;
	cout<<"frame ack ="<<s->ack;
	cout<<"frame data ="<<s->data;
}
/* Start the clock running and enable the timeout event. */
static clock_t end_t=0;
static clock_t start_t=0;
void start_timer(seq_nr k)
{

	// assume timer is equal 1000
	seq_nr timer=end_t-start_t;
	start_t=clock();
	if(timer>1000)
	{
		event_type event=timeout;
		wait_for_event(&event);
		//timeout;
		//resend
	}
}
/* Stop the clock and disable the timeout event. */
void stop_timer(seq_nr k)
{
	end_t=clock();
}
static clock_t end_t_ack=0;
static clock_t start_t_ack=0;
/* Start an auxiliary timer and enable the ack timeout event. */
void start_ack_timer(void)
{
	// assume timer is equal 200
	seq_nr timer=end_t_ack-start_t_ack;
	start_t_=clock();
	if(timer>200)
	{
		event_type event=ack_timeout;
		wait_for_event(&event);
		//timeout;
		//resend
	}	
}
/* Stop the auxiliary timer and disable the ack timeout event. */
void stop_ack_timer(void)
{
		end_t_ack=clock();

}
/* Allow the network layer to cause a network layer ready event. */
void enable_network_layer(void)
{
	event=network_layer_ready;
}

/* Forbid the network layer from causing a network layer ready event. */
void disable_network_layer(void)
{
	goto l1;
}
/* Macro inc is expanded in-line: increment k circularly. */
#define inc(k) if(k < MAX_SEQ) k = k + 1; else k = 0
