## Objectives

Modify the Source SDK in such a way that I might be able to create a long time mod idea I've been carrying around in my head.
For this it's necessary to implement some RPG characteristics into the game engine

## To-Do

* AI relationships
	* [x] create command player_setclass <CLASS_NAME> to change the players relationship
	* [ ] Further optimizations to make it easier to change the settings (maybe load initially from database?)
	* [ ] Change player model (and hands) on change of relationship
	* [ ] Add overlay for certain classes (combine/metropolice)
	* [ ] Save changed relationship in usual save files
* World
	* [ ] Make an easy way to add variables that are updated while exiting a map (eg. number of combine killed, a mini game score, number of items of some sort collected, ...)
* Player
	* [ ] Make it possible to select a character in the new game dialog
	* [ ] Make the starting map and and difficulty dependent on the selected character
	* [ ] Create a trigger that can do different stuff depending on the type of player death (eg. stun stick knocks you out and sends you to prison)
* [ ] Create a test map
	* [ ] Add a trigger for player_setclass command
	* [ ] Add a trigger to spawn certain NPCs (combine, rebel, zombie, ...)
* [ ] create a [documentation](DOCUMENTATION.md) for the changes
	* [x] Add player_setclass command

## Legal notices

Please read the [read me](README), [license](LICENSE) and [third party legal notices](thirdpartylegalnotices.txt) for the original legal notices and license