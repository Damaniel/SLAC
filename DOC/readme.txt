==================================================
Secret Legacy of the Ancient Caves (SLAC) - README
==================================================

Introduction
---------------

You're an accomplished adventurer who's decided to retire to a small town and 
raise a family.  The town is rumored to harbor a secret related to the 
mysterious dungeons scattered throughout.  The first has apparently drawn
many adveuturers, many of whom never returned.  The others are locked by
magical gates; nobody knows what's contained within them.  Some people say
that if you listen long enough, the screams of ancient beasts can be heard 
deep below.  

One day, the call of adventure beckons, and you decide to come out of
retirement in an attempt to help solve the mystery of the town.  While you
know very well that adventuring entails risks, the spirit of adventure also
flows through your family's veins - you know that even if you fail in your 
attempts, your heirs will no doubt continue where you left off. 

Overview
---------------

SLAC is a mostly traditional roguelike with a simple metaprogression system; 
when your player dies, their heir takes over.  While the new generation of
player has no equipment or money, they can take advantage of any artifacts
found by previous generations of players; these stackable items provide small
boosts to the stats of all adventurers of future generations.  With 3 dungeons
and over 200 enemies to fight, you'll need all the help you can get!

System Requirements
-------------------

SLAC requires the following hardware/software:

- a 386 or higher (486 recommended)
- 2MB of RAM (4MB recommended)
- MS-DOS 5.0 or higher, or FreeDOS
- VGA capable of Mode-X (though nearly all are)
- a keyboard; preferably one with a number pad

Controls
----------------

Movement (cardinal directions):
    Up Arrow - move up
    Down Arrow - move down
    Left Arrow - move left
    Right Arrow - move right
    / - stand still for one turn

Movement (including diagonals):

If you have a keyboard with a numpad (and Num Lock on), the following movement
controls can also be used:

    7 - move up and to the left
    8 - move up
    9 - move up and to the right
    4 - move left
    6 - move right
    1 - move down and to the left
    2 - move down
    3 - move down and to the right
    . - stand still for one turn

Action keys
    - Space bar / Enter - performs context sensitive actions
      (this includes picking up items or using stairs)
    - < | > - Moves down or up stairs, respectively
    - G - picks up an item from the floor
    - C - displays the player's stats
    - M - displays a map of the current floor
    - S - manually save the game
    - I - display the inventory

Using the inventory
    - Arrow keys - move between items
    - Enter - bring up the context menu for the selected item
    - Esc - return to the game

The context menu contains options specific to items. These include:
    - Use (for potions and scrolls)
    - Equip / Unequip (for equipment)
    - Drop
    - Delete

The Drop option puts the item on back on the dungeon floor (note that Drop
doesn't work in town).

The Delete option destroys the item permanently.

Some options can't be used with some items.  In those cases, the relevant 
option will be displayed in a darker color and can not be selected.

In most menus/dialogs, the Esc key will exit that menu.  

Artifacts
-------------

Artifacts are items that can be occasionally found in the dungeon.  Each of 
the different artifacts provides small boosts to one or more stats, and the
player can collect any number of each as they explore.  Any artifacts that are
on you at the time of your death are added to your total artifact pool; the 
combined stats from this pool are added to each future generation of player,
increasing passive power over time.  

Artifacts come in 3 broad categories:
    - Single part: each one of these provides a small stat boosts.
    - Multi-part:  each one of these provides a larger stat boost, but only
                   if you've collected enough parts.
    - Multi-generation: much like mutli-part artifacts but they provide the
                   largest boosts.  Unlike multi-part artifacts, a player
                   can only collect at most one per generation.

When the current player dies, a summary will be displayed on screen that shows
what bonus stats the next player will receive.  

The museum in town (TBD) will have a display showing each artifact you've 
found, how many you've found, and how much in passive bonuses that the 
artifact(s) are providing. 

Shops
------------

TBD.  

Dungeons
------------

There are 3 dungeons in the game - the Dusty Tunnels, the Marble Halls, and 
the Crystal Depths.  The latter two are locked by a magical gate; perhaps you
can find keys somewhere in the dungeons.  The Dusty Tunnels consists of 25
floors; as to the other dungeons - you'll figure it out as you go.

License and Attributions:
-------------------------
Copyright 2025 Shaun Brandt

SLAC is open source software, provided under the MIT license.  See LICENSE for
more details.

The game uses the DawnBringer 16 color palette by DawnBringer.

The majority of the graphics tiles come from the DawnLike tileset by 
DragonDePlatino.
