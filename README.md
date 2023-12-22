# SNiS Client Bridge/proxy over HTTP

This is a supplemental game client utility for the excellent multi-player starship bridge simulator ["Space Nerds in Space"](https://smcameron.github.io/space-nerds-in-space/). The intention is to allow Space Nerds in Space to offer an option for "mobile-first/responsive" html5/css/js based game client UI. Necessarily, these will be limited in control options, depending on what the built-in speech bridge feature already can do, and probably never have any "real" feedback.
With that, tablets, mobile telephones, and sundry hybrid-touchscreen-PCs (whether or not they are already running linux), and even potentially dedicated gaming consoles (modern ones using the now pretty common built-in webrowsers) can easily get into the mix of client consoles. Plus: if we do a good job with clean, well designed html/CSS, we get easy-ish reskinning of those clients (LCARS, anyone?). You could possibly just have a menu to instantly refresh page in the style of Star [Trek/Wars/Craft/Punk/etc]. Aside from supplemental bridge control screens, you kind of get functional Trek-style "PADD" mobile devices, too. Perhaps with some additional hackery, this could also be a way to give some kinds of side-channel/secondary functionality to a console. E.g., access to some kind of on-board encyclopedia, "decryption" tools, crew and cargo manifests, invocations of other RESTful APIs such as home-automation lighting, one-off mission-based "settings", one-off mission-based clues (that maybe are coordinated with prompts by main game script)  etc.

Mostly this project is just taking advantage of the clever "/computer" command interface by injection into /tmp/snis-natural-language-fifo (a named pipe which the SNiS game client reads from). So each button must map to one of those already supported commands. E.g., Throttle Up button sends a "THROTTLE UP" "command" back to this little bridge which just writes into the FIFO, and voila, the button caused throttle to go up.

Side-note: each game client's hostname suddenly becomes a potential URL. Or perhaps this bridge utility would only be running only on the server.

A supplemental expansion to this project:
Pi Pico W + GPIO + assorted electronics components 
+ https://docs.circuitpython.org/en/latest/shared-bindings/digitalio/index.html 
+ https://docs.circuitpython.org/en/latest/shared-bindings/mdns/index.html + https://docs.circuitpython.org/projects/requests/en/latest/api.html
(or just an out-of-the-box Pi Zero W) 
= fun and fancy physical control panel that takes advantage of this same bridge (because toggling a physical switch is read by pi gpio which then resolves snis-server.local and uses Requests library to send a "RESTful" CMD to the http_bridge process which feeds it to the fifo).

But then again, Pi Pico has USB HID, so it can pretend to be a keyboard, which might be a /lot/ simpler than all that.


references:
 - https://github.com/smcameron/space-nerds-in-space/blob/master/doc/hacking-space-nerds-in-space.html#guiwidget
 - https://smcameron.github.io/space-nerds-in-space/index.html#comcontrols
 - Some introductions and examples of mongoose webserver (the heart of the http-to-fifo bridge):
    * https://johnvidler.co.uk/linux-journal/LJ/192/10680.html
    * https://github.com/cesanta/mongoose/blob/master/examples/huge-response/main.c


## Setup
    clone https://github.com/jrwarwick/snis-web-consoles.git
    cd snis-web-consoles/
    # Assumes you already have a locally installed SNiS client so we can serve up sounds. Otherwise, you will need to supply your own sounds named according to what the html expects.
    ln -s /usr/local/share/snis/sounds/ ./sounds
    cd http_client_bridge/
    make

    # And now, once you already have your SNiS running (because we need that FIFO), start the http bridge process:
    ./http_client_bridge/snis_http_bridge
    # And navigate to http://${HOSTNAME}:8000/ in your preferred web-browsing device.

alt:
mkdir sound ; cd sound
ln -s /usr/local/share/snis/sounds/ui2.ogg tactinput_acknowledge.ogg
ln -s /usr/local/share/snis/sounds/ui3.ogg tactinput_neg_acknowledge.ogg



## ToDo:

### bugs
on phone: going to fullscreen in landscape is fine, but going to fullscreen in portrait pushs the right side column off screen
ships log is not sorted 

### Direct CMDs implementation
particularly  /CMD/QUIT to shutdown the http bridge process entirely
/CMD/ANNOUNCE to place a popup modal div on all connected clients with arbitrary message. Sanitization considerations.

### Makefile install target
Would not be necessary in this separate project if adopted upstream by parent project.
Maybe also special target for audio asset symlinking

### main index.html that is also a menu 
that lists all the client interfaces in a nice layout.

also maybe some fun/cool QR code , Chirp, TTS, IRC/XMLPP broadcasts etc to announce/share/spawn/clone the "client UI" URL. 
At least dump it on the console or something. Linux/freedesktop "notify-send" maybe?  https://community.linuxmint.com/tutorial/view/2177
https://specifications.freedesktop.org/notification-spec/notification-spec-latest.html

### manifest.json & favicon stuff
```html
<link rel="icon" type="image/png" href="/image.png">
```
more in depth read of Google's PWA specs.

### Themes/skins
CSS / template based approach.
 - SNiS
 - LCARS:TNG
 - Last Parsec
 - Artemis
 - Skeuomorphic things?: Star Wars-ish
 - need to actually handle portrait vs landscape. 

### audio
howler.js
sym link game assets (/usr/local/share/snis/sounds ?), if available (in the makefile, probably), but fallback to bundled default sounds.
naming/mapping/method(s)? (which might include some kind of respect for css classes)

### LARPy/BlinkenLights/Greebleisticness
Maybe some (optional) buttons and switches and "data read-outs" that do not actually have any game function whatsover.
but look kinda cool. With graphs, animations and so on.
	For Navigation: "INERTIAL DAMPING COMPENSATOR LOAD: 12 N [ 1.3G @ 727j ]" "GRAVITATIONAL WELL MAP"
	For Engineering & DamCon & Science:  Life Support "ATMOSPHERIC MIXTURE SPECTRAL ANALYSIS: [ 72 12 6 4 ] , BAROMETRICS [      |  x |  ]
	For Communications:  "INTERFERENCE MODULATOR PARAMETERS: [ 1273.23 887 3212.222 ]" "EMF PATTERN RECOGNIZER ALGORITHMS: QRF-Z (ALT7) XR3X"
	For Weapons: "TARGETING LOCK COUNTERMEASURE/COMPENSATION" "EMF REFRACTION INDEX"
maybe also a few actually kinda useful utilities, even though not strictly "game stuff". E.g., mini-SPA-app-features for: stopwatch/timer, calculator, rot13/viognere "decryptor", almanac-ish/quick-ref things (periodic table, universal constants & formulae, state transition temperatures for common materials, unit of measure conversions)

### Game data from server (back to this web client)
another bridging process? the same one? funky websockets implementation to "directly" get info from server (direct to webbrowser, that is)
map-like things, messages (perhaps daemon/GM messages to captain particularly)
The best options would require some concessions from the upstream game author. Either some kind of json publishing, or possibly a couple of lua hooks that can be hacked into providing something like this directly into the webroot of the http-bridge.

### Contemplate: Side-channel game info integration possibilities
There is some possibility for in-game elements, say a password, or coordinates, trajectory, energy level, etc. that could be discovered external to the game proper, perhaps because it was contained in one of these portable devices that was just conficscated from a spy, and it contains the secret info we need; but to "crack it" we need to solve the puzzle on the device, or get this other device unlocker from somewhere in game.
If this becomes a thing, it would probably be good to have some kind of conventional and standard documented way to include a note in the mission scripts that would advise demon screen and/or put an icon on mission select that "mission requires special external setup/prep". 

### Component naming reconsider
Is "bridge" a bad metaphor name because it collides with "starship _bridge_"? Maybe a rename to http_client_adapter?

### StarDate standard
Haven't found a reasonable and/or consolidated canonical standard. Here is one, about as ridiculous as everything else:
The star nearest to Sagittarius A* (the center of our galaxy) is desginated "S2". S2's orbit is 16 years; a hexadecade, if you will.
Let us pretend a very very stable orbital period, and we now have a stellar-based galactic basis for dates. I.e., Stardate.
Note that most star dates are 5 digit (in the TNG era, anyway), and given dates are about midway through the thousands.
Thus, if first three digits are the Hexadecade then we are around 2000 years after some shared marking event (maybe the first and only time a warp engine popped on the event horizon of Sagittarius A*, but it is a one-time deal and left a "tachyon stream", so while nice for reference, its a one-way suicide trip AND WE MUST NEVER DO IT AGAIN. DON'T CROSS THE STREAMS!).
Ok, so two digits of hexadeximal means we have 4,096 "earth years" of time expressed in the star date.
Then two more digits to divide a hexadecade into 256 pieces. That means 256 of 22 day-long (quasi-month) "epochs".
After "Mark/point", we have a decimal fraction; for every .01, a little over 5 hours passes and also thus .001 is about half an hour, and .0001 is about 3 minutes. So reasonably, a typical workshift or rest period is .02 long, and .1 is "a weekend" or "a couple of days", from a typical earth-human point of view.

So maybe a typical wristwatch will read:  
   .01:2:345
 5-hr  30m   1/100ths of a 30min seg
block  seg.   or: 3min and 20s and 2s ticks

Another idea is just to go sorta SI, but get the actual cesium period itself to a power of 10 and let "earth periods" fall where they may. 
Something like: the transition between the two hyperfine states of the atom's ground state. This transition occurs at a frequency of 9,192,631,770 oscillations per second, which is often rounded to 9.192631770 GHz.
So lets go with 10Ghz even. So "System Galactic" seconds are 1.08782775708 x longer than earth seconds.
Then decaseconds and then "minutes" are kinda close to hectoseconds, kinda almost 2 minutes. Then we have 18 (earth minute) periods, followed by 3-hour periods and then a 30-hour day. 10-day week (at 30-hours a day)? Maybe. 

but maybe all that is just too much baloney. a simple ISO standard YYYY-MM-DDTHH:MI trimmed and pronouncing only the digits and "T" as "mark" is understandable by real players, and kinda sounds goodish-enough.


## Screens
(from https://smcameron.github.io/space-nerds-in-space/#controls)

 - F1 is the help screen. Actually might be kind of useful/cool to have an electronic/digital OPERATIONS REFERENCE MANUAL page. However it would have to be ToC style instead of displaying depends on which screen you're "on".
 - F2 - NAVIGATION
 - F3 - WEAPONS
 - F4 - ENGINEERING
 - F5 - DAMAGE CONTROL
 - F6 - SCIENCE
 - F7 - COMMUNICATIONS
 - F8 - MAIN SCREEN
 - F9 - DEMON SCREEN (dungeon master screen)
 - -- plus synthetic and/or secondary/companion screens:
 - Captain /CO (including ships log)
 - Commander /XO
 - Cartography/Library
 - Knowledgebase (like an on-board encyclopedia/almanac/dossiers/world-fact-book type of thing)
 - Mining Bot Control and/or "Video Feed"
 - Manifest
 - Life Support
 - IT/CIS - could have actual stats on the game server, heh. htop/iostat/netstat, client count, last ping/request timestamp
 - Chronometry (Real Time, Mission Time, Countdown, etc.)
 - Comms II (webRTC, IRC, matrix, whatever sidechannels)
    * pipe in some kind of hip new chatbot thing with a bunch of noise, but also some in-game clue knowledge. Interrogate to try and get some "clues".


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
hmm, going to have to look into this bit where mouse is primary/maybe-only option:
> The mouse controls where the guns are pointed. The guns can yaw left and right and pitch up and down, but cannot roll.
> When the mouse is at the bottom center of the screen, the guns will be pointed straight ahead.
> Moving the mouse from the bottom to the top of the screen moves the guns through the full range of pitch.
> Moving the mouse to the left side of the screen to the right side of the screen moves the guns through the full range of yaw. (Note: Using the arrow keys, you can also yaw and pitch the guns. With the arrow keys, the yaw range is not limited (guns can rotate 360 degrees. This discrepancy could be considered a bug.)
 - Left mouse button and the SPACE BAR fire the phasers.
 - Right mouse button and the Z key fire torpedoes.
 - the + and - (plus and minus) keys control the WAVE LENGTH of the phasers. 
The CHARGE graph shows how much power will be released in the next phaser shot. It takes some time for the phasers to recharge. Firing rapidly means each shot contains less energy and does less damage (but if you miss, you will have wasted less energy.) If the phasers are damaged, or ENGINEERING has diverted power from the phasers, it may take longer to recharge.


### Damage Control Controls
 - Arrow Keys or W, A, S, D keys to control the movement of the robot.
 - Space Bar to control the robot's gripper.
The screen shows each of the systems on the ship, with each system having three components. The components may become damaged, making the systems less effective.
To repair a component, maneuver the robot near the component and use the gripper to pick up the component. If the component is not too badly damaged, the robot will repair it right there. After the component is repaired, operate the gripper to put the component back.
Note, you must put components back in the correct slots for them to work correctly, otherwise the systems will not operate well.
If a component is too badly damaged, you will need to take the component to the repair station located at the bottom. Put the component into one of the slots on the repair station and wait a moment for it to repair. You can pick it up before it is fully repaired and repair it to completion on the way back to replace the component in its slot in the appropriate system.
If you do not have enough players, or if you simply do not want to manually repair the ship, you can press the AUTO button, and the robot will autonomously repair the ship by itself. It probably won't do it as quickly as you could do it manually though.


### Science
#### SRS
Science Short Range Scanner Controls
 - Mouse Scroll Wheel or the RANGE slider control at the top of the screen controls the range (distance) of the short range scanner.
 - Left and Right Arrow keys or the A and D keys control the direction the scanning beam is pointed. The boundaries of the scanning beam is indicated by two flickering lines on the display.
 - Up and Down Arrow keys or the W and S keys control the scanning beam width. The wider the beam is the more volume it covers, but the less resolution it has. The narrower the beam is, the less volume it covers, but the more resolving power it has.
 Items in the scanner are displayed at a distance from the center which corresponds to the 3D distance.
When the scanner has resolved an entity, you can click on it with the mouse, and it, and nearby resolved entities will "pop up" out of the display to give you an idea of how they are situated in 3D space.
#### Details
Science Details Screen
Once an entity is resolved by the scanner and selected, you can press the DETAILS button to see more details about the selected item. What you see depends on the type of the item.
The Warp Factor value gives you an idea of what value to use if you wish to travel to the entity via the warp drive (that is, you may want to relay this information to the NAVIGATION OFFICER.)
If the entity is a ship, the SHIELD PROFILE may indicate that some phaser frequency might be especially effective (so you may want to relay this information to the WEAPONS OFFICER.)
#### LRS
Long Range Scanner Controls
The long range scanner is useful for locating distant planets and starbases. It shows a 3D view of the space around your ship.

 - Mouse Scroll Wheel or the RANGE slider control at the top of the screen controls the range (distance) of the long range scanner.
 - Left and Right Arrow keys or the A and D keys control the direction the scanning beam is pointed. The boundaries of the scanning beam is indicated by two orange dotted lines on the display forming a kind of "orange slice".
 - Up and Down Arrow keys or the W and S keys control the scanning beam width. The wider the beam is the more volume it covers, but the less resolution it has. The narrower the beam is, the less volume it covers, but the more resolving power it has.
 - comma, and forward slash keys rotate (yaw) the scanned volume sphere to the left or right, respectively.
 - period and L keys rotate (pitch) the scanned volume sphere down and up, respectively.
 - K and semicolon keys rotate (roll) the scanned volume sphere counter-clockwise and and clockwise, respectively.
 - ALIGN TO SHIP button aligns the view with the ship so that the view is as if from behind the ship with the ship facing forwards and up is up, left is left, right is right, etc.

### Communications
The row of buttons at the top is for the COMMS OFFICER to control what is displayed on the MAIN SCREEN. For this to work best, individual player stations should not have the MAIN SCREEN ROLE checked (on the NETWORK SETUP SCREEN when they joined the game) but only the computer attached to the projector or big TV should have the MAIN SCREEN role checked. Essentially these buttons make all terminals that have the MAIN SCREEN role switch to displaying the selected station instead. The idea behind this comes from Captain Picard's command, "On screen!" The captain can command any station's screen be displayed "On Screen!" and the COMMS OFFICER can "make it so". Note: it is also possible for any player to press Ctrl-O on their station to make their screen be displayed on the main screen. If they press Ctrl-O a second time, the main screen reverts to showing the main view out the window into space. So if the captain orders "Weapons, On Screen!", either the Weapons Officer can press Ctrl-O, or the Comms Officer can press the WEAPONS button on the COMMS screen. Again, if players have the "MAIN SCREEN" role checked when they join the game, it can be a bit confusing, because then their own computer will be considered to be a "main screen". In general, there normally should only be one computer per bridge that joins the game with the MAIN SCREEN role enabled, and that computer should be the one connected to a projector.

The "EMF" chart in the upper right shows a measuring of local EMF. When an NPC ship scans the players ship, this chart will show elevated levels of EMF. This can give a heads up that some ship is scanning you, and an attack might be coming soon.

 - MAIN SCREEN button in the lower right portion of the screen makes the last 4 lines received appear on the main screen so everyone can see them.
 - RED ALERT button toggles the red alert system on and off.
 - shields display is there so the COMMS officer can know if a request to dock will be denied due to shields still being up.
 - zoom slider control at the bottom of the screen controls the zoom level of the MAIN SCREEN

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
From the main screen, you can steer the ship 
The primary purpose of the main screen view it to be projected on a large screen for all players to view at once.

 - backquote key cycles through first person and a few third person views of the ship.
 - + and - (plus and minus) keys zoom and unzoom the camera. (Additionally the zoom can be controlled from the COMMS screen.)
 - SHIFT-W toggles the main screen view between front facing and weapons facing. This is fun to let the whole crew see what the WEAPONS OFFICER is busy destroying.
 - R key can be used to cycle through different renderer modes (this is really just for debugging though.)
 - ARROW KEYS and with the A, W, S, D keys steer the ship.
 - Q and E allow you to roll the ship. 

Note, in a proper multi-player setup, the MAIN SCREEN ROLE (on the NETWORK SETUP SCREEN, see below) should not be active (checked) for most players, but only for the computer which is connected to the projector or big TV.


