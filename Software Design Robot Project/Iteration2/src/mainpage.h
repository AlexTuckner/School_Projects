/*
 * @copyright 2017 Alex Tuckner, All rights reserved.
 */

/*! \mainpage CSCI3081 Player Simulator Project
 *
 * \section Design Document


    This program consists of a player game in which the user attempts stop all
 robots, by colliding with them, before running out of battery.
The initial place to look for the design in this code is in the
GraphicsArenaViewer. The GraphicsArenaViewer class contains all of the
general gui objects including the player and obstacles, as well as the
buttons and window.  The one thing to note about this design is that all
of the objects have no knowledge of this class, and the rest of the
classes such as arena are only called in this class.  This idea of keeping the
graphics and the objects separate is a good design principle
because it simplifies the code at each step of the way and allows for more
readability throughout.  The arena viewer gets most of its data from the arena,
which is the backbone of the entire project.

	The next place to look for design principles is in the arena.  The arena
contains every object within it including players and obstacles, and updates the
time for each object.  The arena is the most important class in this program as
it is responsible for advancing the time, updating the entities, and checks for
all events that occur between objects within the arena.  The arena is used to dictate
all of the information between these objects.  For example, when two objects
collide, the arena is responsible for deciding if there was a collision, then
sends the proper response to the sensors of the entities that collided. These
sensors then are checked at each TimestepUpdate for the mobile entities, and
when activated, is sent to the motion handler to react accordingly. Another
responsibility of the arena is to receive the input from the user through the
eventcommand class and forward that input to the player to adjust its
angle or speed.  While the arena holds all of this power, the game would
still not be possible without the player itself.

	The Player class is the class in which the player is defined.  It is derived
from the ArenaMobileEntity class which is in turn derived from the ArenaEntity
class.  This design of the player uses inheritance to obtain many of its values
from the classes above it.  In this game, the player contains a battery, speed,
heading angle, and inherits a collision delta for the situation in which it
collides. The Player contains a motion handler, that the player sends events to
every time it receives an event from the arena.  This event will inform the
player that it has collided, and thus uses to the motion handler to react
according to the angle of inflection from the point of contact between objects.

	Overall, the design of this program is pretty good, although there are still
a few flaws within.  One flaw is that the initial arena_mobile_entity class
contained an EventRecharge object which was used to refill the battery if the
player collided with the recharge station.  This value being only a part of the
player class, should have been put in the player class because when we tried to
make the home_base mobile, it was trying to inherit this function that did not
apply to it.  A good principle of this design is that it attempts to separate
the code into many classes.  These classes may only contain a few lines of code,
but each is necessary to the completion of the project.  This simplifies the
code and encapsulates objects from one another to keep their data separate and
ensure no class becomes all-powerful.

 *
 *
 */
