# NetworkLabAssignments


This repository contains the different assignments done as a part of Computer Networks Course taken in Jadavpur University.

The assignments are :

* Assignment1 : It contains implementation of basic error detection schemes such as LRC, VRC, Checksum and CRC and sending and receiving data-frames by IPC. 
The implementation involves the use of MemoryMappedByteBuffer in Java for IPC and connecting sender and receiver.

* Assignment2 : It contains implementation of various flow control algorithms such as Stop and Wait, GobackN and Selective Repeat. The simulations are done by multithreading
and communication between sender and receiver threads are achieved through a modified ArrayBlockingQueue in Java ( here ArrayBlockingList ). For timing different packets
DelayQueue in Java was of a great use.

* Assignment3 : It contains the simulation of CSMA protocol. The simulation consists of generating multiple frames with a random generator function. The protocol has simulations for it's three schemes such as persistent CSMA, non-persistent CSMA and p-persistent CSMA. The channel is sensed and collision is calculated by furthur calculating propagation time and transmission time and comparing them. Upon collision, the frames are delayed by a exponential back-off time calculated randomly.

* Assignment 4: CDMA
