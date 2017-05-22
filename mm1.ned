// *** mm1.ned ***
simple Generator {
parameters:
	volatile double interArrivalTime; // sec
	@display("i=block/source");
gates:
	output out;
}
 
simple Queue {
parameters:
	volatile double serviceTime; // sec
	@display("i=block/queue");
gates:
	input in;
	output out;
}
 
simple Sink {
parameters:
	@display("i=block/sink");
gates:
	input in;
}
 
network MM1 {
submodules:
	gen: Generator{
		@display("p=273,101");
        }
	queue1: Queue{
                @display("p=165,79");
        }
    queue2: Queue{
                @display("p=165,120");
        }
	sink: Sink{
                @display("p=50,79");
        }
connections:
	gen.out --> queue1.in;
	queue1.out --> queue2.in;
	queue2.out --> sink.in;
}
