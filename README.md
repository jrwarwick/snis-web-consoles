# SNiS Client Bridge/proxy over HTTP

Allow for fancy "mobile-first/responsive" html5 client UI (but with limited control options, depends on what the speech bridge already can do) 
so ipads and phones can easily get into the mix, plus if we do a good job with good-practices CSS,
we get easy-ish reskinning of those clients (LCARS, anyone? then a quick switch to Star Wars/Craft/Etcetera)

Mostly we just try to inject into /tmp/snis-natural-language-fifo, a named pipe which the client reads from, stuff the reflects what such a button would mean to do.

Interesting side-note: each game client's hostname suddenly becomes a potential URL. Or this could be running only on the server.

## Setup
ln -s /var/www/html/LCARS/git/lcars/lcars/audio/ ./sound


## ToDo:

### main index.html that is also a menu 
that lists all the client interfaces in a nice layout.

also maybe some fun/cool QR code , Chirp, TTS, IRC/XMLPP broadcasts etc to announce the "client ui" URL.

### manifest.json & favicon stuff
<link rel="icon" type="image/png" href="/image.png">
more in depth read of Google's PWA specs.

### Skins
CSS / template based approach.
 - SNiS
 - Last Parsec
 - LCARS:TNG
 - Artemis
 - Skeuomorphic things?: Star Wars-ish

### audio
howler.js
sym link game assets (/usr/local/share/snis/sounds ?)
naming/mapping/method(s)? (which might include some kind of respect for css classes)

### LARPy/BlinkenLights/Greebleisticness
Maybe some (optional) buttons and switches and "data read-outs" that do not actually have any game function whatsover.
but look kinda cool. With graphs, animations and so on.
	For Navigation: "INTERTIAL DAMPING COMPENSATOR LOAD: 12 N [ 1.3G @ 727j ]" "GRAVITATIONAL WELL MAP"
	For Engineering & DamCon & Science:  Life Support "ATMOSPHERIC MIXTURE SPECTRAL ANALYSIS: [ 72 12 6 4 ] , BAROMETRICS [      |  x |  ]
	For Communications:  "INTERFERENCE MODULATOR PARAMETERS: [ 1273.23 887 3212.222 ]" "EMF PATTERN RECOGNIZER ALGORITHMS: QRF-Z (ALT7) XR3X"
maybe also a few actually kinda useful utilities, even though not strictly "game stuff". E.g., mini-SPA-app-features for: stopwatch/timer, calculator, rot13/viognere "decryptor",

### Game data from server
another bridge? the same one? funky websockets implementation to "directly" get info from server (direct to webbrowser, that is)
map-like things, messages (perhaps daemon/GM messages to captain particuarly)


## Screens
(from https://smcameron.github.io/space-nerds-in-space/#controls)

F1 is the help screen. What it displays depends on which screen you're on.
F2 - NAVIGATION
F3 - WEAPONS
F4 - ENGINEERING
F5 - DAMAGE CONTROL
F6 - SCIENCE
F7 - COMMUNICATIONS
F8 - MAIN SCREEN
F9 - DEMON SCREEN (dungeon master screen)
-- plus synthetic and/or secondary screens:
Commander /XO
Captain /CO
Cartography/Library


### Navigation Controls
use the following keys to steer the ship:

           Q   W   E                ^
                                    |
           A   S   D          <-        ->
                                    |
                                    V
- yaw the ship left and right, respectively.
- pitch the ship down (forward) and up (back), respectively. (If you want to invert these, press Ctrl-I).

- position of the camera in the 3D view, moving it closer or farther from the ship. Press it multiple times to cycle through several possible camera positions.
+ and - (plus and minus) and the mouse scroll wheel control the camera zoom level.

- The vertical slider control on the upper right hand side of the screen is the ship's throttle. Use this to control how fast the ship moves.
- The R button above the throttle slider toggles the ship into or out of reverse thrusting.

- The horizontal slider control below the warp drive controls how much power the warp drive uses. 
	To use the warp drive, set the warp drive control slider to the desired level, wait until the warp drive gauge reaches the desired value, and press the 
- ENGAGE WARP button. Set the warp drive power to zero when not in use to conserve power

- Press the DOCKING MAGNETS button to engage the docking system. (to disengage the docking system press it again.)
	To disconnect from the station, press the DOCKING MAGNETS button again.

- Use the STANDARD ORBIT button when near a planet to enter "standard orbit".

- The COMPUTER button allows you to ask the computer to do something. You can control most aspects of the ship in this way. For example, you can type in "navigate to the nearest starbase", and it should point your ship in the direction of the nearest starbase.

TODO: data from server
 - The GREEN ARROW on the screen points in the direction of whatever entity the SCIENCE OFFICER has selected for scanning. NAVIGATION OFFICER can follow the GREEN ARROW
 - The CYAN ARROW indicates which direction the weapons are currently pointed. Note that the weapons are mounted on top of the ship, and cannot fire on anything beneath the plane parallel to the floor of the ship.



### Weapons Screen Controls
The mouse controls where the guns are pointed. The guns can yaw left and right and pitch up and down, but cannot roll.
When the mouse is at the bottom center of the screen, the guns will be pointed straight ahead.
Moving the mouse from the bottom to the top of the screen moves the guns through the full range of pitch.
Moving the mouse to the left side of the screen to the right side of the screen moves the guns through the full range of yaw. (Note: Using the arrow keys, you can also yaw and pitch the guns. With the arrow keys, the yaw range is not limited (guns can rotate 360 degrees. This discrepancy could be considered a bug.)
The Left mouse button and the SPACE BAR fire the phasers.
The Right mouse button and the Z key fire torpedoes.
The mouse scroll wheel or the + and - (plus and minus) keys control the WAVE LENGTH of the phasers. The SCIENCE OFFICER can use the ships scanners to determine what is what the most effective value for the wave length is for a given enemy.
The CHARGE graph shows how much power will be released in the next phaser shot. It takes some time for the phasers to recharge. Firing rapidly means each shot contains less energy and does less damage (but if you miss, you will have wasted less energy.) If the phasers are damaged, or ENGINEERING has diverted power from the phasers, it may take longer to recharge.

### Damage Control Controls
Use the Arrow Keys or W, A, S, D keys to control the movement of the robot.
Use the Space Bar to control the robot's gripper.
The screen shows each of the systems on the ship, with each system having three components. The components may become damaged, making the systems less effective.
To repair a component, maneuver the robot near the component and use the gripper to pick up the component. If the component is not too badly damaged, the robot will repair it right there. After the component is repaired, operate the gripper to put the component back.
Note, you must put components back in the correct slots for them to work correctly, otherwise the systems will not operate well.
If a component is too badly damaged, you will need to take the component to the repair station located at the bottom. Put the component into one of the slots on the repair station and wait a moment for it to repair. You can pick it up before it is fully repaired and repair it to completion on the way back to replace the component in its slot in the appropriate system.
If you do not have enough players, or if you simply do not want to manually repair the ship, you can press the AUTO button, and the robot will autonomously repair the ship by itself. It probably won't do it as quickly as you could do it manually though.

### Science
#### SRS
Science Short Range Scanner Controls
The Mouse Scroll Wheel or the RANGE slider control at the top of the screen controls the range (distance) of the short range scanner.
The Left and Right Arrow keys or the A and D keys control the direction the scanning beam is pointed. The boundaries of the scanning beam is indicated by two flickering lines on the display.
The Up and Down Arrow keys or the W and S keys control the scanning beam width. The wider the beam is the more volume it covers, but the less resolution it has. The narrower the beam is, the less volume it covers, but the more resolving power it has.
Items in the scanner are displayed at a distance from the center which corresponds to the 3D distance.
When the scanner has resolved an entity, you can click on it with the mouse, and it, and nearby resolved entities will "pop up" out of the display to give you an idea of how they are situated in 3D space.
#### Details
Science Details Screen
Once an entity is resolved by the scanner and selected, you can press the DETAILS button to see more details about the selected item. What you see depends on the type of the item.
The Warp Factor value gives you an idea of what value to use if you wish to travel to the entity via the warp drive (that is, you may want to relay this information to the NAVIGATION OFFICER.)
If the entity is a ship, the SHIELD PROFILE may indicate that some phaser frequency might be especially effective (so you may want to relay this information to theWEAPONS OFFICER.)
#### LRS
Long Range Scanner Controls
The long range scanner is useful for locating distant planets and starbases. It shows a 3D view of the space around your ship.

The Mouse Scroll Wheel or the RANGE slider control at the top of the screen controls the range (distance) of the long range scanner.
The Left and Right Arrow keys or the A and D keys control the direction the scanning beam is pointed. The boundaries of the scanning beam is indicated by two orange dotted lines on the display forming a kind of "orange slice".
The Up and Down Arrow keys or the W and S keys control the scanning beam width. The wider the beam is the more volume it covers, but the less resolution it has. The narrower the beam is, the less volume it covers, but the more resolving power it has.
The comma, and forward slash keys rotate (yaw) the scanned volume sphere to the left or right, respectively.
The period and L keys rotate (pitch) the scanned volume sphere down and up, respectively.
The K and semicolon keys rotate (roll) the scanned volume sphere counter-clockwise and and clockwise, respectively.
The ALIGN TO SHIP button aligns the view with the ship so that the view is as if from behind the ship with the ship facing forwards and up is up, left is left, right is right, etc.

### Communications
The row of buttons at the top is for the COMMS OFFICER to control what is displayed on the MAIN SCREEN. For this to work best, individual player stations should not have the MAIN SCREEN ROLE checked (on the NETWORK SETUP SCREEN when they joined the game) but only the computer attached to the projector or big TV should have the MAIN SCREEN role checked. Essentially these buttons make all terminals that have the MAIN SCREEN role switch to displaying the selected station instead. The idea behind this comes from Captain Picard's command, "On screen!" The captain can command any station's screen be displayed "On Screen!" and the COMMS OFFICER can "make it so". Note: it is also possible for any player to press Ctrl-O on their station to make their screen be displayed on the main screen. If they press Ctrl-O a second time, the main screen reverts to showing the main view out the window into space. So if the captain orders "Weapons, On Screen!", either the Weapons Officer can press Ctrl-O, or the Comms Officer can press the WEAPONS button on the COMMS screen. Again, if players have the "MAIN SCREEN" role checked when they join the game, it can be a bit confusing, because then their own computer will be considered to be a "main screen". In general, there normally should only be one computer per bridge that joins the game with the MAIN SCREEN role enabled, and that computer should be the one connected to a projector.

The "EMF" chart in the upper right shows a measuring of local EMF. When an NPC ship scans the players ship, this chart will show elevated levels of EMF. This can give a heads up that some ship is scanning you, and an attack might be coming soon.

The MAIN SCREEN button in the lower right portion of the screen makes the last 4 lines received appear on the main screen so everyone can see them.

The RED ALERT button toggles the red alert system on and off.

The shields display is there so the COMMS officer can know if a request to dock will be denied due to shields still being up.

The zoom slider control at the bottom of the screen controls the zoom level of the MAIN SCREEN

So what can Comms do with this terminal interface? First of all, anything which is typed in that is not a command is broadcast on the current channel, which is by default channel 0, which all player ships receive. You can also switch channels, and only player ships tuned to the particular channel will receive those messages. The intent here is for player-to-player chat in a multi-bridge setup. The channel system is also used (implicitly) for communications with starbases and with mining bots.

Commands you can type in are preceded with a slash, '/', along the lines of IRC commands.

    /help -- displays a list of commands (I need to update the help screen)
    /computer ",
    /channel channel-number - change current channel",
    /eject cargo-bay-number - eject cargo",
    /hail ship-name - hail ship or starbase on current channel",
    /inventory - report inventory of ship's cargo hold",
    /passengers - report list of passengers
    /about - report information about the game (i.e. version number, etc.)
Of the above, /hail, and /computer are the most powerful.

/hail is how you communicate with starbases to request permission to dock, or other things that starbases do (not all of which are implemented yet):

    LOCAL TRAVEL ADVISORY
    REQUEST PERMISSION TO DOCK
    BUY WARP-GATE TICKETS
    REQUEST REMOTE FUEL DELIVERY
    BUY FUEL
    REPAIRS AND MAINTENANCE
        BUY SHIELD SYSTEM PARTS
        IMPULSE DRIVE PARTS
        BUY WARP DRIVE PARTS
        BUY MANEUVERING PARTS
        BUY PHASER BANKS PARTS
        BUY SENSORS PARTS
        BUY COMMUNICATIONS PARTS
        BUY TRACTOR BEAM PARTS
    ARRANGE TRANSPORT CONTRACTS
        BUY CARGO
        SELL CARGO
        BOARD PASSENGERS
        DISEMBARK PASSENGERS
        EJECT PASSENGERS
    SIGN OFF
You may /hail other player ships, or mining bots. The mining bots have some functionality accessed via comms:

    STATUS REPORT
    RETURN TO SHIP
    TRANSPORT ORES TO CARGO BAYS
    STOW MINING BOT
    RETARGET MINING BOT
    SIGN OFF
If you aren't sure of the name of the mining bot, you can ask the SCIENCE OFFICER to scan it.

The /computer command is the most powerful action the Comms officer can use, with this, the entire ship may be controlled just by asking the computer to do things in English. For example, stuff like this should all work:

    /computer set a course for the nearest starbase
    /computer launch the mining bot
    /computer lower shields
    /computer set warp power to 100%
    /computer engage warp drive
    /computer turn left 10 degrees
    /computer engineering on screen
    /computer calculate a course to the nearest asteroid
    /computer describe 
    /computer set warp drive coolant to 50 percent

### Mainscreen
From the main screen, you can steer the ship with the ARROW KEYS and with the A, W, S, D keys and additionally Q and E allow you to roll the ship. The primary purpose of the main screen view it to be projected on a large screen for all players to view at once.

The backquote key cycles through first person and a few third person views of the ship.

The + and - (plus and minus) keys and the Mouse Scroll Wheel zoom and unzoom the camera. Additionally the zoom can be controlled from the COMMS screen.

SHIFT-W toggles the main screen view between front facing and weapons facing. This is fun to let the whole crew see what the WEAPONS OFFICER is busy destroying.

Note, in a proper multi-player setup, the MAIN SCREEN ROLE (on the NETWORK SETUP SCREEN, see below) should not be active (checked) for most players, but only for the computer which is connected to the projector or big TV.

The R key can be used to cycle through different renderer modes (this is really just for debugging though.)
