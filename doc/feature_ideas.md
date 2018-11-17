# Base Features

## Areas
The game should contain areas with a name, some descriptive text about it, some connected other areas, 
and some objects contained in the area.
  
## Flags
There should be some flags that the player has (simple booleans), that can be acquired in some ways.
Perhaps by simply entering an area, perhaps by performing specific actions in the area.

## Movement
The player should be able to move between areas that are connected through entering some command. Some 
connections should be locked off until the player has the appropriate flags.

## NPCs
There should be NPCs populating the areas, which the player should be able to talk to (could also be 
flag-dependant).

## Items
The player should be able to get items, either as rewards for quests, or in other ways not thought of yet.
The player should have an inventory where these items are contained, which should be able to be viewed at 
all (appropriate) times. Each item should have at least some basic description of what it is, with ideas 
of maybe a Dark Souls-like description providing some history or lore about more than just the item in question.

## Journal
No quests should automatically be added to the journal, but the player should be able to simply write in his 
own journal to define the quests himself. This means that the journal needs to be available at all appropriate 
times (probably with the same requirements as opening the inventory), where it would make sense for the player 
character to pull out his notes and read through them.

# Extra Features

## Minimap
A minimap that shows the basic layout of the current area could be added for each area, or some important areas.
This space could also be used for some pixel-art characters whenever talking to an NPC.

## Combat
Support for combat could be a good use of items. However, the combat part should not take all the development time, 
as the main goal is to be able to tell a story, not make a mob-grinding game. Could be cool to have though, for boss 
fights or similar.  
If implemented, the language for writing the combat should preferrably be flexible enough to give the creator some 
more freedom than just deciding mobs and the stats such as:
* Messages based on mob health
* Messages based on player health
* Switching to another combat scene at some health
* Switching to another combat scene after some amount of turns

# Other ideas

## Fast Lookup
For fast lookup of areas in the game, instead of checking the entire file for the wanted area, the game can 
keep a list of all the areas in the game. This list would contain the file path for the area, and the byte in 
the file at which the area begins. Then the program would only need to read the file from this byte until an 
entire area fitting the grammar has been read, and this would reduce lookup times when there is a large amount of
areas.

