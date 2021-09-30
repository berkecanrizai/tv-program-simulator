Firstly, all of the parts (1, 2, logging) are working properly.

1-2) Here, we initialize gettimeofday. We then initialize the values we have taken with arguements.
We created tvQueue which is the queue for commentors with the size of commentors*q*2 to make sure 
enough room is existing. We then opened threads for each commentor and called commentor method for
each, did same thing for moderator and observer. In the main, we look if there will be event generated,
for every second with probability.
	In the moderator, if there is no question currently, we locked all the commentors with mutex_lock
moderator checks if there is event and if no asks a question. In a while loop moderator waits for commen-
tors to make their decisions for answering. Then for each commentor in the tvQueue which holds current 
commentors willing to speak, at each one waits if currently commentor is talking and after that unlocks the
lock of the next commentor on the queue, pops them and that commentor is speaking. After all commentors in
queue has spoken, locks of each commentor is unlocked so that they can make their decision for the next 
question.
	Commentor waits for questions to be asked in a while. With rand() commentor decides with probability,
p if they will answer and adds themself to list if so, we used lock here so that that two distinct commentors
do not try to modify list at the same time. It controls if there is event and doesn't speak if so. If it is 
time for commentor to speak then they speak and if all commentors had their turns to speak this doesn't execute.
	Observer checks for event and if there is, it cancels the sleep of commentor that is currently speaking 
with the pthread_cond_timedwait and that commentor is cut short, we also logged that. It locks the event mutex
and everyone waits for that mutex to be unlocked. 

3) This was the by far easiest one to make since we half implemented logs (such as prints etc.)
in order to bugfix and see if everything is working as intended. Whenever moderator creates a
question we log it with the relative time to start. Relative time is implemented as we store the
start of the program as long long type structure with the getTime() method as miliseconds. Whenever
we try to log some event we deduct the event time from the start time and with some modification,
we show it as min:sec:msec format in the left side. Whenever commentor generates comment and speaks,
we also logged them. If breaking news occur, it is logged as print. When breaking news end, it is 
logged and also if commentor is cut, it is also written.