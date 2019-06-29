## Objectives

Modify the Source SDK in such a way that I might be able to create a long time mod idea I've been carrying around in my head.
For this it's necessary to implement some RPG characteristics into the game engine

## To-Do

* AI relationships
	* [x] create command player_setrelation <AI_CLASS> to change the players relationship
	* [ ] Further optimizations to make it easier to change the settings (maybe load initially from database?)
	* [ ] Save changed relationship in usual save files
* World
	* [ ] Make an easy way to add variables that are updated while exiting a map (eg. number of combine killed, a mini game score, number of items of some sort collected, ...)
* Player
	* [ ] Make it possible to select a character in the new game dialog
	* [ ] Make the starting map and difficulty dependent on the selected character
	* [ ] Create a trigger that can do different stuff depending on the type of player death (eg. stun stick knocks you out and sends you to prison)
	* [x] create command player_setclass <PLAYER_CLASS> to change the players class (job/faction)
		* [x] Change player model (and hands)
			* [ ] Create better alternative models
		* [x] Change relationship
		* [ ] Change HUD depending on class
			* [ ] Set HUD color depending on class
			* [ ] Add overlay for certain classes (combine/metropolice)
		* [ ] Change character values based on class
			* [x] Health
			* [ ] Armor
			* [ ] Suit
	* [ ] Create player_class <PLAYER_CLASS> (using player_setclass functionality without cheat protection and fiter of available target classes depending on current class eg. combine become zombine and not classic zombies)
* [ ] Create a test map
	* [ ] Add a trigger for player_setclass command
	* [ ] Add a trigger to spawn certain NPCs (combine, rebel, zombie, ...)
* [ ] create a [documentation](DOCUMENTATION.md) for the changes
	* [x] Add player_setclass command

## Legal notices

Please read the [read me](README), [license](LICENSE) and [third party legal notices](thirdpartylegalnotices.txt) for the original legal notices and license