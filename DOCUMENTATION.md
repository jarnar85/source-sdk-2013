# Documentation for all the changes includes in this modification of the Source SDK

## Change AI-relationships

This command needs sv_cheats to be active.
The result will be that you will get the same relationship to all NPCs as the class given as a parameter.
Your allies will get a similar (but not the same) relationship as well.

### COMMAND
player_setrelation <AI_CLASS>

### AI_CLASS
The class name can be any internal class name used for the relationship table
Here are some examples:
* CLASS_COMBINE
* CLASS_ZOMBIE
* CLASS_CITIZEN_REBEL
* CLASS_MANHACK

## Change player class

This command needs sv_cheats to be active.
The result will be that you will get assigned a class.
This modifies the AI-relationships and health (TODO: change model as well)

### COMMAND
player_setclass <PLAYER_CLASS>

### PLAYER_CLASS
Can be one of the following:
* player
* citizen
* rebel
* manhack
* metropolice
* combine_guard
* combine_soldier
* combine_elite
* stalker
* zombie
* zombie_poison
* zombie_fast
* zombie_combine
