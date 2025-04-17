This was a scholl assignment that i did with a partner

To run the SPLand Simulation (os has to be linux):

Build the project
Run make from the root directory.
This will compile the code and place the executable in the bin/ folder.

Run the simulation
Use the following command:
./bin/simulation path/to/config.txt

Replace path/to/config.txt with the path to your configuration file.

Use the following commands inside the simulation:

step <number>

Run the simulation for the given number of steps (time units).

plan <settlement_name> <selection_policy>

Add a new reconstruction plan to a settlement.

Selection policies:

nve: Naive

bal: Balanced

eco: Economy

env: Sustainability

settlement <name> <type>

Add a new settlement. Types:

0: Village

1: City

2: Metropolis

facility <name> <category> <price> <life_score> <eco_score> <env_score>

Add a new facility type to the simulation.

planStatus <plan_id>

Print the status of a specific plan, including scores and facilities.

changePolicy <plan_id> <new_policy>

Change the selection policy of an existing plan.

log

Print the history of all user actions and their result (completed/error).

backup

Save a snapshot of the current simulation state.

restore
Restore the last saved snapshot. Errors if no backup exists.

close
Print final results for all plans and exit the simulation.
