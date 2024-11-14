# philosophers
A Hive Helsinki school project. Keywords: C, Concurrent programming, Multithreading, Multiprocessing.<br />
<br />
The goal: <br />
Keep alive a party of philosophers. <br />

The general rules:<br />
• One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.<br />
• The philosophers alternatively eat, think, or sleep. While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.<br />
• There are also forks on the table. There are as many forks as philosophers.<br />
• Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.<br />
• When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.<br />
• Every philosopher needs to eat and should never starve.<br />
• Philosophers don’t speak with each other.<br />
• Philosophers don’t know if another philosopher is about to die.<br />
• No need to say that philosophers should avoid dying!<br />

The specifics:<br />
• Each philosopher should be a thread.<br />
• There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.<br />
• To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.<br />

